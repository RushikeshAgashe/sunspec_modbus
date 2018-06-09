/*
 * sunspec_interface.h
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */

#ifndef MODBUS_SUNSPEC_INTERFACE_H_
#define MODBUS_SUNSPEC_INTERFACE_H_

#include "mb_interface.h"
#include "sunspec_model.h"

void suns_init();
void suns_model_update();
void suns_poll();
#endif /* MODBUS_SUNSPEC_INTERFACE_H_ */
