#include <kernel:types.h>
#include <kernel:io.h>
#include <kernel:devicecmd.h>
#include <device:serial.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "serialdebug.h"

static Item gSerialIOReq = -1;
static IOInfo gSerialIOInfo;
static Item gSerialDevice = -1;

void SerialWrite(const char *str, int32 len)
{
    if (gSerialIOReq < 0) return;
    memset(&gSerialIOInfo, 0, sizeof(gSerialIOInfo));
    gSerialIOInfo.ioi_Command         = CMD_STREAMWRITE;
    gSerialIOInfo.ioi_Send.iob_Buffer = (void *)str;
    gSerialIOInfo.ioi_Send.iob_Len    = len;
    DoIO(gSerialIOReq, &gSerialIOInfo);
}

static int serialOut(int ch, void *userData)
{
    char c = (char)ch;
    SerialWrite(&c, 1);
    return ch;
}

void SerialPrintf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vcprintf(fmt, serialOut, NULL, args);
    va_end(args);
}

void SerialOpen(void)
{
List     *list;
SerConfig sc;
Err       result;

    result = CreateDeviceStackListVA(&list,
        "cmds", DDF_EQ, DDF_INT, 10,
        CMD_STREAMREAD,
        CMD_STREAMWRITE,
        SER_CMD_STATUS,
        SER_CMD_SETCONFIG,
        SER_CMD_GETCONFIG,
        SER_CMD_WAITEVENT,
        SER_CMD_SETRTS,
        SER_CMD_SETDTR,
        SER_CMD_SETLOOPBACK,
        SER_CMD_BREAK,
        NULL);

    if (result >= 0 && !IsEmptyList(list))
    {
        gSerialDevice = OpenDeviceStack((DeviceStack *)FirstNode(list));
        DeleteDeviceStackList(list);
        if (gSerialDevice >= 0)
        {
            gSerialIOReq = CreateIOReq(NULL, 0, gSerialDevice, 0);

            sc.sc_BaudRate           = 57600;
            sc.sc_Handshake          = SER_HANDSHAKE_NONE;
            sc.sc_WordLength         = SER_WORDLENGTH_8;
            sc.sc_Parity             = SER_PARITY_NONE;
            sc.sc_StopBits           = SER_STOPBITS_1;
            sc.sc_OverflowBufferSize = 0;

            memset(&gSerialIOInfo, 0, sizeof(gSerialIOInfo));
            gSerialIOInfo.ioi_Command         = SER_CMD_SETCONFIG;
            gSerialIOInfo.ioi_Send.iob_Buffer = &sc;
            gSerialIOInfo.ioi_Send.iob_Len    = sizeof(sc);
            DoIO(gSerialIOReq, &gSerialIOInfo);
        }
    }
}

void SerialClose(void)
{
    if (gSerialIOReq >= 0)
    {
        DeleteIOReq(gSerialIOReq);
        CloseDeviceStack(gSerialDevice);
        gSerialIOReq  = -1;
        gSerialDevice = -1;
    }
}