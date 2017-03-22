entity nome is
port (
      A: in bit;
      B: out bit
     );
end nome;

architecture logica of nome is
begin
   process(A)
      begin
   	if(A = 1)then
   	   B <= 0;
   	else
   	   B <= 1;
   	end if;
   end process;
end logica; 
