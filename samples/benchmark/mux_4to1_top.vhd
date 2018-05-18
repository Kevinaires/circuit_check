library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

ENTITY mux_4to1_top IS
PORT(SEL: IN STD_ULOGIC_VECTOR(1 DOWNTO 0);
     X: IN STD_ULOGIC_VECTOR(1 DOWNTO 0);
     A: OUT STD_ULOGIC_VECTOR(3 DOWNTO 0)
	 );
END mux_4to1_top;

architecture Behavioral of mux_4to1_top is
begin

    --@c2vhdl:ASSERT
    --assert not (SEL=__VERIFIER_nondet_int() and A=__VERIFIER_nondet_int())
    --report "Both values of signals x and y are equal to 1"
    --severity ERROR;
    --@c2vhdl:END

with SEL select
    X <= A(0) when "00",
         A(1) when "01",
         A(2) when "10",
         A(3) when "11",
         '0'  when others;
end Behavioral;
