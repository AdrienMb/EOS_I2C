
#include "Sensor.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

using namespace std;

namespace exploringBB {

Sensor::~Sensor() {}

void Sensor::displayData() {
    this->write(54);
}

Sensor::Sensor(unsigned int I2CBus, unsigned int I2CAddress):
	I2CDevice(I2CBus, I2CAddress){   // this member initialisation list calls the parent constructor

}

} /* namespace exploringBB */
