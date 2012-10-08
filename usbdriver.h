#ifndef USBCOM_H
#define USBCOM_H

#include <libusb-1.0/libusb.h>

/* This file servers as usbspi.sys driver */

class UsbDriver
{
public:
    UsbDriver();
    ~UsbDriver();
    void USBInit(void);
    void USBRelease(void);
    bool IsInitialized(void);
    bool ReadData(unsigned char data[], int size);
    bool WriteData(unsigned char data[], int size);

private:
    bool initialized;
    libusb_context *ctx;
    libusb_device_handle *dev_handle;
};

#endif // USBCOM_H
