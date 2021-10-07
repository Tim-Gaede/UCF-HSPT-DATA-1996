{ University of Central Florida 10th Annual High School Programming Tournament }
{ Problem Name: Simple                                                         }
{ Input File  : simple.in                                                      }
{ Output File : output to screen                                               }
{                                                                              }
{ Determine if a polygon is simple.  A polygon is simple if none of its edges  }
{ cross.  For each edge, this program loops through all the other edges and    }
{ checks to see if they intersect.  If any such intersections exist, the       }
{ polygon is not simple.                                                       }
{                                                                              }
Program Simple;

type Point = Record
    X,Y : Integer;
end;

const
  NO  = 0;
  YES = 1;
  CO  = 2;



{ within                                                                  }
{                                                                         }
{ Performs a simple bounding check to see if b is between a and c         }
{                                                                         }
function Within(var b, a, c : Integer) : boolean;
  begin
    if a > c then
      Within := ((c <= b) AND (b <= a))
    else
      Within := ((a <= b) AND (b <= c));
  end;





{ SegmentIntersect                                                        }
{                                                                         }
{ Solves for the "time" of intersection using the parametric form of the  }
{ lines.  Uses Cramer's rule to solve for the parameters.                 }
{                                                                         }
{ Considerations:                                                         }
{   Is the point of intersection needed? (if so t1 = P/D, etc.)           }
{   Colinear, intersecting segments return CO.  if this is not a concern  }
{     that block of code may be deleted.                                  }
{                                                                         }
function SegmentIntersect(var L1, L2, M1, M2 : Point) : Integer;
  var
    Ldx, Ldy, Mdx, Mdy : LongInt; { Deltas                  }
    P,                            { t1 determinant          }
    Q,                            { t2 determinant          }
    D                  : LongInt; { denominator determinant }
    bP, bQ             : Boolean;

  begin
    { Calculate delta values }
    Ldx := L2.X - L1.X;
    Ldy := L2.Y - L1.Y;
    Mdx := M2.X - M1.X;
    Mdy := M2.Y - M1.Y;

    { Calculate determinants }
    D := Ldx*-Mdy + Ldy*Mdx;
    P := (M1.X-L1.X)*-Mdy + Mdx*(M1.Y-L1.Y);
    Q := Ldx*(M1.Y-L1.Y) - Ldy*(M1.X-L1.X);

    { if D is 0, then L and M are paralell or colinear,  }
    { and the parameters are undefined                   }
    if D = 0 then
      begin
          if ( within(M1.X,L1.X,L2.X) OR within(L1.X,M1.X,M2.X) ) AND
             ( within(M1.Y,L1.Y,L2.Y) OR within(L1.Y,M1.Y,M2.Y) ) then
            SegmentIntersect := CO
          else
            SegmentIntersect := NO;
      end
    { otherwise, check to see if the parameters fall between 0 and 1 }
    else
      begin
        if D > 0 then
          begin
            bP := (P >= 0) AND (P <= D);
            bQ := (Q >= 0) AND (Q <= D);
          end
        else if D < 0 then
          begin
            bP := (P <= 0) AND (P >= D);
            bQ := (Q <= 0) AND (Q >= D);
          end
        else
          bP := False;

        if bP AND bQ then
          SegmentIntersect := YES
        else
          SegmentIntersect := NO;
      end
  end;




VAR
  InFile : Text;
  Poly    : Array[1..100] of Point;
  NPoly   : Integer;
  st      : String;
  i,j     : Integer;
  bSimple : Boolean;

BEGIN
    Assign(InFile, 'simple.in');
    reset(InFile);

    { Read in the number of vertices for the first set }
    readln(InFile, NPoly);
    while (NPoly > 0) AND (Not Eof(InFile)) Do
      begin
        { Read in the vertices }
        For i := 1 to NPoly Do
          readln(InFile, Poly[i].X, Poly[i].Y);

        { Copy to first vertex to "close" the polygon }
        Poly[NPoly+1].X := Poly[1].X;
        Poly[NPoly+1].Y := Poly[1].Y;
        NPoly := NPoly + 1;

        { Loop through the edges looking for intersections }
        bSimple := True;
        For i := 2 to NPoly Do
          begin
            For j := i+2 to NPoly Do
              begin
                if not ((i = 2) AND (j = NPoly)) and
                   (SegmentIntersect(Poly[i-1], Poly[i], Poly[j-1], Poly[j]) <> 0) then
                  begin
                    Write('NOT ');
                    bSimple := False;
                    break;
                  end;
              end;

            if NOT bSimple then
                break;
          end;
        Writeln('SIMPLE');

        { Read in the number of vertices for the next set }
        readln(InFile, NPoly);
      end;

    close(InFile);
END.
