/*University of Central Florida 10th Annual High School Programming Tournament
  Problem Name: Sorting
  Input File  : sorting.in
  Output File : output to screen

  Given two numbers, print which is larger by ouputting the corresponding
  color
									      */
#include <stdio.h>

void main()
{
FILE *In;
char st[256];
int White, Dark;

  In = fopen("sorting.in","rt");
  while (fgets(st,256,In))
  {
    sscanf(st,"%d %d",&White,&Dark);
    if (White > Dark)
      printf("whites darks\n");
    else
      printf("darks whites\n");
  }
  fclose(In);
}
