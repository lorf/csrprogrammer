#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "usbprogrammer.h"

/* This file servers partially as pttransport.dll transport layer */

class DeviceManager
{
public:
    DeviceManager();

    bool XapResetAndGo();
    bool XapResetAndStop();
    bool XapGo();
    bool XapStop();
    bool IsSupported();

private:
    UsbProgrammer *programmer;
};

#endif // DEVICEMANAGER_H
