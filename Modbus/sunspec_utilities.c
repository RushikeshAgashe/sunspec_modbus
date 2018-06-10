/*
 * sunspec_utilities.c
 *
 *  Created on: Jun 10, 2018
 *      Author: Rushikesh
 */

#include <string.h>
#include "math.h"
#include "sunspec_utilities.h"

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

suns_uint32 scale_f32(float value, sunssf scaling_factor){
    return swap_u32(value*pow(10,(scaling_factor*(-1))));
}






