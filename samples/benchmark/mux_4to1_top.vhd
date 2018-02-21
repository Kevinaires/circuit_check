library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity mux_4to1_top is
    Port ( SEL : in  BIT_VECTOR (1 downto 0);     -- select input
           A   : in  BIT_VECTOR (3 downto 0);     -- inputs
           X   : out BIT);                        -- output
end mux_4to1_top;

architecture Behavioral of mux_4to1_top is
begin
with SEL select
    X <= A(0) when "00",
         A(1) when "01",
         A(2) when "10",
         A(3) when "11",
         '0'  when others;
end Behavioral;