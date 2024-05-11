#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include<errno.h>
#include <fcntl.h>
#include<sys/wait.h>
#include <libgen.h>


#define TYPESIZE 50
#define FILESIZE 100

typedef struct
{
    char name[TYPESIZE];
    off_t size;
    unsigned long id;
    time_t access;
    char type[TYPESIZE];
}Metadata_t;

int isDir(const char* fileName)
{
  struct stat path;
  if(lstat(fileName, &path)==-1)
  {
    exit(-1);
  }
  return S_ISDIR(path.st_mode);
}

DIR* openDir(const char* fileName)
{
   if(!isDir(fileName))
   {
      perror("The argument is not a directory\n");
      exit(-1);
   }
  DIR *dir=opendir(fileName);
  if(dir==NULL)
  {
    perror("Error opening the directory\n");
    exit(-1);
  }  
  return dir;
}

void print(Metadata_t d[FILESIZE], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s: %s,%ld,%ld,%ld\n",d[i].name,d[i].type,d[i].access,d[i].id,d[i].size);
    }
    printf("\n");
}

int removeFile(char *path,char *izolateDirectory)
{
    char destPath[256] = "./";
    strcat(destPath,izolateDirectory);
    strcat(destPath,"/");
    strcat(destPath, basename(path));
    if (rename(path, destPath) == 0)
        return 1;
    else
        return 0;
}

int hasActivePermission(const char *path)
{
    struct stat fileStat;

    if (stat(path, &fileStat) == -1)
    {
        perror("Error getting file status\n");
        return -1;
    }

    if (fileStat.st_mode & S_IRWXU || fileStat.st_mode & S_IRWXG || fileStat.st_mode & S_IRWXO)
        return 1;
    else return 0;
}

Metadata_t addData(const char *fileName)
{
  Metadata_t auxFile;
  struct stat path;
  if(lstat(fileName,&path)==-1)
  {
      perror("Error accessing file in addData");
      fprintf(stderr, "Error code: %d\n", errno);
      exit(-1);
  }
  if(isDir(fileName))
    {
      strcpy(auxFile.type,"Directory");
    }

  else strcpy(auxFile.type,"File");
  auxFile.size=path.st_size;
  auxFile.id=path.st_ino;
  auxFile.access=path.st_mtime;
  return auxFile;
}

void readDataAboutDirectory(const char *dirName,char *isolateDirectory,Metadata_t *files,int *count)
{
    DIR *dir = openDir(dirName);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.') continue;
        char path[TYPESIZE] = "./";
        strcat(path, dirName);
        strcat(path, "/");
        strcat(path, entry->d_name);

        if (!hasActivePermission(path))
        {
            int fd[2];
            if (pipe(fd) == -1)
            {
                perror("Pipe creation failed");
                exit(-1);
            }

            pid_t pid = fork();

            if (pid == -1)
            {
                perror("Fork failed");
                exit(-1);
            }

            if (pid == 0)
            {
                close(fd[0]);
                chmod(path, S_IRGRP | S_IRUSR | S_IROTH);
                char command[TYPESIZE];
                snprintf(command, sizeof(command), "./verify_malicious.sh %s", path);
                int final_status;
                if ((final_status = system(command)) == -1)
                {
                    exit(-1);
                }

                chmod(path, 0);
                if (final_status == 0)
                    write(fd[1], path, sizeof(path));

                else
                    write(fd[1], "SAFE", sizeof(path));

                close(fd[1]);
                exit(0);
            }
            close(fd[1]);

            int status;
            waitpid(pid, &status, 0);

            char result[TYPESIZE];
            read(fd[0], result, TYPESIZE);

            close(fd[0]);

            if (strcmp(result, "SAFE") != 0)
            {
                removeFile(path,isolateDirectory);
                continue;
            }
        }
        files[*count] = addData(path);
        strcpy(files[*count].name, entry->d_name);
        (*count)++;
        if (isDir(path))
            readDataAboutDirectory(path, isolateDirectory,files, count);
    }
}

int isEmpty(const char *file)
{
    struct stat path;
    if(lstat(file,&path) == -1)
    {
        if(errno == ENOENT) return 1;
        exit(-1);
    }
    if(path.st_size==0) return 1;
    return 0;
}


void printSnapshot(char *dirName,char *outputDirName,Metadata_t *d, int count)
{
    char outFile[TYPESIZE] = "./";
    strcat(outFile,outputDirName);
    strcat(outFile,"/");
    strcat(outFile,dirName);
    strcat(outFile,"_snapshot.txt");
    int file = open(outFile, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (file == 0) {
        perror("Error opening file for writing");
        exit(-1);
    }

    char buff[FILESIZE * 2];
    for (int i = 0; i < count; i++)
    {
        snprintf(buff, sizeof(Metadata_t), "Name: %s\n ID: %ld\n Size:%ld\n Last access: %ld\n Type: %s\n\n", d[i].name, d[i].id, d[i].size, d[i].access,
                 d[i].type);
        write(file, buff, strlen(buff));
    }
    close(file);
}

void printData(Metadata_t d[FILESIZE], int count, char *file)
{
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("Error opening the file for writing\n");
        exit(-1);
    }

    for (int i = 0; i < count; ++i)
    {
        write(fd, &d[i], sizeof(Metadata_t));
    }

    close(fd);
}

void readData(Metadata_t d[FILESIZE], int *count, char *file) {
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening the file for reading\n");
        exit(-1);
    }

    int i = 0;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &d[i], sizeof(Metadata_t))) > 0)
        ++i;

    if (bytesRead == -1)
    {
        perror("Error reading from the file\n");
        exit(-1);
    }
    *count = i;
    close(fd);
}

int compareData(Metadata_t *d, Metadata_t *aux, int count1, int count2)
{
    int returnValue=0;
    if(count1!=count2)
    {
        printf("The number of the files has changed\n");
        return 1;
    }
    for(int i=0; i<count1;i++)
        for(int j=0; j<count2;j++)
        {
            if(d[i].id == aux[j].id)
            {
                if(strcmp(d[i].name,aux[j].name)!=0)
                {
                    printf("The name of the file %s has been changed\n",d[i].name);
                    returnValue++;
                }
                if(d[i].access!=aux[j].access)
                {
                    printf("The file %s has been accessed\n",d[i].name);
                    returnValue++;
                }
                if(d[i].size != aux[j].size)
                {
                    printf("The size of the file %s has been changed\n",d[i].name);
                    returnValue++;
                }
                break;
            }
        }
    if(!returnValue) printf("No changes found\n");
    return returnValue;
}

void startProcess(char *name,char *outputDir,char *isolateDirectory)
{
    if(!isDir(name))
    {
        printf("Argument is not a directory\n");
        exit(-1);
    }

    Metadata_t d[FILESIZE],aux[FILESIZE];
    int count=0,count2=0;
    readDataAboutDirectory(name,isolateDirectory,d,&count);

    char path[TYPESIZE] = "./utils/";
    strcat(path, name);
    strcat(path, "_snapshot.txt");

    if(isEmpty(path))
    {
        printData(d, count,path);
    }
    else
    {
        readData(aux, &count2, path);
        if (compareData(d, aux, count, count2) > 0)
        {
            printSnapshot(name, outputDir, aux, count2);
            printData(d, count, path);
        }
    }
    exit(0);
}

void waitForChildren(int numChildren)
{
    int status;
    pid_t pid;

    for (int i = 0; i < numChildren; i++)
    {
        pid = waitpid(-1, &status, 0);
        if (pid > 0)
        {
            if (WIFEXITED(status))
            {
                printf("Child process with PID %d ended with exit code %d.\n", pid, WEXITSTATUS(status));
            }
            else
            {
                printf("Child process with PID %d ended unusually .\n", pid);
            }
        } else
        {
            perror("Error waiting for the child process.\n");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc,char **argv)
{
   if(argc<5|| argc>14)
   {
       perror("The number of arguments is not the right one\n");
       exit(-1);
   }

   for(int indx=4;indx<argc;indx++)
   {
         pid_t pid = fork();
         if(pid<0)
         {
             exit(-1);
         }
         else if(pid == 0)
         {
             startProcess(argv[indx],argv[2],argv[3]);
         }
   }

    waitForChildren(argc-4);

    return 0;
}
