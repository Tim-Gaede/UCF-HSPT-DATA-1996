/*University of Central Florida 10th Annual High School Programming Tournament 
  Problem Name: Simple                                                         
  Input File  : simple.in                                                      
  Output File : output to screen                                               
                                                                               
  Determine if a polygon is simple.  A polygon is simple if none of its edges  
  cross.  For each edge, this program loops through all the other edges and    
  checks to see if they intersect.  If any such intersections exist, the       
  polygon is not simple.                                                       
                                                                              */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO  0
#define YES 1
#define CO  2

typedef struct
{
    int X, Y;
} Point;




/* within                                                                  */
/*                                                                         */
/* Performs a simple bounding check to see if b is between a and c         */
/*                                                                         */
int within(long int b, long int a, long int c)
{
    if (a > c)
      return ((c <= b) && (b <= a));

    return ((a <= b) && (b <= c));
}






/* SegmentIntersect                                                        */
/*                                                                         */
/* Solves for the "time" of intersection using the parametric form of the  */
/* lines.  Uses Cramer's rule to solve for the parameters.                 */
/*                                                                         */
/* Considerations:                                                         */
/*   Is the point of intersection needed? (if so t1 = P/D, etc.)           */
/*   Colinear, intersecting segments return CO.  if this is not a concern  */
/*     that block of code may be deleted.                                  */
/*                                                                         */
int SegmentIntersect(Point L1, Point L2, Point M1, Point M2)
{
long int Ldx, Ldy, Mdx, Mdy; /* Deltas                  */
long int P,                  /* t1 determinant          */
         Q,                  /* t2 determinant          */
         D;                  /* denominator determinant */

    /* Calculate delta values */
    Ldx = L2.X - L1.X;
    Ldy = L2.Y - L1.Y;
    Mdx = M2.X - M1.X;
    Mdy = M2.Y - M1.Y;

    /* Calculate determinants */
    D = Ldx*-Mdy + Ldy*Mdx;
    P = (M1.X-L1.X)*-Mdy + Mdx*(M1.Y-L1.Y);
    Q = Ldx*(M1.Y-L1.Y) - Ldy*(M1.X-L1.X);

    /* if D is 0, then L and M are paralell or colinear,  */
    /* and the parameters are undefined                   */
    if (!D)
    {
        if ( (within(M1.X,L1.X,L2.X) || within(L1.X,M1.X,M2.X)) &&
             (within(M1.Y,L1.Y,L2.Y) || within(L1.Y,M1.Y,M2.Y)) )
            return CO;
        else
            return NO;
    }

    /* otherwise, check to see if the parameters fall between 0 and 1 */
    if (D > 0)
        return ( ((P >= 0) && (P <= D)) && ((Q >= 0) && (Q <= D)) );
    else if (D < 0)
        return ( ((P <= 0) && (P >= D)) && ((Q <= 0) && (Q >= D)) );
    else
        return NO;
}






void main()
{
FILE  *In;
Point Poly[100];
char  st[256];
int   NPoly, bSimple;
int   i, j;

    In = fopen("simple.in","rt");
    
    while (fgets(st,256,In))
    {
        /* Read in the number of vertices */
        sscanf(st,"%d",&NPoly);
        if (!NPoly)
          break;

        /* Read in the vertices */
        for (i=0; i < NPoly; i++)
        {
          fgets(st,256,In);
          sscanf(st,"%d %d", &Poly[i].X, &Poly[i].Y);
        }

        /* Copy to first vertex to "close" the polygon */
        Poly[NPoly].X = Poly[0].X;
        Poly[NPoly].Y = Poly[0].Y;
        NPoly++;

        /* Loop through the edges looking for intersections */
        bSimple = 1;
        for (i=1; i < NPoly; i++)
        {
            for (j=i+2; j < NPoly; j++)
            {
                if ((i==1) && (j == NPoly-1))
                    continue;

                if ( SegmentIntersect(Poly[i-1], Poly[i], Poly[j-1], Poly[j]) )
                {
                    printf("NOT ");
                    bSimple = 0;
                    break;
                }
            }
            if (!bSimple)
                break;
        }
        printf("SIMPLE\n");
    }

    fclose(In);
}
