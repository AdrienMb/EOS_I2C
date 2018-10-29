
#ifndef Sensor_H_
#define Sensor_H_
#include"I2CDevice.h"

namespace exploringBB {

class Sensor:protected I2CDevice {
public:
	Sensor(unsigned int I2CBus, unsigned int I2CAddress=0x53);
	virtual ~Sensor();
    void displayData();

};

}

#endif