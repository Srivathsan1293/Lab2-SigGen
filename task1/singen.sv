module singen (
    input logic [7:0] incr,
    input logic [7:0] freq,
    input logic rst, en, clk,
    output logic [7:0] dout
);

    logic [7:0] addr;
    counter counter (.clk(clk), .rst(rst), .ld(en), .v(incr), .count(addr));

    logic [7:0] adj_addr;
    logic [7:0] cur_freq;

always_ff @(posedge clk) begin
    if (rst) 
        cur_freq <= 8'd1;     // Set a default frequency on reset
    else if (en) 
        cur_freq <= freq;     // Lock in the new frequency when 'en' is high
end
    assign adj_addr = addr * cur_freq;
    rom sinevals (.clk(clk), .addr(adj_addr), .dout(dout));
endmodule


