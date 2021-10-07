/******************************************************************************
* University of Central Florida 10th Annual High School Programming Tournament*
*                                                                             *
* File: HAIKU.C - Solution to the "Check-ing Hai-ku" problem                  *
*                                                                             *
*                                                                             *
******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int CountSyllables(char *s)
{
  int count, loop;

  /* for sake of simplicity, first change all dashes into spaces, so
    we only have to deal with one whitespace character */

  for (loop = 0; loop < strlen(s); loop++)
    if (s[loop] == '-')
      s[loop] = ' ';

  /* Now, any group of non-space characters will represent a syllable.
    Starting from the first character in the string, look for non-space
    characters. Whenever one is found, increment count and then move the
    looping variable past this syllable. */

  count = 0;
  loop = 0;
  while (loop < strlen(s))
  {
    if (s[loop] != ' ')  /* found the first letter of a syllable */
    {
      count++;
      while ((loop < strlen(s)) && (s[loop] != ' '))
        loop++;
    }
    else
      loop++;  /* skip over this space character */
  }
  return count;
}


typedef int HaikuSyllableCounts[10];

#define ErrorStr "Not a Haiku because it has"

void CheckValidity (HaikuSyllableCounts Lines, int NumLines)
{
  if (NumLines != 3)         /* too few / too many lines */
    printf("%s the wrong number of lines.\n", ErrorStr);
  else if (Lines[0] != 5)   /* wrong # of syllables on line 1 */
    printf("%s the wrong number of syllables on line 1.\n", ErrorStr);
  else if (Lines[1] != 7)   /* wrong # of syllables on line 2 */
    printf("%s the wrong number of syllables on line 2.\n", ErrorStr);
  else if (Lines[2] != 5)   /* wrong # of syllables on line 3 */
    printf("%s the wrong number of syllables on line 3.\n", ErrorStr);
  else
    printf("Good Haiku!\n");
}


void main()
{
  char istr[256];
  int NumLines, loop;
  HaikuSyllableCounts Lines;
  FILE *infile;

  infile = fopen("haiku.in", "rt");
  do
  {
    /* initialize variables */
    NumLines = 0;
    for (loop = 0; loop < 10; loop++)
      Lines[loop] = 0;
    /* read in lines until a blank is found, or eof is reached */
    do
    {
      istr[0] = '\0';
      if (!feof(infile))
      {
        fgets(istr, sizeof(istr), infile);
        /* strip off carriage return, if it exists */
        if ((strlen(istr) > 0) && (istr [ strlen(istr)-1 ] == '\n'))
          istr[ strlen(istr)-1 ] = '\0';
        if (strlen(istr) > 0)
        {
          Lines[NumLines] = CountSyllables(istr);
          NumLines++;
        }
      }
    } while ((!feof(infile)) && (strlen(istr) > 0));
    /* Now, NumLines has the number of lines in this student's haiku.
    Time to see if the haiku is valid. */
    CheckValidity(Lines, NumLines);

  } while (!feof(infile));

  fclose(infile);
}


