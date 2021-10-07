/*-----------------------------------------------------------------
Program Name
   Space.cpp

Programer
   Chris Stadler May 2, 1996

Function
   Solution for Space problem for HS contest.

Input
   File off disk (space.in)

Output
   Screen
-----------------------------------------------------------------*/

#include <stdio.h>
FILE *infile;                /* Input File Name */

void main(void)
{
  int x;                     /* # of names to read               */
  int y;                     /* Counter #1                       */
  int z;                     /* Counter #2                       */
  char ch[3];                /* Charictor String read by Program */

  infile =  fopen("space.in","r");  /* Set Space.In as Input File Name */

  fscanf(infile,"%d", &x);          /* Reads Number of Names to read */
  for (y=0; y<x; y++)
  {
    fscanf(infile,"%s",ch);
    for (z=0; z<3; z++)
    {
      ch[z]--;                      /* Deincrement Charictor  */
      if(ch[z]=='@')                /* Converts A's to Z      */
      {
	ch[z] ='Z';
      }
    }
  printf("%s\n",ch);
  }

  fclose(infile);
}
