/*
 * sunspec.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */
#include "sunspec_model.h"
#include <string.h>

const char* suns_manufacturer   = "FREEDM Systems Center";
const char* suns_model          = "3-SST Setup";
const char* suns_version        = "v1.0";
const char* suns_serial_number  = "1Z3H7YT893FAB";

void suns_string_fill(char* dest_str, const char* base_str){
    unsigned int *ptr = (unsigned int*)dest_str;
    unsigned int len = strlen(base_str);
    if (len%2){
        len /= 2;
        while(len--){ *ptr++ = (*base_str++ & 0xFF) | ((*base_str++ & 0xFF) << 8); }
        *ptr = (*base_str & 0xFF)<<8;
    }
    else{
        while(*base_str != '\0'){ *ptr++ = (*base_str++ & 0xFF) | ((*base_str++ & 0xFF) << 8); }
    }
}

void suns_common_model_init(SunSpecModbusModelMap_S * pSunSpecModbusModelMap){
    pSunSpecModbusModelMap->SunSpecCommonModel.ID = 1;
    pSunSpecModbusModelMap->SunSpecCommonModel.L = 66;
    suns_string_fill(&(pSunSpecModbusModelMap->SunSpecCommonModel.Mn[0]), suns_manufacturer);
    suns_string_fill(&(pSunSpecModbusModelMap->SunSpecCommonModel.Md[0]), suns_model);
    suns_string_fill(&(pSunSpecModbusModelMap->SunSpecCommonModel.Vr[0]), suns_version);
    suns_string_fill(&(pSunSpecModbusModelMap->SunSpecCommonModel.SN[0]), suns_serial_number);
}

void suns_standard_model_init(SunSpecModbusModelMap_S * pSunSpecModbusModelMap){
    pSunSpecModbusModelMap->SunSpecStandardModel.ID = 64161;
    pSunSpecModbusModelMap->SunSpecStandardModel.L = 4;
    pSunSpecModbusModelMap->SunSpecStandardModel.E3_SF = -2;
}

void suns_end_model_init(SunSpecModbusModelMap_S * pSunSpecModbusModelMap){
    pSunSpecModbusModelMap->SunSpecEndModel.ID = 0xFFFF;
    pSunSpecModbusModelMap->SunSpecEndModel.L = 0;
}

void suns_model_init(SunSpecModbusModelMap_S * pSunSpecModbusModelMap){
    pSunSpecModbusModelMap->sunspec_id_H = 0x5375;
    pSunSpecModbusModelMap->sunspec_id_L = 0x6e53;
    suns_common_model_init(pSunSpecModbusModelMap);
    suns_standard_model_init(pSunSpecModbusModelMap);
    suns_end_model_init(pSunSpecModbusModelMap);
}



