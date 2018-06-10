/*
 * sunspec_interface.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */

#include "sunspec_interface.h"
#include "sunspec_model.h"
#include "mb_interface.h"
#include "math.h"
union{
    SunSpecModbusModelMap_S *pSunSpecModbusModelMap;
    USHORT *pusRegHoldingBuf;
}SunSpec;

void f_update(suns_uint16 *point, sunssf *scaling_factor, float value){
    *point = value*pow(10,(*scaling_factor*(-1)));
}

void u32_update(suns_uint32 *point, suns_uint32 value){
    suns_uint32 temp_val;
    temp_val = ((value & 0xFFFF) << 16) | ((value & 0xFFFF0000) >> 16);
    *point = temp_val;
}
void suns_model_update(){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[70];
    u32_update(&pStandardModel->Vbat,142);
    u32_update(&pStandardModel->Vldc,153);
    u32_update(&pStandardModel->Vhdc,191);
}

void suns_init(){
    ModbusInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE);
    suns_model_init();
}

void suns_poll(){
    ModbusPoll();
}


