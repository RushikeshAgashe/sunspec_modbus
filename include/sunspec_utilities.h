/*
 * sunspec_utilities.h
 *
 *  Created on: Jun 10, 2018
 *      Author: Rushikesh
 */

#ifndef MODBUS_INCLUDE_SUNSPEC_UTILITIES_H_
#define MODBUS_INCLUDE_SUNSPEC_UTILITIES_H_

#include "sunspec_model.h"
#define SWAP_32(value)                            ((value & 0xFFFF0000) >> 16) | ((value & 0x0000FFFF) << 16)
#define SUNS_SF_WRITE(value)                      value
#define SUNS_U16_WRITE(value)                     value
#define SUNS_U32_WRITE(value)                     swap_u32(value)
#define SUNS_S16_WRITE(value)                     value
#define SUNS_S32_WRITE(value)                     value
#define SUNS_F32_WRITE(value, scaling_factor)     swap_u32(scale_f32(value, scaling_factor))
#define SUNS_F32_READ(value, scaling_factor)      scale_u32(SWAP_32(value), scaling_factor*(-1))


suns_uint32 swap_u32(suns_uint32 value);
suns_int32 scale_f32(float value, sunssf scaling_factor);
float scale_u32(suns_int32 value, sunssf scaling_factor);
void suns_string_fill(char* dest_str, const char* base_str);

#endif /* MODBUS_INCLUDE_SUNSPEC_UTILITIES_H_ */
