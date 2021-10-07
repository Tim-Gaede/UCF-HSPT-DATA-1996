#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 5K ==> 5 Kilometers --> 5000 meters */
#define DISTANCE 5000.0

char FastestRunnerName[100];
long FastestRunnerTime;

void main()
{
  int RaceNo = 0, NumRunners = 1, i;
  float DistanceLeft;

  FILE *fin = fopen("running.in", "rt");

  if (fin == NULL) return;
  
  while (!feof(fin) && (NumRunners != 0))
  {
    char data[200];
    
    fgets(data, 190, fin);
    NumRunners = atoi(data);

    while (NumRunners != 0)
    {
      char RunnersName[100];
      float Speed, RunTime, RestTime;
      float Cycles, Extra, TotalTime;

      strcpy(FastestRunnerName, "nobody.");
      FastestRunnerTime = 99999;

      for(i=0;i<NumRunners;i++)
      {
	    fgets(data, 190, fin);
	    sscanf(data, "%s", RunnersName);

	    fgets(data, 190, fin);
	    sscanf(data, "%f", &Speed);

	    fgets(data, 190, fin);
	    sscanf(data, "%f", &RunTime);

	    fgets(data, 190, fin);
	    sscanf(data, "%f", &RestTime);

	    /* Distance that can be traveled in one cycle is */
	    /* Speed*RunTime                                 */
	    Cycles = DISTANCE/(Speed*RunTime);
	    Extra  = Cycles;

	    /* Whole Portion */
	    Cycles = floor(Cycles);

	    /* Remainder */
	    Extra  = Extra - Cycles;

	    /* Compute time necessary for running and resting */
	    TotalTime = Cycles*(RunTime + RestTime);

	    /* Meters left */
	    DistanceLeft = DISTANCE - Cycles*Speed*RunTime;

	    TotalTime += DistanceLeft / Speed;

	    if (TotalTime < FastestRunnerTime)
	    {
	      FastestRunnerTime = (long) floor ( TotalTime + 0.5 );
	      strcpy(FastestRunnerName, RunnersName);
	    }
      }

      RaceNo++;
      printf("Race %d: The winner is %s with a time of %ld:%02ld.\n",
	    RaceNo, FastestRunnerName,
	    FastestRunnerTime/60, FastestRunnerTime % 60);

      fgets(data, 190, fin);
      NumRunners = atoi(data);

    }
  }
}
