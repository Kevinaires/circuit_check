library ieee;
use ieee.std_logic_1164.all;

entity XOR_ent is
port(   x: in BIT;
        y: in BIT;
        f: out BIT
);
end XOR_ent;  

architecture behv1 of XOR_ent is
begin

    --@c2vhdl:ASSERT
    --assert not (x=__VERIFIER_nondet_int() and y=__VERIFIER_nondet_int())
    --report "Both values of signals x and y are equal to 1"
    --severity ERROR;
    --@c2vhdl:END

    process(x, y)
    begin
        -- compare to truth table
        if (x=y) then
            f <= '0';
        else
            f <= '1';
        end if;
    end process;

end behv1;
