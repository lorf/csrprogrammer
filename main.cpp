#include <iostream>
#include <string>
#include "usbprogrammer.h"
#include "devicemanager.h"
#include "flash.h"

using namespace std;

void usage(char* prog)
{
    cout << "Usage: " << prog << " <action> <filename>" << endl;
    cout << "Action can be:" << endl;
    cout << " dump - dump firmware from device" << endl;
    cout << " flash - flash new firmware to device" << endl;
}

int main(int argc, char **argv) {
    DeviceManager manager;
    Flash flash;

    if(argc != 3) {
        usage(argv[0]);
        return 0;
    }

    string action = argv[1];
    if(action != "dump" && action != "flash") {
        cout << "Invalid action!" << endl;
        usage(argv[0]);
        return 0;
    }

    if(!UsbProgrammer::getProgrammer()->IsInitialized()) {
        cout << "Cannot connect to programmer!" << endl;
        return 1;
    }

    if(!manager.IsSupported()) {
        cout << "Device is NOT supported!" << endl;
        return 1;
    }


    if(action == "dump") {
        if(!flash.dump(argv[2])) {
            cout << "Dumping failed!" << endl;
            return 1;
        }
    } else if(action == "flash"){
        cout << "Action currently not supported!" << endl;
    }

    manager.XapResetAndGo();

    return 0;
}
