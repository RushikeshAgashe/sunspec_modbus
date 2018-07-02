/*
 * sunspec_interface.h
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */

#ifndef MODBUS_SUNSPEC_INTERFACE_H_
#define MODBUS_SUNSPEC_INTERFACE_H_

#define BUADRATE    19200
#define SLAVE_ID    1

void suns_init(void);
void suns_model_update(void);
void suns_poll(void);
#endif /* MODBUS_SUNSPEC_INTERFACE_H_ */
