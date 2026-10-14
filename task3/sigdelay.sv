module sigdelay(
    input logic clk, rst, wr, rd,
    input logic [8:0] offset, 
    input logic [7:0] mic_signal,
    output logic [7:0] delayed_signal
);
    logic [8:0] wr_addr;
    counter address (.clk(clk), .rst(rst), .ld(1'b0), .v(9'd1), .count(wr_addr));

    ram stored (.clk(clk), .wr_en(wr), .rd_en(rd), .wr_addr(wr_addr), .rd_addr(wr_addr+offset), .din(mic_signal), .dout(delayed_signal));



endmodule

