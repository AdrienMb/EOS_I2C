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

#include <iostream>
#include "PWM.h" //placed in the current directory for ease of use
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

using namespace exploringBB;
using namespace std;

void checkFile()
{

    FILE *fp;
    char ptr = '1';

    char cmd[] = "config-pin -a P9_21 pwm";
    system(cmd);
    DIR *dir = opendir("/sys/class/pwm/pwmchip1/pwm-1:1");

    if (dir)
    {
        closedir(dir);
        printf("File already exists \n");
    }
    else
    {
        char path[] = "/sys/class/pwm/pwmchip1/export";
        fp = fopen("/sys/class/pwm/pwmchip1/export", "wb");
        fwrite(&ptr, 1, 1, fp);
        fclose(fp);
        closedir(dir);
        printf("Set export to 1 \n");
    }
}

int main(int argc, const char *argv[])
{
    FILE *fp;
    char ptr = '1';

    checkFile();

    usleep(500000);

    int angle;
    int dutyInt;
    for(int i = 1; i < argc; i++) {
        angle = atoi(argv[i]);
        if(argc > 2) {
            printf("Too many arguments provided.\n");
            exit(99);
        }
    }
    
    if(angle<=90 && angle>=0){
        dutyInt = angle * 11111 +1000000;
    }
    else {
        dutyInt = 0;
        printf("Please write angle between 0 to 180\n");        
    }




    char period[] = "20000000";

    fp = fopen("/sys/class/pwm/pwmchip1/pwm-1:1/period", "w");
    fwrite(period, 1, sizeof(period), fp);
    fclose(fp);

    
    fp = fopen("/sys/class/pwm/pwmchip1/pwm-1:1/enable", "w");
    fwrite(&ptr, 1, 1, fp);

    std::string dutyS = std::to_string(dutyInt);
    char const *duty = dutyS.c_str(); 

    fp = fopen("/sys/class/pwm/pwmchip1/pwm-1:1/duty_cycle", "w");
    fwrite(duty, 1, sizeof(dutyS), fp);
    fclose(fp);



    
}
