/*
 * sunspec_utilities.h
 *
 *  Created on: Jun 10, 2018
 *      Author: Rushikesh
 */

#ifndef MODBUS_INCLUDE_SUNSPEC_UTILITIES_H_
#define MODBUS_INCLUDE_SUNSPEC_UTILITIES_H_

#include "sunspec_model.h"
#define SUNS_SF(value)                      value
#define SUNS_U16(value)                     value
#define SUNS_U32(value)                     swap_u32(value)
#define SUNS_S16(value)                     value
#define SUNS_S32(value)                     value
#define SUNS_F32(value, scaling_factor)     scale_f32(value, scaling_factor)


suns_uint32 swap_u32(suns_uint32 value);
suns_uint32 scale_f32(float value, sunssf scaling_factor);
void suns_string_fill(char* dest_str, const char* base_str);

#endif /* MODBUS_INCLUDE_SUNSPEC_UTILITIES_H_ */
