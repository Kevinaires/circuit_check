library ieee;
use ieee.std_logic_1164.all;

entity AND_ent is
port(   x: in bit;
        y: in bit;
        F: out bit
);
end AND_ent;

--------------------------------------------------

architecture behav1 of AND_ent is
begin

    process(x, y)
    begin
        -- compare to truth table
        if ((x='1') and (y='1')) then
            F <= '1';
        else
            F <= '0';
        end if;
    end process;

    --@c2vhdl:ASSERT
    --assert  (S= '1' and R= '1')
    --report "Both values of signals S and R are equal to '1'"
    --severity ERROR;
    --@c2vhdl:



    --@c2vhdl:ASSERT
    --assert  (S= '0' and R= '0')
    --report "Both values of signals S and R are equal to '1'"
    --severity ERROR;
    --@c2vhdl:

end behav1;
