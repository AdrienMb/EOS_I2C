
#include <iostream>
#include "Sensor.h"
#include <unistd.h>
#include <pthread.h>

using namespace std;
using namespace exploringBB;

int main(int argc, char* argv[]) {
    unsigned int i2c_bus = 2;

    if(argc > 1) {
        if(*argv[1] >= '0' && *argv[1] <= '2') {
            i2c_bus = *argv[1] - 0x30;
        } else {
            cout << "Usage:" << argv[0] << " [i2c-bus]\r\n";
            cout << "i2c-bus is either 0, 1 or 2. Default is 2\r\n";
            return -1;
        }
    }

    Sensor sensor(i2c_bus, 0x27);

    sensor.displayData();

	return 0;
}
