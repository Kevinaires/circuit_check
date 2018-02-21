library ieee;
use ieee.std_logic_1164.all;
entity soma04 is 
	port(cin: in bit;
		  a,b: in bit_vector (3 downto 0);
		  cout: out bit;
		  s: out bit_vector (3 downto 0));
	end soma04;

architecture arch_soma04 of soma04 is 
begin 
	process (a,b,cin)
	variable soma:bit_vector(3 downto 0);
	variable c: bit;
	begin
		c:=cin;
			for i in 0 to 3 loop
				soma(i):=a(i) xor b(i) xor c;
				c:= (a(i) and b(i)) or ((a(i) xor b(i)) and c);
			end loop;
			cout<=c;
			s<=soma;
	end process;
end arch_soma04;
