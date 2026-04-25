#ifndef __SERIALDEBUG_H
#define __SERIALDEBUG_H

#include <kernel:types.h>
#include <device:serial.h>
#include <stdio.h>
#include <stdarg.h>

void SerialOpen(void);
void SerialClose(void);
void SerialWrite(const char *str, int32 len);
void SerialPrintf(const char *fmt, ...);

#endif
