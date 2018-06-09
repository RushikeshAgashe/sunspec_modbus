/*
 * main.c
 */
#include "DSP28x_Project.h"
#include "DSP2833x_Sci.h"
#include "DSP2833x_EPwm.h"
#include "stdio.h"

//MODBUS
#include "port.h"
#include "sunspec_interface.h"

interrupt void controller(){

    EPwm1Regs.CMPA.half.CMPA = PWM_Duty;
    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

int main(void) {
    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);   // used in program to flash

    InitSysCtrl();
    InitGpio();
    InitEPwmGpio();

    InitScibGpio();
    InitCpuTimers(); //Initialize all CPU timers to known states
    DINT;
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    InitPieVectTable();

    EALLOW;
    PieVectTable.EPWM1_INT = &controller;   // ISR address stored

    //MODBUS
    PieVectTable.SCITXINTB  = &SciTxIsrHandler;
    PieVectTable.SCIRXINTB  = &SciRxIsrHandler;
    PieVectTable.TINT0      = &CpuTimer0IsrHandler;

    PieCtrlRegs.PIEIER3.bit.INTx1   = 1;      // Enable service to Group3 Interrupt1 i.e. EPWM1_INT
    PieCtrlRegs.PIECTRL.bit.ENPIE   = 1;    // Enable the PIE block

    //MODBUS
    PieCtrlRegs.PIEIER9.bit.INTx3   = 1;   // PIE Group 9, INT1 //SCIRXINTB_ISR
    PieCtrlRegs.PIEIER9.bit.INTx4   = 1;   // PIE Group 9, INT2 FOR SCIB TX
    PieCtrlRegs.PIEIER1.bit.INTx7   = 1;   // TINT0 in the PIE: Group 1 interrupt 7


    IER |= M_INT3;                          // Enable Group3 Interrupts (CPU INT3)

    //MODBUS
    IER |= M_INT9; //SCI Tx, Rx ISR         // Enable Group9 Interrupts (CPU INT9)
    IER |= M_INT1; //CPU Timer ISR

    InitEPwm();
    EINT;
    ERTM; // Enable Global Real Time Interrupt

    suns_init();
    while (1){
        suns_model_update();
        suns_poll();
    }
}
