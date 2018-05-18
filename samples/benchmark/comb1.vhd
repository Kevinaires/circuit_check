entity comb1 is
port (in1, in2:in integer;
      sel :in integer range 0 to 3;
      out1 :out integer);
end comb1;

architecture behave of comb1 is
begin
  process (in1, in2, sel)
     begin
        case sel is
          when 0 => out1 <= in1+in2;
          when 1 => out1 <= in1-in2;
          when 2 => out1 <= in1*in2;
          when 3 => out1 <= 0;
        end case;
     end process;
end behave;
