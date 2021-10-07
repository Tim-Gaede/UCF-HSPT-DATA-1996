{-----------------------------------------------------------------
Program Name
   Space.pas

Programer
   Chris Stadler May 2, 1996

Function
   Solution for Space problem for HS contest.

Input
   File off disk (space.in)

Output
   Screen
-----------------------------------------------------------------}

program space;

var infile:   text;            {Input File Name}
    x:        integer;         {# of names to read}
    y:        integer;         {Counter #1}
    z:        integer;         {Counter #2}
    code:     integer;         {Asc Value of Correct Charictor}
    st:       string;          {Charictor read in by Program}

begin

    assign(infile, 'space.in');     { \__ Sets up Space.in as   }
    reset(infile);                  { /   a file off of a disk  }

    readln(infile,x);               {Reads Number of names to read}

    for y := 1 to x do
      begin
       readln(infile,st);
       for z := 1 to 3 do
         begin
          code := ord(st[z])-1;
                               {DeIncrements Charictor}
          if code = 64 then code:=code + 26;
                               {Converts letter A to Z}
          write(chr(code));
         end;
       writeln;
      end;
    close(infile);
end.