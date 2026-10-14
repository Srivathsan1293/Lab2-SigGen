module singen (
    input logic [7:0] incr,
    input logic rst, en, clk,
    output logic [7:0] dout;
);

    logic [7:0] addr;
    counter counter (.clk(clk), .rst(rst), .ld(en), .v(incr), .count(addr));

    rom sinevals (.clk(clk), .addr(addr), .dout(dout));
endmodule