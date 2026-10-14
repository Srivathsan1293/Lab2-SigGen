module singen (
    input logic [7:0] incr,
    input logic [7:0] freq,
    input logic rst, en, clk,
    output logic [7:0] dout
);

    logic [7:0] addr;
    counter counter (.clk(clk), .rst(rst), .ld(en), .v(incr), .count(addr));

    logic [7:0] adj_addr;

    assign adj_addr = addr * freq;
    rom sinevals (.clk(clk), .addr(adj_addr), .dout(dout));
endmodule


