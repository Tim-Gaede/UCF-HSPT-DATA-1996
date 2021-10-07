/************************************************************************/
/*   Palindrome Compression                                             */
/*   for the 1996 High School Programming Contest                       */
/************************************************************************/

#include <stdio.h>
#include <string.h>

void main()
{
     FILE *fp;
     char szWord[72];
     int iFront, iBack;

     fp = fopen("compress.in","rt");

     while (!feof(fp))
     {
          /* read a string from the input */
          fscanf(fp,"%s",szWord);

          iFront = 0;
          iBack = strlen(szWord) - 1;

         /* Scan the word from both ends until it is not */
         /* symmetric or the middle is reached.          */
         while ((szWord[iFront]==szWord[iBack]) &&
              (iBack > iFront))
         {
             iBack--;
             iFront++;
         }

         /* Determine if this is an even palindrome, an odd */
         /* palindrome, or not a palindrome, and print the  */
         /* results.                                        */
         if (iBack>iFront)
         {
            /* it's not a palindrome */
            printf("%s\n",szWord);
         }
         else if (iBack == iFront)
         {
              /* it's an odd palindrome -- truncate the string */
              /* after the first half and then output with '~' */
              szWord[iFront+1] ='\0';
              printf("%s~\n",szWord);
         }
         else  /* iBack < iFront */
         {
               /* It's and even palindrome -- truncate the string */
               /* and output '*'                                  */
               szWord[iFront] = '\0';
               printf("%s*\n",szWord);
         }

     }

     fclose (fp);

}
