#include "usbdriver.h"

UsbDriver::UsbDriver() :
    initialized(false),
    ctx(NULL),
    dev_handle(NULL)
{
    USBInit();
}

void UsbDriver::USBInit(void)
{
    if(initialized) return;

    libusb_device **devs;

    int r;
    ssize_t cnt;
    r = libusb_init(&ctx);

    cnt = libusb_get_device_list(ctx, &devs);
    if(cnt < 0) {
        USBRelease();
        return;
    }

    dev_handle = libusb_open_device_with_vid_pid(ctx, 0x0a12,0x0042);
    if(dev_handle == NULL) {
        USBRelease();
        return;
    }

    libusb_free_device_list(devs, 1);

    r = libusb_claim_interface(dev_handle, 0);
    if(r < 0) {
        USBRelease();
        return;
    }

    initialized = true;
}

void UsbDriver::USBRelease(void)
{
    if(dev_handle) {
        libusb_release_interface(dev_handle, 0);
        libusb_close(dev_handle);
    }

    if(ctx)
        libusb_exit(ctx);

    ctx = NULL;
    dev_handle = NULL;
    initialized = false;
}

UsbDriver::~UsbDriver()
{
    USBRelease();
}

bool UsbDriver::IsInitialized(void)
{
    return initialized;
}

bool UsbDriver::WriteData(unsigned char data[], int size)
{
    if(!initialized) return false;

    int r,actual,writed = 0;
    do {
        r = libusb_bulk_transfer(dev_handle, (2 | LIBUSB_ENDPOINT_OUT),
                     &data[writed], size-writed, &actual, 0);
        writed += actual;
        if(r) return false;
    } while (writed < size);
    return true;
}

bool UsbDriver::ReadData(unsigned char data[], int size)
{
    if(!initialized) return false;

    int r,actual = 0,readed = 0;
    do {
        r = libusb_bulk_transfer(dev_handle, (2 | LIBUSB_ENDPOINT_IN),
                    &data[readed], size-readed, &actual, 0);
        readed += actual;
        if(r) return false;
    } while(readed < size);
    return true;
}
