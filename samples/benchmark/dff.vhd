library ieee ;
use ieee.std_logic_1164.all;

entity dff is
port(data_in:        in STD_ULOGIC;
     clock:          in STD_ULOGIC;
     data_out:       out STD_ULOGIC
);
end dff;

architecture behv of dff is
begin

    --@c2vhdl:ASSERT
    --assert not (data_in=__VERIFIER_nondet_int() and clock=__VERIFIER_nondet_int())
    --report "Both values of signals x and y are equal to 1"
    --severity ERROR;
    --@c2vhdl:END

    process(data_in, clock)
    begin
        -- clock rising edge
        if (clock='1' and clock'event) then
            data_out <= data_in;
        end if;
    end process;        
end behv;
