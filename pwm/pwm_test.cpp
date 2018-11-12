/*
 * pwm_test.cpp  Created on: 3rd Feb 2015
 * Copyright (c) 2014 Derek Molloy (www.derekmolloy.ie)
 * Made available for the book "Exploring BeagleBone"
 * See: www.exploringbeaglebone.com
 * Licensed under the EUPL V.1.1
 *
 * This Software is provided to You under the terms of the European
 * Union Public License (the "EUPL") version 1.1 as published by the
 * European Union. Any use of this Software, other than as authorized
 * under this License is strictly prohibited (to the extent such use
 * is covered by a right of the copyright holder of this Software).
 *
 * This Software is provided under the License on an "AS IS" basis and
 * without warranties of any kind concerning the Software, including
 * without limitation merchantability, fitness for a particular purpose,
 * absence of defects or errors, accuracy, and non-infringement of
 * intellectual property rights other than copyright. This disclaimer
 * of warranty is an essential part of the License and a condition for
 * the grant of any rights to this Software.
 *
 * For more details, see http://www.derekmolloy.ie/
 */

#include<iostream>
#include"PWM.h"      //placed in the current directory for ease of use
#include <stdio.h>
#include <string.h>
#include <dirent.h>

using namespace exploringBB;
using namespace std;


void checkFile() {
    char cmd[] = "config-pin -a P9_21 pwm";
    system(cmd);
    DIR *dir = opendir("/sys/class/pwm/pwmchip1/pwm-1\\:1");

    if(dir){
        closedir(dir);
        printf("File already exists \n");
    } else{
        char ptr = '1';
        char path[] = "/sys/class/pwm/pwmchip1/export";
        FILE *fp;
        fp = fopen(path, "w");
        fwrite(&ptr, 1, 1, fp);
        fclose(fp);
        closedir(dir);
        printf("Set export to 1 \n");
    }
    
}

int main( int argc, const char* argv[] ) {

    // checkFile();

    int intensity;

    for(int i = 1; i < argc; i++) {
        intensity = atoi(argv[i]);
        if(argc > 2) {
            printf("Too many arguments provided.\n");
            exit(99);
        }
    }

    int period = intensity * 10000;

    // PWM pwm("pwm_test_P9_22.15");  // example alternative pin
    PWM pwm("pwm_test_P9_21.12");  // P9_42 MUST be loaded as a slot before use
    pwm.setPeriod(period);         // Set the period in ns
    pwm.setDutyCycle(50.0f);       // Set the duty cycle as a percentage
    pwm.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
    pwm.run();                     // start the PWM output

}
