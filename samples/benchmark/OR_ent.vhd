library ieee;
use ieee.std_logic_1164.all;

entity OR_ent is
port(   x: in bit;
        y: in bit;
        f: out bit
);
end OR_ent;  

architecture OR_arch of OR_ent is
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
            f <= '0';
        else
            f <= '1';
        end if;
    end process;

end OR_arch;
