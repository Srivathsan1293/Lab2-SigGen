# Task 3: Audio Signal Delay Capture

## Overview

This task implements an audio signal delay system using a dual-port RAM configuration. The capture circuit writes audio samples from Vbuddy's microphone to successive memory locations, while simultaneously reading back from an address offset from the write position. This creates a time-delayed version of the original audio signal. The delay duration is controlled by a rotary encoder on Vbuddy via the `offset` parameter.

## Files Included

### 1. Dual-Port RAM Module (`ram.sv`)

```verilog
module ram #(
    parameter   ADDRESS_WIDTH = 9, 
                    DATA_WIDTH = 8
)(
    input logic clk, wr_en, rd_en,
    input logic [ADDRESS_WIDTH - 1:0] wr_addr,   
    input logic [ADDRESS_WIDTH - 1:0] rd_addr,
    input logic [DATA_WIDTH - 1 : 0] din, 
    output logic [DATA_WIDTH - 1 : 0] dout
);
    logic [DATA_WIDTH - 1 : 0 ] ram_array[2**ADDRESS_WIDTH - 1 : 0];

    always_ff @(posedge clk) begin
        if (wr_en == 1'b1) begin
            ram_array[wr_addr] <= din;
        end
        if (rd_en == 1'b1) begin
            dout <= ram_array[rd_addr]; 
        end
    end
    
endmodule 
```

### 2. Counter Module (`counter.sv`)

```verilog
module counter #(
  parameter WIDTH = 9
)(
  // interface signals
  input  logic             clk,      // clock
  input  logic             rst,      // reset
  input  logic             ld,       // load counter from data
  input  logic [WIDTH-1:0] v,        // value to preload
  output logic [WIDTH-1:0] count     // count output
);

always_ff @ (posedge clk)
  if (rst) count <= {WIDTH{1'b0}};
  else     count <= ld ? v : count + {{WIDTH-1{1'b0}},1'b1};
endmodule
```

### 3. Signal Delay Module (`sigdelay.sv`)

```verilog
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
```

### 4. Testbench (`sigdelay_tb.cpp`)

```cpp
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsigdelay.h"

#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 1000000
#define ADDRESS_WIDTH 9
#define RAM_SZ pow(2,ADDRESS_WIDTH)

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int tick;       // each clk cycle has two ticks for two edges

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vsigdelay* top = new Vsigdelay;
  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("sigdelay.vcd");
  
  // init Vbuddy
  if (vbdOpen()!=1) return(-1);
  vbdHeader("L2T3:Delay");
  //vbdSetMode(1);        // Flag mode set to one-shot

  // initialize simulation input 
  top->clk = 1;
  top->rst = 0;
  top->wr = 1;
  top->rd = 1;
  top->offset = 64;
  
  // intialize variables for analogue output
  vbdInitMicIn(RAM_SZ);

  // run simulation for MAX_SIM_CYC clock cycles
  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {
    // dump variables into VCD file and toggle clock
    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval ();
    }
    top->mic_signal = vbdMicValue();
    top->offset = abs(vbdValue());     // adjust delay by changing incr

    // plot RAM input/output, send sample to DAC buffer, and print cycle count
    vbdPlot(int (top->mic_signal), 128, 255);
    vbdPlot(int (top->delayed_signal), 0, 127);
    vbdCycle(simcyc);

    // either simulation finished, or 'q' is pressed
    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
      exit(0);
  }

  vbdClose();     // ++++
  tfp->close(); 
  printf("Exiting\n");
  exit(0);
}
```

## Delay Mechanism

### How Signal Delay Works

The signal delay system uses a RAM with offset-based addressing:

1. **Continuous Writing**: Audio samples from microphone are written to address `wr_addr` (which increments via counter)
2. **Offset-Based Reading**: Data is read from address `rd_addr = wr_addr + offset`
3. **Delay Effect**: By reading from an offset address, the output appears delayed relative to the input

### Delay Control via Offset

The delay amount is controlled by the 9-bit offset value:

- **Initial offset**: 64 samples (default)
- **Real-time adjustment**: Rotary encoder adjusts offset via `vbdValue()` wrapped in `abs()`
- **Offset range**: 0 to 511 samples (for 9-bit addressing)

### Memory Configuration

- **Address width**: 9 bits (512 locations)
- **Data width**: 8 bits per sample
- **Write enable**: Always asserted for continuous streaming capture
- **Read enable**: Always asserted for delayed output generation

## Audio Capture Mechanism

### Microphone Buffer Initialization

```cpp
vbdInitMicIn(RAM_SZ);
```

This reserves a buffer of `RAM_SZ = 2^9 = 512` audio samples on Vbuddy. The buffer management is automatic:

- When samples are exhausted, Vbuddy captures another block
- Samples are returned sequentially via `vbdMicValue()`

### Audio Sample Retrieval

```cpp
top->mic_signal = vbdMicValue();
```

This function provides continuous audio sample streaming from the hardware microphone to the simulation model.

## Display Mechanism

The testbench displays both the captured audio signal and the delayed version on Vbuddy:

```cpp
vbdPlot(int (top->mic_signal), 128, 255);   // Plot input audio (normalized to 0-255)
vbdPlot(int (top->delayed_signal), 0, 127);  // Plot delayed output (inverted range)
```

The two plots show:
- **Input signal**: Current microphone sample being captured
- **Delayed signal**: Sample from RAM read with offset applied

## Challenge Completed: ✓

The implementation successfully demonstrates:
1. Dual-port RAM configuration using separate write/read addresses
2. Time-delayed audio signal generation via address offset
3. Real-time delay adjustment through rotary encoder
4. Continuous audio capture from Vbuddy microphone
5. Automatic buffer management on the hardware side

