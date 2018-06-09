/*
 * sunspec.h
 *
 *  Created on: May 26, 2018
 *      Author: ragashe
 */

#ifndef SUNSPEC_MODEL_H_
#define SUNSPEC_MODEL_H_
#include <stdint.h>
#include "mb_interface.h"

typedef uint16_t suns_uint16;
typedef int16_t suns_int16;
typedef uint32_t suns_uint32;
typedef int16_t sunssf;

typedef struct SunSpecCommonModel{
    suns_uint16 ID;
    suns_uint16 L;
    char Mn[16];
    char Md[16];
    char Opt[8];
    char Vr[8];
    char SN[16];
    suns_uint16 DA;
    suns_uint16 pad;
}SunSpecCommonModel_S;

typedef struct SunSpecStandardModel{
    suns_uint16 ID;
    suns_uint16 L;
    suns_uint16 Vbat;
    suns_uint16 Vldc;
    suns_uint16 Vhdc;
    suns_int16 E3_SF;
}SunSpecStandardModel_S;

typedef struct SunSpecEndModel{
    suns_uint16 ID;
    suns_uint16 L;
}SunSpecEndModel_S;

typedef struct SunSpecModbusModelMap{
    suns_uint16   dummy;
    suns_uint16   sunspec_id_H;
    suns_uint16   sunspec_id_L;
    SunSpecCommonModel_S SunSpecCommonModel;
    SunSpecStandardModel_S SunSpecStandardModel;
    SunSpecEndModel_S SunSpecEndModel;
}SunSpecModbusModelMap_S;

extern SunSpecModbusModelMap_S SunSpecModbusModelMap;
void suns_model_init();
#endif /* SUNSPEC_H_ */
