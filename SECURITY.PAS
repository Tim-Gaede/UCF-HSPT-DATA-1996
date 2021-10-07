(*=========================================================================

    security.pas  -  Don Cross, 27 April 1996.

    Turbo Pascal judge solution to SECURITY problem from
    1996 High School Programming Tournament.

=========================================================================*)

const
    MaxPeople = 20;
    MaxPlaces = 20;

type
    NameString = string [80];
    PlaceList = array [1..MaxPlaces] of NameString;

    SecurityEntry =
        record
            person:     NameString;
            numPlaces:  integer;
            places:     PlaceList;
        end;

    SecurityDatabase = array [1..MaxPeople] of SecurityEntry;

var
    infile: text;
    i, j, n, m, p: integer;
    sd: SecurityDatabase;
    c: char;
    pl, pltemp: SecurityEntry;
    person: NameString;


procedure FindPerson ( person: NameString; var pl: SecurityEntry );
var   i: integer;
begin
    for i := 1 to n do begin
        if sd[i].person = person then begin
            pl := sd[i];
            exit;
        end;
    end;
end;


procedure Intersect ( a, b: SecurityEntry; var c: SecurityEntry );
var
    i, j: integer;
begin
    c.numPlaces := 0;

    for i := 1 to a.numPlaces do begin
        for j := 1 to b.numPlaces do begin
            if a.places[i] = b.places[j] then begin
                INC(c.numPlaces);
                c.places[c.numPlaces] := a.places[i];
            end;
        end;
    end;
end;


begin
    assign ( infile, 'security.in' );
    reset ( infile );

    (* Read in the security database *)
    readln ( infile, n );    (* number of people in the database *)
    for i := 1 to n do begin
        readln ( infile, sd[i].person );
        j := 1;
        sd[i].places[j] := '';
        while not eoln(infile) do begin
            read ( infile, c );
            if c = ' ' then begin
                INC(j);
                sd[i].places[j] := '';
            end else begin
                sd[i].places[j] := sd[i].places[j] + c;
            end;
        end;

        readln ( infile );
        if sd[i].places[j] = '' then DEC(j);   (* handle any trailing space *)
        sd[i].numPlaces := j;
    end;

    (* now handle the security access requests *)

    readln ( infile, m );
    for i := 1 to m do begin
        readln ( infile, p );
        pl.numPlaces := 0;

        for j := 1 to p do begin
            readln ( infile, person );
            if j = 1 then begin
                FindPerson ( person, pl );
            end else begin
                FindPerson ( person, pltemp );
                Intersect ( pl, pltemp, pl );
            end;
        end;

        if pl.numPlaces = 0 then
            writeln ( 'Do not grant access to any areas.' )
        else begin
            write ( 'Grant access to ' );
            for j := 1 to pl.numPlaces do begin
                if j > 1 then write(', ');
                write ( pl.places[j] );
            end;
            writeln ( '.' );
        end;
    end;

    close (infile);
end.


(*--- end of file security.pas ---*)