/*
 * sunspec_interface.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */

#include "sunspec_interface.h"
#include "sunspec_model.h"
#include "sunspec_utilities.h"

void suns_model_update(){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    pStandardModel->E3_SF = SUNS_SF(-3);
    pStandardModel->Vbat = SUNS_F32(142.891,pStandardModel->E3_SF);
    pStandardModel->Vldc = SUNS_F32(153.204,pStandardModel->E3_SF);
    pStandardModel->Vhdc = SUNS_F32(191.663,pStandardModel->E3_SF);
}

void suns_init(){
    ModbusInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE);
    suns_model_init();
}

void suns_poll(){
    ModbusPoll();
}


