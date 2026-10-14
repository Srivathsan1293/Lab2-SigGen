// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsingen.h for the primary calling header

#include "Vsingen__pch.h"
#include "Vsingen___024root.h"

void Vsingen___024root___eval_act(Vsingen___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vsingen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsingen___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vsingen___024root___nba_sequent__TOP__0(Vsingen___024root* vlSelf);

void Vsingen___024root___eval_nba(Vsingen___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vsingen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsingen___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vsingen___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vsingen___024root___nba_sequent__TOP__0(Vsingen___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vsingen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsingen___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*7:0*/ __Vdly__singen__DOT__addr;
    __Vdly__singen__DOT__addr = 0;
    // Body
    __Vdly__singen__DOT__addr = vlSelfRef.singen__DOT__addr;
    __Vdly__singen__DOT__addr = ((IData)(vlSelfRef.rst)
                                  ? 0U : (0xffU & ((IData)(vlSelfRef.en)
                                                    ? (IData)(vlSelfRef.incr)
                                                    : 
                                                   ((IData)(1U) 
                                                    + (IData)(vlSelfRef.singen__DOT__addr)))));
    vlSelfRef.dout1 = vlSelfRef.singen__DOT__sinevals__DOT__rom_array
        [(0xffU & VL_SHIFTL_III(8,8,32, (IData)(vlSelfRef.singen__DOT__addr), 2U))];
    vlSelfRef.dout2 = vlSelfRef.singen__DOT__sinevals__DOT__rom_array
        [(0xffU & VL_SHIFTL_III(8,8,32, ((IData)(vlSelfRef.singen__DOT__addr) 
                                         + (IData)(vlSelfRef.off)), 2U))];
    vlSelfRef.singen__DOT__addr = __Vdly__singen__DOT__addr;
}

void Vsingen___024root___eval_triggers__act(Vsingen___024root* vlSelf);

bool Vsingen___024root___eval_phase__act(Vsingen___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vsingen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsingen___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vsingen___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vsingen___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vsingen___024root___eval_phase__nba(Vsingen___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vsingen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsingen___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vsingen___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsingen___024root___dump_triggers__nba(Vsingen___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsingen___024root___dump_triggers__act(Vsingen___024root* vlSelf);
#endif  // VL_DEBUG

void Vsingen___024root___eval(Vsingen___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vsingen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsingen___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vsingen___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("singen.sv", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vsingen___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("singen.sv", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vsingen___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vsingen___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vsingen___024root___eval_debug_assertions(Vsingen___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vsingen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsingen___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelfRef.en & 0xfeU))) {
        Verilated::overWidthError("en");}
    if (VL_UNLIKELY((vlSelfRef.clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG
