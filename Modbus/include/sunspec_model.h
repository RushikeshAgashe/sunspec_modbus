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

#define SUNSID_LENGTH               2
#define HEADER_LENGTH               2

#define COMMON_MODEL_OFFSET         (SUNSID_LENGTH)
#define COMMON_MODEL_ID             1
#define COMMON_MODEL_PDU_LENGTH     66
#define COMMON_MODEL_DEVICE_ADDRESS 1
#define SUNS_MANUFACTURER           "FREEDM Systems Center"
#define SUNS_MODEL                  "3-SST Setup"
#define SUNS_VERSION                "v1.0"
#define SUNS_SERIAL_NUMBER          "1Z3H7YT893FAB"

#define STANDARD_MODEL_OFFSET       (COMMON_MODEL_OFFSET + COMMON_MODEL_PDU_LENGTH + HEADER_LENGTH)
#define STANDARD_MODEL_ID           64161
#define STANDARD_MODEL_PDU_LENGTH   8

#define END_MODEL_OFFSET            (STANDARD_MODEL_OFFSET + STANDARD_MODEL_PDU_LENGTH + HEADER_LENGTH)
#define END_MODEL_ID                0xFFFF
#define END_MODEL_PDU_LENGTH        0

typedef uint16_t suns_uint16;
typedef int16_t suns_int16;
typedef uint32_t suns_uint32;
typedef int16_t sunssf;

typedef struct CommonModel{
    suns_uint16 ID;
    suns_uint16 L;
    char Mn[16];
    char Md[16];
    char Opt[8];
    char Vr[8];
    char SN[16];
    suns_uint16 DA;
    suns_uint16 pad;
}CommonModel_S;

typedef struct StandardModel{
    suns_uint16 ID;
    suns_uint16 L;
    suns_uint32 Vbat;
    suns_uint32 Vldc;
    suns_uint32 Vhdc;
    suns_int16 E3_SF;
    suns_uint16 pad;
}StandardModel_S;

typedef struct EndModel{
    suns_uint16 ID;
    suns_uint16 L;
}EndModel_S;

typedef struct SunSpecModbusModelMap{
    suns_uint32   sunspec_id;
    CommonModel_S CommonModel;
    StandardModel_S StandardModel;
    EndModel_S EndModel;
}SunSpecModbusModelMap_S;

void suns_model_init();
#endif /* SUNSPEC_H_ */
