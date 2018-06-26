/*
 * sunspec_interface.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */

#include <include/sunspec_interface.h>
#include <include/sunspec_model.h>
#include <include/sunspec_utilities.h>

float Vbat = 142.891;
float Vldc = 153.204;
float Vhdc = 339.549;
float Vref = 737.444;
float dummy0 = 137.436;
float dummy1 = 335.158;
float dummy2 = 221.249;
float dummy3 = 154.145;
float dummy4 = 617.434;

void suns_model_default_init(){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    pStandardModel->E3_SF = SUNS_SF(-3);
    pStandardModel->Vbat = SUNS_F32(Vbat, pStandardModel->E3_SF);
    pStandardModel->Vldc = SUNS_F32(Vldc, pStandardModel->E3_SF);
    pStandardModel->Vhdc = SUNS_F32(Vhdc, pStandardModel->E3_SF);
    pStandardModel->dummy0 = SUNS_F32(dummy0, pStandardModel->E3_SF);
    pStandardModel->dummy1 = SUNS_F32(dummy1, pStandardModel->E3_SF);
    pStandardModel->dummy2 = SUNS_F32(dummy2, pStandardModel->E3_SF);
    pStandardModel->dummy3 = SUNS_F32(dummy3, pStandardModel->E3_SF);
    pStandardModel->dummy4 = SUNS_F32(dummy4, pStandardModel->E3_SF);
}

void suns_model_update(){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    pStandardModel->E3_SF = SUNS_SF(-3);
    Vbat += 1.763;
    Vldc += 3.332;
    Vhdc += 0.077;
    pStandardModel->Vbat = SUNS_F32(Vbat, pStandardModel->E3_SF);
    pStandardModel->Vldc = SUNS_F32(Vldc, pStandardModel->E3_SF);
    pStandardModel->Vhdc = SUNS_F32(Vhdc, pStandardModel->E3_SF);
    Vbat = (Vbat>500)?(142.891):Vbat;
    Vldc = (Vldc>180)?(153.204):Vldc;
    Vhdc = (Vhdc>350)?(339.549):Vhdc;
}

void suns_init(){
    ModbusInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE);
    suns_model_init();
}

void suns_poll(){
    ModbusPoll();
}


