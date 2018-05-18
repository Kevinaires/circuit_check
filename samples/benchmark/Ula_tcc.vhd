library ieee;
use ieee.std_logic_1164.all;

ENTITY Ula_tcc IS
PORT(A,B,Binvertido,Op1:IN BIT;
	  Resultado:OUT BIT);
END Ula_tcc;

ARCHITECTURE Ula_tcc_behavl OF Ula_tcc IS
SIGNAL and_port: bit;
SIGNAL or_port: bit;
SIGNAL mux2x1: bit;
BEGIN
	PROCESS(A,B,Binvertido,Op1)
	BEGIN
		--PORTA AND
		and_port <= A AND mux2x1;
		--PORTA OR
		or_port <= A OR mux2x1;
		--INVERSOR
		IF(Binvertido = '0') THEN
			mux2x1 <= B;
		ELSE
			mux2x1 <= NOT B;
		END IF;
		--mux4x1
		IF(Op1 = '0') THEN
			Resultado <= and_port;
		ELSIF(Op1 = '1') THEN
			Resultado <= or_port;
		END IF;
	END PROCESS;
END Ula_tcc_behavl;
