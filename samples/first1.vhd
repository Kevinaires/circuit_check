-- first1.vhd
-- First Example File
--
-- The vhdl source must contain both the entity and the architecture
-- declaration. You can put comments almost in any place and they will be
-- copied in the translation.
-- The name of the entity is used for the name of the output files.

-- The entity starts here:

entity first1_e is
  port(
      in1: in bit;
      in2: in std_ulogic_vector( 3 downto 0 );
      ctl, bogus : in integer;
      out1 : out std_ulogic_vector( 3 downto 0 )
      );
end first1_e;


-- Now comes the architecture. This examples really does nothing useful; it
-- is just a demostration of the program behaviour and not of my VHDL skills...

architecture first1_a of first1_e is

-- There are just a few VHDL types that are recognized,
-- and only IN and OUT directions are accepted.
signal aaa, bbb: std_ulogic_vector( 3 downto 0 );
signal c8: std_ulogic_vector( 1 downto 0 ) := '0';

begin
-- In the architecture body you can place your code.

-- Some concurrent statements:
 aaa <= in2;
 bbb <= in1 & in1 & in1;

-- A sequential process
  myproc1: process (bbb, in1)
  begin
   if in1=1 and bbb="101" then out1<=aaa;
   else out1<=bbb;
  end if;
  end process;

end first1_a;
