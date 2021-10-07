/*-----------------------------------------------------------------
Program Name
   Predict.cpp

Programer
   Chris Stadler May 2, 1996

Function
   Solution for Predict problem for HS contest.

Input
   File off disk (Predict.in)

Output
   Screen
-----------------------------------------------------------------*/

#include <stdio.h>
FILE *infile;                          /*  File to read from Disk  */

void main(void)
{
  int day;                             /*  Day Counter    */
  int month;                           /*  Month Counter  */
  int dayomonth[13];                   /*  Days in Month Database  */

  dayomonth[1] = 31;   dayomonth[7] = 31;
  dayomonth[2] = 28;   dayomonth[8] = 31;
  dayomonth[3] = 31;   dayomonth[9] = 30;     /*  Loading in # of days  */
  dayomonth[4] = 30;   dayomonth[10] = 31;    /*  In Each month         */
  dayomonth[5] = 31;   dayomonth[11] = 30;
  dayomonth[6] = 30;   dayomonth[12] = 31;

  infile = fopen("predict.in","r");

  fscanf(infile, "%d", &day);               /*  Reads on starting day  */
  while(day != 0)
  {
     month = 1;
     if(day > 28)
     {
       month = 2;                        /* checks day=31 case */
       day = day - 31;
     }
     while (month < 12)
     {
	day = day + 29;
	if(day > dayomonth[month])
	{
	  day = day - dayomonth[month];
	  month = month + 1;
	}
	printf("Full Moon On %d-%d\n",month,day);
     }
     fscanf(infile, "%d", &day);
     printf("\n");
  }
  fclose(infile);
}