// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsingen.h for the primary calling header

#include "Vsingen__pch.h"
#include "Vsingen__Syms.h"
#include "Vsingen___024root.h"

void Vsingen___024root___ctor_var_reset(Vsingen___024root* vlSelf);

Vsingen___024root::Vsingen___024root(Vsingen__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsingen___024root___ctor_var_reset(this);
}

void Vsingen___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vsingen___024root::~Vsingen___024root() {
}
