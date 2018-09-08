/*
 * sunspec.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */
#include <include/sunspec_model.h>
#include <include/sunspec_utilities.h>

static void suns_common_model_init(void){
    CommonModel_S * pCommonModel = (CommonModel_S *)&usRegHoldingBuf[COMMON_MODEL_OFFSET];
    pCommonModel->ID = COMMON_MODEL_ID;
    pCommonModel->L = COMMON_MODEL_PDU_LENGTH;
    pCommonModel->DA = COMMON_MODEL_DEVICE_ADDRESS;
    suns_string_fill(&(pCommonModel->Mn[0]), SUNS_MANUFACTURER);
    suns_string_fill(&(pCommonModel->Md[0]), SUNS_MODEL);
    suns_string_fill(&(pCommonModel->Vr[0]), SUNS_VERSION);
    suns_string_fill(&(pCommonModel->SN[0]), SUNS_SERIAL_NUMBER);
}

static void suns_standard_model_init(void){
    StandardModel_S * pStandardModel = (StandardModel_S *)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    pStandardModel->ID = STANDARD_MODEL_ID;
    pStandardModel->L = STANDARD_MODEL_PDU_LENGTH;
}

static void suns_end_model_init(void){
    EndModel_S * pEndModel = (EndModel_S *)&usRegHoldingBuf[END_MODEL_OFFSET];
    pEndModel->ID = END_MODEL_ID;
    pEndModel->L = END_MODEL_PDU_LENGTH;
}

void suns_model_init(void){
    SunSpecModbusModelMap_S * pSunSpecModbusModelMap = (SunSpecModbusModelMap_S *)&usRegHoldingBuf[0];
    pSunSpecModbusModelMap->sunspec_id = SUNS_U32_WRITE(SUNSID);
    suns_common_model_init();
    suns_standard_model_init();
    suns_end_model_init();
}



