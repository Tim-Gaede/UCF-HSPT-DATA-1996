#include <stdio.h>
#include <string.h>

void main(void)
{
        FILE *fp;
        char line[80];

        /* Open the file */
        fp = fopen("nocrt.in","rt");

        /* Read one line at a time until end of file */
        while(fgets( line, 80, fp ))
        {
                /* Remove the newline */
		if (line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = '\0';

                /* Check if the line matches uses crt; */
                if (!strcmp(line,"uses crt;"))
                {
                        /* If it does, print Wrong Answer */
                        printf("Wrong Answer\n");
                }
                else
                {
                        /* Otherwise, print Might be correct */
                        printf("Might be correct\n");
                }
        }

        /* Close the file */
        fclose( fp );
}

