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

void suns_model_update(){
    SunSpecStandardModel_S * StandardModel = &SunSpec.pSunSpecModbusModelMap->SunSpecStandardModel;
//    f_update(&StandardModel->Vbat,&StandardModel->E3_SF, 145.23);
    SunSpec.pSunSpecModbusModelMap->SunSpecStandardModel.Vbat = 140;
    SunSpec.pSunSpecModbusModelMap->SunSpecStandardModel.Vldc = 150;
    SunSpec.pSunSpecModbusModelMap->SunSpecStandardModel.Vhdc = 250;
}

void suns_init(){
    ModbusInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE);
    SunSpec.pusRegHoldingBuf = &usRegHoldingBuf[0];
    suns_model_init(SunSpec.pSunSpecModbusModelMap);
}

void suns_poll(){
    ModbusPoll();
}


