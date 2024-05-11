#include<stdio.h>
#include<stdlib.h>
#include"Bin.h"

int main()
{
  int n=4;
  Student_t s[] = {
		   {"ana",19,8},
		   {"mihai",21,6.5},
		   {"maria",20,9.2},
		   {"andrei",29,4}};
  int m;
  scriereFisierBinar("testare.bin",s,n);
  Student_t v[SIZE];
  citire("testare.bin",v,&m);
  printf("%d\n",m);
  afisare(v,m);
  cautare("testare.bin",2);
  scriereFisierText("test2.txt",v,m);
  return 0;
}
