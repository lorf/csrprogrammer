#ifndef FLASH_H
#define FLASH_H

#include <string>
#include <stdint.h>
#include "usbprogrammer.h"
#include "devicemanager.h"

/* This file servers as flash.dll */

using namespace std;

class Flash
{
public:
    Flash();
    bool dump(string filename);

private:
    uint32_t calc_crc(uint16_t *buffer, uint32_t length);
    bool wait_to_stop(int timeout);
    bool bootprog_load_and_run();
    bool bootprog_run();
    int read_flash_size();
    uint32_t read_flashcrc();
    void setsector(uint32_t sector);

private:
    UsbProgrammer *programmer;
    DeviceManager manager;
};

#endif // FLASH_H
