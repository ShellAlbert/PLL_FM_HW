///////////////////////////////////////////////////////////////////////////////
// Description: SPI (Serial Peripheral Interface) Master
//              Creates master based on input configuration.
//              Sends a byte one bit at a time on MOSI
//              Will also receive byte data one bit at a time on MISO.
//              Any data on input byte will be shipped out on MOSI.
//
//              To kick-off transaction, user must pulse i_TX_DV.
//              This module supports multi-byte transmissions by pulsing
//              i_TX_DV and loading up i_TX_Byte when o_TX_Ready is high.
//
//              This module is only responsible for controlling Clk, MOSI, 
//              and MISO.  If the SPI peripheral requires a chip-select, 
//              this must be done at a higher level.
//
// Note:        i_Clk must be at least 2x faster than i_SPI_Clk
//
// Parameters:  SPI_MODE, can be 0, 1, 2, or 3.  See above.
//              Can be configured in one of 4 modes:
//              Mode | Clock Polarity (CPOL/CKP) | Clock Phase (CPHA)
//               0   |             0             |        0
//               1   |             0             |        1
//               2   |             1             |        0
//               3   |             1             |        1
//              More: https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Mode_numbers
//              CLKS_PER_HALF_BIT - Sets frequency of o_SPI_Clk.  o_SPI_Clk is
//              derived from i_Clk.  Set to integer number of clocks for each
//              half-bit of SPI data.  E.g. 100 MHz i_Clk, CLKS_PER_HALF_BIT = 2
//              would create o_SPI_CLK of 25 MHz.  Must be >= 2
//
///////////////////////////////////////////////////////////////////////////////

module SPI_Master #(parameter SPI_MODE = 0, parameter CLKS_PER_HALF_BIT = 2)
(
   // Control/Data Signals,
   input        i_Rst_L,     // FPGA Reset
   input        i_Clk,       // FPGA Clock
   
   // TX (MOSI) Signals
   input [7:0]  i_TX_Byte,        // Byte to transmit on MOSI
   input        i_TX_DV,          // Data Valid Pulse with i_TX_Byte
   output reg   o_TX_Ready,       // Transmit Ready for next byte
   
   // RX (MISO) Signals
   output reg       o_RX_DV,     // Data Valid pulse (1 clock cycle)
   output reg [7:0] o_RX_Byte,   // Byte received on MISO

   // SPI Interface
   output reg o_SPI_Clk,
   input      i_SPI_MISO,
   output reg o_SPI_MOSI
);



  reg [$clog2(CLKS_PER_HALF_BIT*2)-1:0] r_SPI_Clk_Count;
  reg r_SPI_Clk;
  
  reg [4:0] r_SPI_Clk_Edges;
  reg r_Leading_Edge;
  reg r_Trailing_Edge;
  
  reg       r_TX_DV;
  reg [7:0] r_TX_Byte;

  reg [2:0] r_RX_Bit_Count;
  reg [2:0] r_TX_Bit_Count;

  // SPI Interface (All Runs at SPI Clock Domain)
  wire w_CPOL;     // Clock polarity
  wire w_CPHA;     // Clock phase
  
  // CPOL: Clock Polarity 时钟极性
  // CPOL=0 means clock idles at 0, leading edge is rising edge. 空闲时CLK=0,引领沿为上升沿
  // CPOL=1 means clock idles at 1, leading edge is falling edge.空闲时CLK=1,引领沿为下升沿 
  assign w_CPOL  = (SPI_MODE == 2) | (SPI_MODE == 3);

  // CPHA: Clock Phase 时钟相位
  // CPHA=0 means the "out" side changes the data on trailing edge of clock
  //              the "in" side captures data on leading edge of clock 上升沿输入锁存，下降沿输出

  
  // CPHA=1 means the "out" side changes the data on leading edge of clock
  //              the "in" side captures data on the trailing edge of clock 下降沿锁存输入，上升沿输出
  assign w_CPHA  = (SPI_MODE == 1) | (SPI_MODE == 3);


  // Purpose: Generate SPI Clock correct number of times when DV pulse comes
  always @(posedge i_Clk or negedge i_Rst_L)
  begin
    if (~i_Rst_L) //异步复位信号时，初始化清0
    	begin
      		o_TX_Ready      <= 1'b0;
		    r_SPI_Clk_Edges <= 0;
      		r_Leading_Edge  <= 1'b0;
      		r_Trailing_Edge <= 1'b0;
      		r_SPI_Clk       <= w_CPOL; // assign default state to idle state 默认时钟极性状态
      		r_SPI_Clk_Count <= 0;
    	end
    else
    	begin
			// Default assignments 为了保证上升/下降沿标志位只占一个时钟周期，每次都要清0.
      		r_Leading_Edge  <= 1'b0;
      		r_Trailing_Edge <= 1'b0;
      
      		if (i_TX_DV) //TxDataValid,当有数据要发送时,该脉冲只占一个CLK.
      			begin
        			o_TX_Ready      <= 1'b0; //发送完成标志位清0，等移出16个数据后再置位.
        			r_SPI_Clk_Edges <= 16;  // Total # edges in one byte ALWAYS 16，8个bits数据需要8个CLK，共16个上下沿.
      			end
      		else if (r_SPI_Clk_Edges > 0) //由于上面i_TX_DV只占一个CLK，所以下一个i_Clk时，就进入到这里执行了.
      			begin
        			o_TX_Ready <= 1'b0; //其实i_Tx_DV有效的那个时钟周期已经将清0了，这里不需要也行。
        			if (r_SPI_Clk_Count == CLKS_PER_HALF_BIT*2-1) //2*2-1=3.这里相当于对系统时钟进行4分频(0~3).
        				begin
          					r_SPI_Clk_Edges <= r_SPI_Clk_Edges - 1;//总共是16个clk,完成一次，这里减1.
          					r_Trailing_Edge <= 1'b1; //现在是下降沿
          					r_SPI_Clk_Count <= 0; //从0计到3，完成4分频后，再重新置0.
          					r_SPI_Clk       <= ~r_SPI_Clk; //时钟线反转
        				end
        			else if (r_SPI_Clk_Count == CLKS_PER_HALF_BIT-1)//2-1=1，这里是拿到4分频的中间位置.
        				begin
          					r_SPI_Clk_Edges <= r_SPI_Clk_Edges - 1;//总共是16个clk,完成一次，这里减1.
          					r_Leading_Edge  <= 1'b1;//现在是上升沿
          					r_SPI_Clk_Count <= r_SPI_Clk_Count + 1;//已完成一次，加1.
          					r_SPI_Clk       <= ~r_SPI_Clk; //时钟线反转
        				end
        			else
        				begin //对产生的r_spi_clk计数
          					r_SPI_Clk_Count <= r_SPI_Clk_Count + 1;
        				end
      			end  
      		else //当r_SPI_Clk_Edges减到0时，完成了16个CLK，此时发送结束，o_TX_Ready置1.
      			begin
        			o_TX_Ready <= 1'b1;
      			end
    end // else: !if(~i_Rst_L)
  end // always @ (posedge i_Clk or negedge i_Rst_L)


  // Purpose: Register i_TX_Byte when Data Valid is pulsed.
  // Keeps local storage of byte in case higher level module changes the data
  always @(posedge i_Clk or negedge i_Rst_L)
  begin
    if (~i_Rst_L)
    	begin
      		r_TX_Byte <= 8'h00;
      		r_TX_DV   <= 1'b0;
    	end
    else
      	begin
        	r_TX_DV <= i_TX_DV; // 1 clock cycle delay   延时一拍，打一拍
        	if (i_TX_DV)
        		begin
          			r_TX_Byte <= i_TX_Byte; //锁存数据，防止高层模块修改总线数据，这样输入只在这一个时钟周期内有效即可.
        		end
      	end // else: !if(~i_Rst_L)
 end // always @ (posedge i_Clk or negedge i_Rst_L) 


  // Purpose: Generate MOSI data
  // Works with both CPHA=0 and CPHA=1
  always @(posedge i_Clk or negedge i_Rst_L)
  begin
    if (~i_Rst_L)
    	begin
      		o_SPI_MOSI     <= 1'b0;
      		r_TX_Bit_Count <= 3'b111; // send MSb first
    	end
    else
    	begin
      		// If ready is high, reset bit counts to default
      		if (o_TX_Ready) //只要发送结束,o_Tx_Ready就被一直置1，此时复位发送计数器为7.当再次发送i_TX_DV有效时，o_TX_Ready被清0.
      			begin
        			r_TX_Bit_Count <= 3'b111;
      			end
      		// Catch the case where we start transaction and CPHA = 0
      		else if (r_TX_DV & ~w_CPHA)
      			begin
        			o_SPI_MOSI     <= r_TX_Byte[3'b111]; //移出最高位bit[7]
        			r_TX_Bit_Count <= 3'b110; //计数器减1为6
      			end
      		else if ((r_Leading_Edge & w_CPHA) | (r_Trailing_Edge & ~w_CPHA))
      			begin
        			r_TX_Bit_Count <= r_TX_Bit_Count - 1; //计数器减1
        			o_SPI_MOSI     <= r_TX_Byte[r_TX_Bit_Count]; //称出数据
        			//这里并没有控制o_SPI_MOSI何时停止，当r_TX_Bit_Count为0时,o_SPI_MOSI始终保持r_TX_Byte[0]的数据不变，就相当于停止了.
      			end
    	end
  end


  // Purpose: Read in MISO data.
  always @(posedge i_Clk or negedge i_Rst_L)
  begin
    if (~i_Rst_L) //异步清0
    	begin
      		o_RX_Byte      <= 8'h00;
      		o_RX_DV        <= 1'b0;
      		r_RX_Bit_Count <= 3'b111;
    	end
    else
    	begin
    		////每个i_Clk时钟周期都清0，这样的话，当有一个时钟周期o_RX_DV置1后，下一个时钟周期又会将其清0，保证只一个时钟周期有效.
      		// Default Assignments
      		o_RX_DV   <= 1'b0; 
      		if (o_TX_Ready) // Check if ready is high, if so reset bit count to default
      			begin
        			r_RX_Bit_Count <= 3'b111;
      			end
      		else if ((r_Leading_Edge & ~w_CPHA) | (r_Trailing_Edge & w_CPHA))
      			begin
        			o_RX_Byte[r_RX_Bit_Count] <= i_SPI_MISO;  // Sample data  移入数据
        			r_RX_Bit_Count            <= r_RX_Bit_Count - 1;  //每接收一个，计数器减1
        			if (r_RX_Bit_Count == 3'b000) //当接收计数器减到0时，表示接收到了8个数据，输出一个时钟周期的o_RX_DV脉冲用于触发其他模块.
        				begin
          					o_RX_DV   <= 1'b1;   // Byte done, pulse Data Valid
        				end
      			end
    	end
  end
  
  
  // Purpose: Add clock delay to signals for alignment.
  always @(posedge i_Clk or negedge i_Rst_L)
  begin
    if (~i_Rst_L) 
    	begin
      		o_SPI_Clk  <= w_CPOL;//异步复位时，输出默认极性(默认为高或低)
    	end
    else
      	begin
        	o_SPI_Clk <= r_SPI_Clk;//将内部寄存器时钟送到外部端口上，同步到系统时钟i_Clk.
      	end // else: !if(~i_Rst_L)
  end // always @ (posedge i_Clk or negedge i_Rst_L)
  

endmodule // SPI_Master