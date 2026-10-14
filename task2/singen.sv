module singen (
    input logic [7:0] incr,
    input logic [7:0] off,
    input logic rst, en, clk,
    output logic [7:0] dout1,
    output logic [7:0] dout2
);

    logic [7:0] addr;
    counter counter (.clk(clk), .rst(rst), .ld(en), .v(incr), .count(addr));

    rom sinevals (.clk(clk), .addr1(4*addr), .dout1(dout1), .addr2(4*(addr+off)), .dout2(dout2));
endmodule


