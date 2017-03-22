LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY shift_left IS
PORT(a: IN STD_ULOGIC_VECTOR(3 DOWNTO 0);
     s: OUT STD_ULOGIC_VECTOR(3 DOWNTO 0)
	 );
END shift_left;

ARCHITECTURE behavior OF shift_left IS
BEGIN
	process(a)
	begin
		for i in 0 to 2 loop
			s(i) <= a(i+1);
		end loop;
		s(3) <= '0';
	end process;
END behavior;

