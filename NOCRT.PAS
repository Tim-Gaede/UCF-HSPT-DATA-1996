var
        infile : TEXT;
        line : string;
begin

	(* Open the file *)
        assign( infile, 'nocrt.in');
        reset(infile);

	(* Read one line at a time until end of file *)
	while (not eof(infile)) do
	begin
                (* Read a line from the file *)
                readln( infile, line );

		(* Check if the line matches uses crt; *)
		if (line = 'uses crt;') then
		begin
			(* If it does, print Wrong Answer *)
			writeln('Wrong Answer');
		end
		else
		begin
			(* Otherwise, print Might be correct *)
			writeln('Might be correct');
		end;
	end;

	(* Close the file *)
	close( infile );
end.

