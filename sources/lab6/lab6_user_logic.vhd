-- MIT License
--
-- Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in all
-- copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
-- SOFTWARE.

---------------------------------------------------------------------------------- 
-- Module Name:    lab2_user_logic
-- Description:  8 Bit Adder with vio input capabilities
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity lab2_user_logic is
    Port ( ain : in  STD_LOGIC_VECTOR (7 downto 0);
           bin : in  STD_LOGIC_VECTOR (7 downto 0);
           ain_vio : in  STD_LOGIC_VECTOR (7 downto 0);
           bin_vio : in  STD_LOGIC_VECTOR (7 downto 0);
           Clk : in  STD_LOGIC;
           sel : in  STD_LOGIC;
           Reset_n : in  STD_LOGIC;
           result : out  STD_LOGIC_VECTOR (8 downto 0));
end lab2_user_logic;

architecture Behavioral of lab2_user_logic is

signal ain_i : std_logic_vector (7 downto 0);
signal bin_i : std_logic_vector (7 downto 0);

begin

    ain_i <= ain_vio WHEN sel='1' ELSE ain; 
    bin_i <= bin_vio WHEN sel='1' ELSE bin; 

    ADD_PROC : process( Clk ) is
    begin
    
      if Clk'event and Clk = '1' then
        if Reset_n = '0' then
          result <= (others => '0');
        else
          result <= ('0' & ain_i) +('0' & bin_i);
        end if;
      end if;
    
    end process ADD_PROC;

end Behavioral;

