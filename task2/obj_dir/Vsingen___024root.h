// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsingen.h for the primary calling header

#ifndef VERILATED_VSINGEN___024ROOT_H_
#define VERILATED_VSINGEN___024ROOT_H_  // guard

#include "verilated.h"


class Vsingen__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsingen___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(incr,7,0);
    VL_IN8(off,7,0);
    VL_IN8(rst,0,0);
    VL_IN8(en,0,0);
    VL_OUT8(dout1,7,0);
    VL_OUT8(dout2,7,0);
    CData/*7:0*/ singen__DOT__addr;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*7:0*/, 256> singen__DOT__sinevals__DOT__rom_array;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vsingen__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsingen___024root(Vsingen__Syms* symsp, const char* v__name);
    ~Vsingen___024root();
    VL_UNCOPYABLE(Vsingen___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
