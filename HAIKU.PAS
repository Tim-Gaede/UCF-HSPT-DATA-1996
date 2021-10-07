{******************************************************************************
* University of Central Florida 10th Annual High School Programming Tournament*
*                                                                             *
* File: HAIKU.PAS - Solution to the "Check-ing Hai-ku" problem                *
*                                                                             *
*                                                                             *
******************************************************************************}

program Haiku;


function CountSyllables(s : string) : integer;
var
  count, loop : integer;
begin
  { for sake of simplicity, first change all dashes into spaces, so
    we only have to deal with one whitespace character }
  for loop:=1 to length(s) do
    if s[loop] = '-' then
      s[loop]:=' ';

  { Now, any group of non-space characters will represent a syllable.
    Starting from the first character in the string, look for non-space
    characters. Whenever one is found, increment count and then move the
    looping variable past this syllable. }
  count:=0;
  loop:=1;
  while (loop <= length(s)) do
  begin
    if (s[loop] <> ' ') then
    begin
      count:=count+1;
      while (loop <= length(s)) and (s[loop] <> ' ') do
        loop:=loop+1;
    end
    else
      loop:=loop+1;
  end;
  CountSyllables:=count;
end;


type
  HaikuSyllableCounts = array [1..10] of integer;

const
  ErrorStr = 'Not a Haiku because it has ';

procedure CheckValidity( Lines : HaikuSyllableCounts; NumLines : integer);
begin
  if (NumLines <> 3) then { too few / too many lines }
    writeln(ErrorStr, 'the wrong number of lines.')
  else if (Lines[1] <> 5) then { wrong # of syllables on line 1 }
    writeln(ErrorStr, 'the wrong number of syllables on line 1.')
  else if (Lines[2] <> 7) then { wrong # of syllables on line 2 }
    writeln(ErrorStr, 'the wrong number of syllables on line 2.')
  else if (Lines[3] <> 5) then { wrong # of syllables on line 3 }
    writeln(ErrorStr, 'the wrong number of syllables on line 3.')
  else
    writeln('Good Haiku!');
end;


var
  istr : string;
  numlines, loop : integer;
  lines : HaikuSyllableCounts;
begin
  assign(input,'haiku.in');
  reset(input);
  while (not eof) do
  begin
    {initialize variables}
    numlines:=0;
    for loop:=1 to 10 do
      lines[loop]:=0;
    {read in lines until a blank is found, or eof is reached}
    repeat
      istr:='';
      if (not eof) then
      begin
        readln(istr);
        if (length(istr) > 0) then
        begin
          numlines:=numlines+1;
          lines[numlines]:= CountSyllables(istr);
        end;
      end
    until eof or (length(istr) = 0);
    {Now, numlines has the number of lines in this student's haiku.
    Time to see if the haiku is valid.}
    CheckValidity(lines, numlines);
  end;
  close(input);
end.
