# Directory Monitoring and Security Enhancement

## Overview

This program offers a suite of functionalities aimed at directory monitoring and enhancing system security. It operates on the principle of creating snapshots of directory contents, detecting potentially dangerous or corrupted files, and isolating them to mitigate security risks.

## Task 1: Directory Snapshot Creation

The program initiates by creating a directory monitoring system. It accepts a directory path as a command-line argument and meticulously monitors it for any changes. Leveraging C language functions like `opendir`, `readdir`, and `stat`, it captures metadata for each item within the directory, including name, size, type, and other pertinent attributes. This information is then stored in a snapshot for future comparison.

## Task 2: Enhanced Functionality with Command-line Arguments

Building upon the initial functionality, the program now accepts up to 10 unique directory paths as command-line arguments. It processes only directories, disregarding other types of arguments. Metadata capture and snapshot creation are extended to all valid directory inputs provided by the user. Additionally, the program introduces an output directory specified by the `-o` option, where snapshots of all specified directory entries are stored.

## Task 3: Parallel Snapshot Creation

To expedite the snapshot creation process, the program utilizes system calls to spawn a new process for each parsed directory. These child processes run in parallel, each responsible for creating snapshots for its assigned directory. Upon completion, the parent process retrieves the status of each child process and displays a corresponding message.

## Task 4: Identification of Dangerous or Corrupted Files

A critical aspect of system security is the detection and isolation of potentially harmful files. This task focuses on implementing a mechanism to analyze files within a specified directory for signs of corruption or malicious content. Suspected files are flagged for further scrutiny and isolation.

## Task 5: File Corruption Detection Script

The program employs a file analysis script to identify potentially corrupted files based on specific criteria. This script evaluates various aspects such as the number of lines, words, characters, presence of non-ASCII characters, and keywords associated with dangerous files. Upon detection of suspicious characteristics, the script flags the file as dangerous.

## Implementation Details

The program executes the file analysis script within child processes, communicating results to the parent process through pipes. Based on the received information, the parent process determines whether to move the files to an isolated directory. This process ensures the proactive identification and isolation of potentially harmful files, thereby enhancing system security.

## Conclusion

By combining directory monitoring with advanced file analysis techniques, this program provides a comprehensive solution for maintaining system integrity and security. Users can rest assured knowing that potentially dangerous or corrupted files are promptly identified and isolated, mitigating the risks posed by malicious entities.

