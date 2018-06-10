/*
 * sunspec.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */
#include "sunspec_model.h"
#include <string.h>

//SunSpecModbusModelMap_S SunSpecModbusModelMap;

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

void suns_common_model_init(void){
    CommonModel_S * pCommonModel = (CommonModel_S *)&usRegHoldingBuf[COMMON_MODEL_OFFSET];
    pCommonModel->ID = COMMON_MODEL_ID;
    pCommonModel->L = COMMON_MODEL_PDU_LENGTH;
    pCommonModel->DA = COMMON_MODEL_DEVICE_ADDRESS;
    suns_string_fill(&(pCommonModel->Mn[0]), SUNS_MANUFACTURER);
    suns_string_fill(&(pCommonModel->Md[0]), SUNS_MODEL);
    suns_string_fill(&(pCommonModel->Vr[0]), SUNS_VERSION);
    suns_string_fill(&(pCommonModel->SN[0]), SUNS_SERIAL_NUMBER);
}

void suns_standard_model_init(void){
    StandardModel_S * pStandardModel = (StandardModel_S *)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    pStandardModel->ID = STANDARD_MODEL_ID;
    pStandardModel->L = STANDARD_MODEL_PDU_LENGTH;
}

void suns_end_model_init(void){
    EndModel_S * pEndModel = (EndModel_S *)&usRegHoldingBuf[END_MODEL_OFFSET];
    pEndModel->ID = END_MODEL_ID;
    pEndModel->L = END_MODEL_PDU_LENGTH;
}

void suns_model_init(void){
    SunSpecModbusModelMap_S * pSunSpecModbusModelMap = (SunSpecModbusModelMap_S *)&usRegHoldingBuf[0];
    pSunSpecModbusModelMap->sunspec_id = 0x6e535375;
    suns_common_model_init();
    suns_standard_model_init();
    suns_end_model_init();
}



