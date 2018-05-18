entity seq1 is
port (in1, in2: in bit;
      reset: in bit;
      out1, out2: out bit);
end seq1;

architecture behave of seq1 is
begin
  process (in1,in2,reset)
   variable st: bit;
   begin
    if reset=0 then st:=0;
                    out1 <= 0;
                    out2 <= 0;
    elsif (in1=0 and in2=0 and st=0) then out2 <= 1;
    elsif (in1=1 and in2=1 and st=1) then out1 <= 1;
    end if;
    st:=not st;
   end process;
end behave;
