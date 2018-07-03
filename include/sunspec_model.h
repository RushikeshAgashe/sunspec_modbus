/*
 * sunspec.h
 *
 *  Created on: May 26, 2018
 *      Author: ragashe
 */

#ifndef SUNSPEC_MODEL_H_
#define SUNSPEC_MODEL_H_
#include <stdint.h>
#include "../modbus/include/mb_interface.h"

/* Notes:
 * ~~~~~~~~~~~~ SUNSPEC MODBUS MODEL MAP ~~~~~~~~~~~~~
 *       ---------------------------------------
 *      |          SUNSID = 0x53756e53          |
 *       ---------------------------------------
 *      |             COMMON MODEL              |
 *      |                                       |
 *      |       - Model ID      = 1             |
 *      |       - Model Length  = 66            |
 *      |       - Model Points                  |
 *      |           -Device Manufacturer Name   |
 *      |           -Device Model Name          |
 *      |           -Device Options(Optional)   |
 *      |           -Device Version(Optional)   |
 *      |           -Device Serial Number       |
 *      |           -Device Address             |
 *      |           -Pad for 32-bit Alignment   |
 *       ---------------------------------------
 *      |            STANDARD MODEL             |
 *      |                                       |
 *      |       - Model ID      =<user defined> |
 *      |       - Model Length  =<user defined> |
 *      |       - Model Points                  |
 *      |           - Points from a SunSpec     |
 *      |             defined Model or a        |
 *      |             custom model.             |
 *      |           - 32-bit Alignment Pad (if  |
 *      |             required to make model    |
 *      |             length even)              |
 *       ---------------------------------------
 *      |     More Standard Models (Optional)   |
 *       ---------------------------------------
 *      |               END MODEL               |
 *      |                                       |
 *      |       - Model ID      = 0xFFFF        |
 *      |       - Model Length  = 0             |
 *       ---------------------------------------
 *
 * COMMON MODEL
 * Common Model is a SunSpec defined model with Model_ID = 1
 * Every SunSpec compliant device must have this as the first model.
 *
 * STANDARD MODEL
 * This model is a SunSpec defined Standard Model or custom defined Standard Model.
 * Contains the data points.
 * For custom model, Model ID is of value 64xxx
 * When using custom model, client must have the corresponding smdx_64xxx.xml file.
 *
 * END MODEL
 * This is a SunSpec defined model with Model_ID = 0xFFFF and
 * Model_Length = 0. It denotes the end of the SunSpec Modbus Map.
 * Every SunSpec compliant device must have this as the last model.
 *
 *
 *Example Standard Model Configuration:
 * #define STANDARD_MODEL_PDU_LENGTH   8
 * typedef struct StandardModel{
 *   suns_uint16 ID;
 *   suns_uint16 L;
 *   suns_uint32 dummy0;
 *   suns_uint32 dummy1;
 *   suns_uint32 dummy2;
 *   sunssf dummy_sf;
 *   suns_uint16 pad;
 * }StandardModel_S;
 *
 * NOTE:
 * Size of every model must be an even number. Use a 16-bit pad if required to
 * make the size even.(This is required to maintain 32-bit alignment)
 *
*/

#define SUNSID                      0x53756e53
#define SUNSID_LENGTH               2
#define HEADER_LENGTH               2

#define COMMON_MODEL_OFFSET         (SUNSID_LENGTH)
#define COMMON_MODEL_ID             1
#define COMMON_MODEL_PDU_LENGTH     66
#define COMMON_MODEL_DEVICE_ADDRESS 1
#define SUNS_MANUFACTURER           "Manufacturer Name"
#define SUNS_MODEL                  "Model Name"
#define SUNS_VERSION                "Version Number"
#define SUNS_SERIAL_NUMBER          "Serial Number"

#define STANDARD_MODEL_OFFSET       (COMMON_MODEL_OFFSET + COMMON_MODEL_PDU_LENGTH + HEADER_LENGTH)
#define STANDARD_MODEL_ID           64161   /* Change as needed */
#define STANDARD_MODEL_PDU_LENGTH   0       /* Change as needed */

#define END_MODEL_OFFSET            (STANDARD_MODEL_OFFSET + STANDARD_MODEL_PDU_LENGTH + HEADER_LENGTH)
#define END_MODEL_ID                0xFFFF
#define END_MODEL_PDU_LENGTH        0

typedef int16_t     suns_int16;
typedef uint16_t    suns_uint16;
typedef int32_t     suns_int32;
typedef uint32_t    suns_uint32;
typedef int16_t     sunssf;
typedef char     suns_string;

typedef struct CommonModel{
    suns_uint16 ID;
    suns_uint16 L;
    suns_string Mn[16];
    suns_string Md[16];
    suns_string Opt[8];
    suns_string Vr[8];
    suns_string SN[16];
    suns_uint16 DA;
    suns_uint16 pad;
}CommonModel_S;

typedef struct StandardModel{
    suns_uint16 ID;
    suns_uint16 L;

    /* Add model points here */

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

void suns_model_init(void);
#endif /* SUNSPEC_H_ */
