
#include "Sensor.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <bitset>

using namespace std;

namespace exploringBB {

Sensor::~Sensor() {}

template <size_t N1, size_t N2 >
bitset <N1 + N2> concat( const bitset <N1> & b1, const bitset <N2> & b2 ) {
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    return bitset <N1 + N2>( s1 + s2 );
}

int Sensor::convertToCelcius(int temp){
    return temp/(pow(2,14)-2)*165-40;
}

int Sensor::convertToRH(int h){
    return h/(pow(2,14)-2)*100;
}

void Sensor::displayData() {
    int x = this->write(0x27);
    unsigned char *y = this->readDevice(5);
    int humidity = 0;
    int temperature = 0;

    bitset <6> h1(y[0]);
    bitset <8> h2(y[1]);
    bitset <14> h3 = concat(h1, h2);
    humidity = (int)(h3.to_ulong());

    bitset <8> t1(y[2]);
    bitset <8> t2(y[3]);
    t2 = t2 >> 2;
    bitset <6> t3(t2.to_ulong());
    bitset <14> t4 = concat(t1, t3);
    temperature = (int)(t4.to_ulong());
    
    humidity = convertToRH(humidity);
    temperature = convertToCelcius(temperature);

    printf("H: %d\n", humidity);
    printf("T: %d\n", temperature);
}

Sensor::Sensor(unsigned int I2CBus, unsigned int I2CAddress):
	I2CDevice(I2CBus, I2CAddress){   // this member initialisation list calls the parent constructor

}

} /* namespace exploringBB */
