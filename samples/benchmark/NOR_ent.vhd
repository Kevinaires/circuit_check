library ieee;
use ieee.std_logic_1164.all;

entity NOR_ent is
port(   x: in BIT;
        y: in BIT;
        f: out BIT
);
end NOR_ent;  

architecture NOR_arch of NOR_ent is
begin

    --@c2vhdl:ASSERT
    --assert not (x=__VERIFIER_nondet_int() and y=__VERIFIER_nondet_int())
    --report "Both values of signals x and y are equal to 1"
    --severity ERROR;
    --@c2vhdl:END

    process(x, y)
    begin
        -- compare to truth table
        if ((x='0') and (y='0')) then
            f <= '1';
        else
            f <= '0';
        end if;
    end process;

end NOR_arch;
