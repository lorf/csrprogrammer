#ifndef USBPROGRAMMER_H
#define USBPROGRAMMER_H

#include "usbdriver.h"
#include "stdint.h"

/* This file servers as usbspi.dll programmer interface
 * and partially as pttransport.dll transport layer
 */

class UsbProgrammer
{
public:
    static UsbProgrammer* getProgrammer();
    bool ReadBlock(uint16_t addr, int size, uint16_t buffer[]);
    bool Read(uint16_t addr, uint16_t *data);
    bool WriteBlock(uint16_t addr, int size, uint16_t buffer[]);
    bool Write(uint16_t addr, uint16_t data);
    bool SetTransferSpeed(uint16_t speed);
    bool IsXAPStopped(void);
    bool IsInitialized(void);
    bool SetMode(bool spi);
    bool ClearCmdBits();

private:
    UsbProgrammer();

private:
    UsbDriver usb;
    static UsbProgrammer *programmer;
    bool progInit;
};

#endif // USBPROGRAMMER_H
