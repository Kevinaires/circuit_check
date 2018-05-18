library ieee;
use ieee.std_logic_1164.all;

entity NAND_ent is
port(   x: in BIT;
        y: in BIT;
        f: out BIT

);
end NAND_ent;  

architecture behav1 of NAND_ent is
begin

    --@c2vhdl:ASSERT
    --assert not (x=__VERIFIER_nondet_int() and y=__VERIFIER_nondet_int())
    --report "Both values of signals x and y are equal to 1"
    --severity ERROR;
    --@c2vhdl:END

    process(x, y)
    begin
        -- compare to truth table
        if ((x='1') and (y='1')) then
            f <= '0';
        else
            f <= '1';
        end if;
    end process;

end behav1;
