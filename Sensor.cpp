
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

    printf("base10\n");
    printf("%d\n", y[0]);
    printf("%d\n", y[1]);
    printf("%d\n", y[2]);
    printf("%d\n\n", y[3]);
    

    bitset <8> h1(y[1]);
    bitset <8> h2(y[2]);
    bitset <16> h3 = concat(h1, h2);
    humidity = (int)(h3.to_ulong());

    bitset <8> t1(y[3]);
    bitset <8> t2(y[4]);
    bitset <16> t3 = concat(t1, t2);
    temperature = (int)(t3.to_ulong());


    // printf("bitsets\n");
    // printf("%s\n", h1.to_string());
    // printf("%s\n", h2.to_string());
    // printf("%s\n", t1.to_string());
    // printf("%s\n", t2.to_string());

    printf("before conversion\n");
    printf("H: %d\n", humidity);
    printf("T: %d\n", temperature);
    
    
    humidity = convertToRH(humidity);
    temperature = convertToCelcius(temperature);

    printf("H: %d", humidity);
    printf("T: %d", temperature);
}

Sensor::Sensor(unsigned int I2CBus, unsigned int I2CAddress):
	I2CDevice(I2CBus, I2CAddress){   // this member initialisation list calls the parent constructor

}

} /* namespace exploringBB */
