library ieee;
use ieee.std_logic_1164.all;

entity NOR_ent is
port(   x: in bit;
        y: in bit;
        F: out bit
);
end NOR_ent;  


architecture NOR_arch of NOR_ent is
begin
    
    process(x, y)
    begin
        -- compare to truth table
        if ((x='0') and (y='0')) then
            F <= '1';
        else
            F <= '0';
        end if;
    end process;

end NOR_arch;
