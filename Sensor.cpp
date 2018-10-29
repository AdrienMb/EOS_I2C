
#include "Sensor.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <bitset>

using namespace std;

namespace exploringBB {

Sensor::~Sensor() {}

void Sensor::displayData() {
    int x = this->write(0x27);
    unsigned char *y = this->readDevice(5);

    for(int i = 0; i < 4; i++) {
        std::cout << std::bitset<8>(y[i]) << " ";
        printf("%d\n",y[i]);
    }
}

Sensor::Sensor(unsigned int I2CBus, unsigned int I2CAddress):
	I2CDevice(I2CBus, I2CAddress){   // this member initialisation list calls the parent constructor

}

} /* namespace exploringBB */
