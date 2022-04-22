module power_on_reset(clk,reset);

input clk;
output reset;

reg [31:0] count = 0;

always @(posedge clk) 
begin
		if(count ==     32'd10000005) 
			count <= count;
		else
			count <= count + 1'b1;
end

assign reset = (count <32'd10000000) ? 1'b1 : 1'b0; // power on reset high for 2000ms

endmodule