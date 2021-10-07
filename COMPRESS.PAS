(************************************************************************)
(*   Palindrome Compression                                             *)
(*   for the 1996 High School Programming Contest                       *)
(************************************************************************)

var
     fp : TEXT;
     s : string;
     iFront, iBack:integer;
begin
     assign(fp, 'compress.in');
     reset(fp);

     while (not(eof(fp))) do
     begin
       (* read a string from the input *)
           readln(fp,s);

           iFront := 1;
           iBack := Length(s);

          (* Scan the word from both ends until it is not *)
          (* symmetric or the middle is reached.          *)
          while ((s[iFront] = s[iBack]) and
               (iBack > iFront)) do
               begin
                      dec(iBack);
                      inc(iFront);
               end;

          (* Determine if this is an even palindrome, an odd *)
          (* palindrome, or not a palindrome, and print the  *)
          (* results.                                        *)
          if (iBack>iFront) then
          begin
             (* it's not a palindrome *)
             writeln(s);
          end
          else if (iBack = iFront) then
          begin
               (* it's an odd palindrome -- truncate the string *)
               (* after the first half and then output with '~' *)
               s := copy(s,1,iFront);
               writeln(s,'~');
          end
          else  (* iBack < iFront *)
          begin
                (* It's and even palindrome -- truncate the string *)
                (* and output '*'                                  *)
                s := copy(s,1,iFront-1);
                writeln( s,'*' );
          end;
     end;

     close(fp);

end.
