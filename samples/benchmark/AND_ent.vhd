library ieee;
use ieee.std_logic_1164.all;

entity AND_ent is
port(   x: in bit;
        y: in bit;
        f: out bit
);
end AND_ent;

architecture behav1 of AND_ent is
begin

    --@c2vhdl:ASSERT
    --assert not (x=__VERIFIER_nondet_int() and y=__VERIFIER_nondet_int())
    --report "Both values of signals x and y are equal to 1"
    --severity ERROR;
    --@c2vhdl:END

    process(x, y)
    begin
        if ((x='1') and (y='1')) then
            f <= '1';
        else
            f <= '0';
        end if;
    end process;

end behav1;
