/*
 * mb_interface.h
 */
#include "../../modbus/include/mb.h"

#ifndef MB_INTERFACE_H_
#define MB_INTERFACE_H_

#define REG_HOLDING_NREGS               200
#define REG_INPUT_NREGS                 (20U)

// Inputs from modbus
extern unsigned int MBPowerRequest;

// Outputs to modbus
extern volatile unsigned int PWM_Duty;
extern unsigned int MBStorageCapacity;

extern void ModbusInit(eMBMode eMode, UCHAR ucSlaveAddress, UCHAR ucPort, ULONG ulBaudRate, eMBParity eParity);
extern void ModbusPoll(void);

extern USHORT   usRegInputStart;
extern USHORT   usRegInputBuf[REG_INPUT_NREGS];
extern USHORT   usRegHoldingStart;
extern USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];

#endif /* MB_INTERFACE_H_ */
