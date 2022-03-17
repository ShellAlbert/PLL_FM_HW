


module traffic_light(clk,rst_n,c,light_farm,light_highway);

parameter HGRE_FRED=2’b00, //Highway green and farm red
HYEL_FRED=2’b01, //Highway yellow and farm red
HRED_FGRE=2’b10, //Highway red and farm green
HRED_FYEL=2’b11; //Highway red and farm yellow

 
endmodule

