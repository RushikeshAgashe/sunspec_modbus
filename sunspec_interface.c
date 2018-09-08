/*
 * sunspec_interface.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */

#include <include/sunspec_interface.h>
#include <include/sunspec_model.h>
#include <include/sunspec_utilities.h>

/* suns_model_update(void) should be called periodically to update the
 * MODBUS registers with the updated value of the corresponding variables.
 * To ensure correct sunspec datatype, use suitable MACRO from the list below:
 * -----------------------------------------------------------------------------
 *      DATATYPE            MACRO
 * -----------------------------------------------------------------------------
 *      sunssf              SUNS_SF(<int value>)
 *      suns_uint32         SUNS_F32(<positive float value>, <scaling factor>)
 *                          or SUNS_U32(<uint32 value>)
 *      suns_int32          SUNS_F32(<float value>, <scaling factor>)
 *                          or SUNS_S32(<int value>)
 *      suns_uint16         SUNS_U16(<uint16 value>)
 *      suns_int16          SUNS_S32(<int16 value>)
 * -----------------------------------------------------------------------------
 *
 * Example Usage:
 * void suns_model_update(void){
 *   StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
 *   pStandardModel->dummy_sf = SUNS_SF(dummy_sf);
 *   pStandardModel->dummy0 = SUNS_F32(dummy0, pStandardModel->dummy_sf);
 *   pStandardModel->dummy1 = SUNS_U32(dummy1, pStandardModel->dummy_sf);
 *   pStandardModel->dummy2 = SUNS_S16(dummy2, pStandardModel->dummy_sf);
 * }
 *
 * where, dummy_sf, dummy0, dummy1, dummy2 are variables of your project.
 * For example, if your variables are declared in "variables.h", include this file at the top
 * of this file.
 */

void suns_model_default_init(){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    /*Initialize default values of data points here*/
}

void suns_model_update(void){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    /* Update MODBUS registers here */
}

void suns_init(void){
    ModbusInit(MB_RTU, SLAVE_ID, 0, BUADRATE, MB_PAR_NONE);
    suns_model_init();
}

void suns_poll(void){
    ModbusPoll();
}


