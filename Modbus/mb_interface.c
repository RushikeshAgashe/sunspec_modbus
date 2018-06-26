/*
 * FreeModbus Libary: MSP430 Demo Application
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: demo.c,v 1.3 2006/11/19 15:22:40 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include <modbus/include/mb.h>
#include <modbus/include/mb_interface.h>
#include <modbus/include/mbport.h>
#include <modbus/include/port.h>
#include "string.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_SLAVE_ID						(0x01)
#define MB_BAUD_RATE					(19200)

#define REG_INPUT_START   				(0)
#define REG_INPUT_NREGS   				(20U)

#define REG_HOLDING_START 				1
#define REG_HOLDING_NREGS 				200

// Indices for outputs to Modbus
#define OUTPUT1 1

// Indices for input from modbus
#define INPUT1	2

/* ----------------------- Static variables ---------------------------------*/
USHORT   usRegInputStart = REG_INPUT_START;
USHORT   usRegInputBuf[REG_INPUT_NREGS];
USHORT   usRegHoldingStart = REG_HOLDING_START;
USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];

eMBErrorCode    eStatus;

// Outputs to modbus

/* ----------------------- Start implementation -----------------------------*/

/*
*******************************************************************************
* void ModbusInit(void)
*******************************************************************************
* Input         : void
* Output        : void
* Description   : Main Function for HUPS project.
*******************************************************************************
*/

void ModbusInit(eMBMode eMode, UCHAR ucSlaveAddress, UCHAR ucPort, ULONG ulBaudRate, eMBParity eParity)
{
	eStatus = eMBInit(eMode, ucSlaveAddress, ucPort, ulBaudRate, eParity);
	eStatus = eMBEnable();
	memset(usRegHoldingBuf,0,sizeof(usRegHoldingBuf));
}// End of ModbusInit


/*
*******************************************************************************
* void ModbusPoll(void)
*******************************************************************************
* Input         : void
* Output        : void
* Description   :
*******************************************************************************
*/

void ModbusPoll(void)
{
	(void)eMBPoll();
}// End of ModbusPoll

/*
*******************************************************************************
* eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
*******************************************************************************
* Input         : void
* Output        : void
* Description   :
*******************************************************************************
*/

eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}


/*
*******************************************************************************
* eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress,
* 								USHORT usNRegs, eMBRegisterMode eMode )
*******************************************************************************
* Input         : void
* Output        : void
* Description   :
*******************************************************************************
*/

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress,
							  USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_HOLDING_START ) &&
        ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegHoldingStart );
        switch ( eMode )
        {
            /* Pass current register values to the protocol stack. */
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
                *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
                *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            break;

            /* Update current register values with new values from the
             * protocol stack. */
        case MB_REG_WRITE:
            while( usNRegs > 0 )
            {
                usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                iRegIndex++;
                usNRegs--;
            }
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
