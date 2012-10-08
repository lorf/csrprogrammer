#include "devicemanager.h"
#include "stopwatch.h"
#include "usbprogrammer.h"
#include <cstring>

DeviceManager::DeviceManager()
{
    programmer = UsbProgrammer::getProgrammer();
}

bool DeviceManager::IsSupported()
{
    uint16_t id;
    if(!programmer->Read(0xff9a, &id)) return false;
    return id == 0x4826;
}

bool DeviceManager::XapResetAndGo()
{
    if(!IsSupported()) return false;

    int reset_count = 0;
    StopWatch timer;
    uint16_t tmp;
    int xx = 0x540000;

    programmer->SetTransferSpeed(0x189);
    programmer->Write(0x6A, 2);
    timer.start();
    while (timer.elapsedmsec() < 0x10 )
      programmer->Write(0x6A, 2);

    programmer->SetTransferSpeed(4);
    for(int i=0;i<100;i++)
    {
      if ( !programmer->Read(0x73, &tmp) )
      {
        if ( tmp >= 0x200u )
          programmer->Write(0x73u, 0);
        if(++reset_count >= 10)
            break;
      }
    }

    uint32_t address = 0xa000 + xx - 0x140000;
    programmer->Write(address,0);
    programmer->Write(address + 1, 0);
    programmer->Write(address + 2, 0xE0u);
    programmer->Write(0xFFE9, xx >> 16);
    programmer->Write(0xFFEA, xx);

    programmer->Read(0xFF7E, &tmp);
    tmp &= 0xEFFF;
    programmer->Write(0xFF7E, tmp);
    programmer->Write(0xFFDE, 0);
    programmer->Read(0xFFE8, &tmp);
    tmp &= 0x20u;
    programmer->Write(0xFFE8, tmp);
    programmer->Write(0x76, 2);
    programmer->Write(0xFF91, 5);
    programmer->Write(0x77, 1);
    programmer->Write(0x6A, 0);

    return true;
}

bool DeviceManager::XapResetAndStop()
{
    if(!IsSupported()) return false;

    int status;
    uint16_t data[0x6B],tmp;
    StopWatch timer;

    XapResetAndGo();
    timer.start();
    do
    {
        programmer->ReadBlock(0xFF91, 1, &tmp);
        if ( tmp )
            status = 0;
        else
            ++status;
    }
    while ( status < 2 && timer.elapsedmsec() < 8 );

    if(status < 2)
        return false;

    for (int i = 0; i < 20; ++i )
        programmer->Write(0x6A, 2);

    memset(data, 0, 0xD6);

    programmer->WriteBlock(0, 0x6B, data);
    programmer->Write(0x6A, 2);
    programmer->Write(0x6A, 2);
    programmer->WriteBlock(0xFFE0, 16, data);
    programmer->Write(0xFFEB, 0xff);
    programmer->Write(0xFFEC, 0xffff);

    return true;
}

bool DeviceManager::XapGo()
{
    if(!IsSupported()) return false;

    programmer->Write(0x6A,2);
    programmer->Write(0x6A,3);
    programmer->Write(0x6A,2);
    programmer->Write(0x6A,1);

    return true;
}

bool DeviceManager::XapStop()
{
    if(!IsSupported()) return false;

    uint16_t data[0x6B];//,tmp;

    for (int i = 0; i < 20; ++i )
        programmer->Write(0x6A, 2);

    memset(data, 0, sizeof(data));

    programmer->WriteBlock(0, 0x6B, data);
    programmer->Write(0x6A, 2);
    programmer->Write(0x6A, 2);
    /*programmer->Read(0xFFEB, &tmp);
    programmer->Read(0xFFEC, &tmp)*/
    programmer->WriteBlock(0xFFE0, 16, data);
    programmer->Write(0xFFEB, 0xff);
    programmer->Write(0xFFEC, 0xffff);

    return true;
}
