{-----------------------------------------------------------------
Program Name
   Predict.pas

Programer
   Chris Stadler May 2, 1996

Function
   Solution for Predict problem for HS contest.

Input
   File off disk (Predict.in)

Output
   Screen
-----------------------------------------------------------------}

program predictor;

var infile:       text;                      {File to read from disk}
    dayomonth:    array[1..12] of integer;   {Number of days in that month}
    day:          integer;                   {Day Counter    }
    month:        integer;                   {Month Counter}

begin
    dayomonth[1] := 31; dayomonth[7] := 31;  {Loading in # of days}
    dayomonth[2] := 28; dayomonth[8] := 31;  {In Each month       }
    dayomonth[3] := 31; dayomonth[9] := 30;
    dayomonth[4] := 30; dayomonth[10]:= 31;
    dayomonth[5] := 31; dayomonth[11]:= 30;
    dayomonth[6] := 30; dayomonth[12]:= 31;

    assign(infile, 'predict.in');            {Setup Infile as a }
    reset(infile);                           {Read File}

    readln(infile,day);
    while day<>0 do
      begin
        month := 1;
        if day > 28 then
          begin
            month := 2;                      {Checks day=31 case}
            day := day - 31;
          end;
        while month<12 do
          begin
            day := day + 29;                  {Increment Day Counter}
            if day > dayomonth[month] then      {\  adjust day and  }
              begin                             { | month for when  }
                day := day - dayomonth[month];  { | month changes   }
                month := month + 1;             { |                 }
              end;                              {/                  }
            writeln('Full Moon On ',month,'-',day);
          end;
        writeln;
        readln(infile,day);
      end;
    close(infile);
end.