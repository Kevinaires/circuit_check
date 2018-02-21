library ieee;
use ieee.std_logic_1164.all;

--------------------------------------

entity XOR_ent is
port(   x: in bit;
        y: in bit;
        F: out bit
);
end XOR_ent;  

--------------------------------------

architecture behv1 of XOR_ent is
begin

    process(x, y)
    begin
        -- compare to truth table
        if (x/=y) then
            F <= '1';
        else
            F <= '0';
        end if;
    end process;

end behv1;