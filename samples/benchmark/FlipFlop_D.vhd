library ieee;
use ieee. std_logic_1164.all;
use ieee. std_logic_arith.all;
use ieee. std_logic_unsigned.all;

entity FlipFlop_D is
PORT(D,CLK,RST: in std_ulogic;
     Q: out std_ulogic);
end FlipFlop_D;

architecture behavioral of FlipFlop_D is
begin
  process(RST,CLK)
    begin
      if(RST='1')then
        Q<='0';
      elsif(CLK='1' and CLK'EVENT) then
        Q<=D;
      end if; 
  end process;
end behavioral;
