/*
 * FreeModbus Libary: C2000 Port
 * 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $$
 */

/* ----------------------- Platform includes --------------------------------*/
#include <modbus/include/mb.h>
#include <modbus/include/mbport.h>
#include <modbus/include/port.h>
#include <modbus/rtu/mbrtu.h>
/* ----------------------- Serial Port --------------------------------------*/
#if SCI_PORT == SCI_A
    volatile struct SCI_REGS* sci_regs_ptr = &SciaRegs;
#elif SCI_PORT == SCI_B
    volatile struct SCI_REGS* sci_regs_ptr = &ScibRegs;
#endif

/* ----------------------- Defines ------------------------------------------*/

/* ----------------------Pragmas---------------------------------------------*/
#pragma CODE_SECTION(SciRxIsrHandler, "ramfuncs");
#pragma CODE_SECTION(SciTxIsrHandler, "ramfuncs");
#pragma CODE_SECTION(xMBPortSerialGetByte, "ramfuncs");

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{

    ENTER_CRITICAL_SECTION();
    if(xRxEnable)
    {
        SciRxSet(sci_regs_ptr, ENABLED);
        SciRxIsrSet(sci_regs_ptr, ENABLED);
    }
    else
    {
        SciRxSet(sci_regs_ptr, DISABLED);
        SciRxIsrSet(sci_regs_ptr, DISABLED);
    }

    if( xTxEnable )
    {
        SciTxSet(sci_regs_ptr, ENABLED);
        SciTxIsrSet(sci_regs_ptr, ENABLED);
        SendFirstByte();
    }
    else
    {
        SciTxSet(sci_regs_ptr, DISABLED);
        SciTxIsrSet(sci_regs_ptr, DISABLED);
    }
    EXIT_CRITICAL_SECTION();
}

BOOL
xMBPortSerialInit(UCHAR ucPort, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity)
{
	SciInit(sci_regs_ptr,ulBaudRate);

	vMBPortSerialEnable(TRUE, FALSE);

    return TRUE;
}
/*************************************************************************/
BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
#if SCI_PORT == SCI_A
    SciaRegs.SCITXBUF = ucByte;
#elif SCI_PORT == SCI_B
    ScibRegs.SCITXBUF = ucByte;
#endif
    return TRUE;
}
/*************************************************************************/
BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
#if SCI_PORT == SCI_A
    *pucByte = SciaRegs.SCIRXBUF.all;
#elif SCI_PORT == SCI_B
    *pucByte = ScibRegs.SCIRXBUF.all;
#endif
    return TRUE;
}

/*************************************************************************/
interrupt void SciRxIsrHandler(void)
{
	pxMBFrameCBByteReceived(  );
	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;
}// End of SciRxIsrHandler

/*************************************************************************/


interrupt void SciTxIsrHandler(void)
{
	pxMBFrameCBTransmitterEmpty();
	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;
}// End of SciTxIsrHandler

/*************************************************************************/
