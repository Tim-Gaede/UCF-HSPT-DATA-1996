(*=========================================================================

    cards.pas  -  Don Cross, 27 April 1996.

    Turbo Pascal sample solution to CARDS problem from
    1996 High School Programming Tournament.

=========================================================================*)

(* We use sets to represent the deck of cards. *)
(* There is one set for each suit. *)
(* Jack=11, Queen=12, King=13, Ace=14 *)

type
    FaceValue = 2..14;
    SuitSet = set of FaceValue;
    Suit = (Spade, Heart, Diamond, Club, Nothing);

var
    infile: text;
    Deck: array [Suit] of SuitSet;
    cardFace: FaceValue;
    cardSuit: Suit;
    newDataSet: boolean;
    setCounter: integer;
    SuitName: array [Suit] of string[10];


function ReadCard ( var f: FaceValue; var s: Suit ): boolean;
var  c: char;
begin
    repeat
        while eoln(infile) do begin
            if eof(infile) then begin
                ReadCard := FALSE;
                exit;
            end;
            readln(infile);
        end;

        read ( infile, c );
    until c <> ' ';

    case c of
        '2'..'9':  f := ord(c) - ord('0');
        'T':       f := 10;
        'J':       f := 11;
        'Q':       f := 12;
        'K':       f := 13;
        'A':       f := 14;
        else       f := 2;
    end;

    read ( infile, c );
    case c of
        'H':  s := Heart;
        'S':  s := Spade;
        'D':  s := Diamond;
        'C':  s := Club;
        else  s := Nothing;
    end;

    ReadCard := TRUE;
end;


function CardChar ( f: FaceValue ): char;
begin
    case f of
        2..9:  CardChar := chr ( f + ord('0') );
        10:    CardChar := 'T';
        11:    CardChar := 'J';
        12:    CardChar := 'Q';
        13:    CardChar := 'K';
        14:    CardChar := 'A';
        else   CardChar := '?';
    end;
end;


procedure Report;
var
    s: Suit;
    f: FaceValue;
begin
    writeln ( 'Data set ', setCounter, ':' );
    INC (setCounter);
    for s := Spade to Club do begin
        write ( '   ', SuitName[s], ':' );
        for f := 2 to 14 do begin
            if not (f in Deck[s]) then
                write ( ' ', CardChar(f) );
        end;
        writeln;
    end;
    writeln;
end;


begin
    SuitName[Spade]   := 'Spades';
    SuitName[Heart]   := 'Hearts';
    SuitName[Diamond] := 'Diamonds';
    SuitName[Club]    := 'Clubs';

    assign ( infile, 'cards.in' );
    reset ( infile );

    newDataSet := TRUE;
    setCounter := 1;

    while ReadCard (cardFace, cardSuit) do begin
        if newDataSet then begin
            Deck[Heart]    := [];
            Deck[Spade]    := [];
            Deck[Club]     := [];
            Deck[Diamond]  := [];
            newDataSet := FALSE;
        end;

        if cardSuit = Nothing then begin
            newDataSet := TRUE;
            Report;
        end else begin
            Deck[cardSuit] := Deck[cardSuit] + [cardFace];
        end;
    end;

    close (infile);
end.


(*--- end of file cards.pas ---*)
