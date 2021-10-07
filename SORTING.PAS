{ University of Central Florida 10th Annual High School Programming Tournament }
{ Problem Name: Sorting                                                        }
{ Input File  : sorting.in                                                     }
{ Output File : output to screen                                               }
{                                                                              }
{ Given two numbers, print which is larger by ouputting the corresponding      }
{ color                                                                        }
{                                                                              }
Program Sorting;

Var
  InFile : Text;
  st     : String;
  White,
  Dark   : Integer;

Begin
  Assign(InFile, 'sorting.in');
  Reset(InFile);
  while Not Eof(InFile) Do
    Begin
      Readln(InFile, White, Dark);
      if White > Dark then
          Writeln('whites darks')
      else
          Writeln('darks whites');
    End;

  Close(InFile);
End.
