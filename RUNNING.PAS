(*=========================================================================

    running.pas  -  Don Cross, 2 May 1996.

    Sample solution to the RUNNING program from the
    1996 UCF High School Programming Tournament.

==========================================================================*)

const
    MaxRunners = 50;
    Distance = 5000.0;

type
    NameString = string[80];


function TwoDig ( x: LongInt ): string;
begin
    TwoDig := chr ( ord('0') + x div 10 ) +
              chr ( ord('0') + x mod 10 );
end;


var
    infile: text;
    numRunners, i: integer;
    name, bestName: string;
    speed, distanceLeft: real;
    bestTime, runTime, restTime, finishTime: real;
    Cycles, Extra, TotalTime: real;
    raceNo: integer;
    min, sec: LongInt;

begin
    assign ( infile, 'running.in' );
    reset ( infile );
    raceNo := 0;

    repeat
        readln ( infile, numRunners );
        bestTime := 1.0e+20;

        if numRunners > 0 then begin
            for i := 1 to numRunners do begin
                readln ( infile, name );
                readln ( infile, speed );
                readln ( infile, runTime );
                readln ( infile, restTime );

                Cycles := Distance / (speed * runTime);
                Extra := Cycles;
                Cycles := trunc(Cycles);
                Extra := Extra - Cycles;
                TotalTime := Cycles * (runTime + restTime);
                distanceLeft := Distance - Cycles*Speed*runTime;
                TotalTime := TotalTime + DistanceLeft/Speed;

                if totalTime < bestTime then begin
                    bestTime := totalTime;
                    bestName := name;
                end;

            end;

            INC (raceNo);

            min := trunc ( bestTime / 60.0 );
            sec := round ( bestTime - 60*min );

            writeln ( 'Race ', raceNo, ': The winner is ', bestName,
                ' with a time of ', TwoDig(min), ':', TwoDig(sec), '.' );
        end;
    until numRunners = 0;

    close ( infile );
end.


(*--- end of file running.pas ---*)