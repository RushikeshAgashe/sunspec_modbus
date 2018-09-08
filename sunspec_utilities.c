/*
 * sunspec_utilities.c
 *
 *  Created on: Jun 10, 2018
 *      Author: Rushikesh
 */

#include <include/sunspec_utilities.h>
#include <string.h>
#include "math.h"
#define POW_LTB_SIZE 10

float pow_ltb[10] = {0.00001f,0.0001f,0.001f,0.01f,0.1f,1.0f,10.0f,100.0f,1000.0f,10000.0f};

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

suns_uint32 swap_u32(suns_uint32 value){
    return ((value & 0xFFFF) << 16) | ((value & 0xFFFF0000) >> 16);
}

suns_int32 scale_f32(float value, sunssf scaling_factor){
    return (suns_int32)(value*pow_ltb[scaling_factor*(-1) + POW_LTB_SIZE/2]);
}

float scale_u32(suns_int32 value, sunssf scaling_factor){
    return (float)(value*pow_ltb[scaling_factor*(-1) + POW_LTB_SIZE/2]);
}






