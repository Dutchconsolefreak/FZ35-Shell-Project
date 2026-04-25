#include <kernel:types.h>
#include <kernel:driver.h>
#include "serialdebug.h"

int main(int argc, char **argv)
{
    SerialOpen();
    SerialPrintf("Performing soft reset...\r\n");
    SerialClose();
    SoftReset();
    return 0;  /* never reached */
}