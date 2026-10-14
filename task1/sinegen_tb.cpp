#include "Vsingen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
	Verilated::commandArgs(argc, argv);
	Vsingen* top = new Vsingen;
	Verilated::traceEverOn(true);
	VerilatedVcdC* tfp = new VerilatedVcdC;
	top->trace(tfp, 99);
	tfp->open("singen.vcd");

	if (vbdOpen() != 1) return(-1);
	vbdHeader("Lab 2: sinegen");
        vbdSetMode(1);
        
	top->clk = 1;
	top->rst = 1;
	top->en = 0;
        top->incr = 1;
        top->freq = 1;

	for (int i = 0; i < 1000000; i++) {
		// 1. ALWAYS dump time, toggle the clock, and evaluate the model
		for (int clk = 0; clk < 2; clk++) {
			tfp->dump(2*i + clk);
			top->clk = !top->clk;
			top->eval();
		}

		vbdPlot(top->dout, 0x00, 0xFF);
		vbdCycle(i+1);

		// 2. Change the reset stimulus so it doesn't interrupt us at i==15
		top->rst = (i < 2) | (i == 15);
		top->en = vbdFlag(); // decides where to reset value to what ever is next line. 
                 // makes sure when the frequency changes you keep the same x. 
		  top->freq = vbdValue(); // sets new value
		 
		if ((Verilated::gotFinish()) || (vbdGetkey()=='q'))  exit(0);
	}
	vbdClose();
	tfp->close();
	exit(0);
}
