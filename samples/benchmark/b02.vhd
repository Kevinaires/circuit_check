entity b02 is
port(reset : in bit;
	clock : in bit;
	linea : in bit;
	u     : out bit
    );
end b02;

architecture BEHAV of b02 is

	signal A:integer:=0; --constant
	signal B:integer:=1; --constant
	signal C:integer:=2; --constant
	signal D:integer:=3; --constant
	signal E:integer:=4; --constant
	signal F:integer:=5; --constant
	signal G:integer:=6; --constant

begin
    process(reset,clock)

	variable stato:integer; --range 6 downto 0;

    begin

        if reset='1' then
           stato:=A;
           u<='0';
        elsif clock'event and clock='1' then
           case stato is

                when A =>
                     stato:=B;
                     u<='0';
                when B =>
                     if linea='0' then
                        stato:=C;
                     else
                        stato:=F;
                     end if;
                     u<='0';
                when C =>
                     if linea='0' then
                        stato:=D;
                     else
                        stato:=G;
                     end if;
                     u<='0';
                when D =>
                     stato:=E;
                     u<='0';
                when E =>
                     stato:=B;
                     u<='1';
                when F =>
                     stato:=G;
                     u<='0';
                when G =>
                     if linea='0' then
                        stato:=E;
                     else
                        stato:=A;
                     end if;
                     u<='0';

           end case;
        end if;

    end process;
end BEHAV;
