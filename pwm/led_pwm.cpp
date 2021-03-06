#include <iostream>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

void checkFile()
{

    FILE *fp;
    char ptr = '0';

    char cmd[] = "config-pin -a P9_22 pwm";
    system(cmd);
    DIR *dir = opendir("/sys/class/pwm/pwmchip1/pwm-1:0");

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

    int intensity;
    int dutyInt;
    for(int i = 1; i < argc; i++) {
        intensity = atoi(argv[i]);
        if(argc > 2) {
            printf("Too many arguments provided.\n");
            exit(99);
        }
    }
    
    if(intensity<=100 && intensity>=0){
        dutyInt = intensity * 30000;
    }
    else {
        dutyInt = 0;
        printf("Please write intensity between 0 to 100\n");        
    }

    

    char period[] = "20000000";
    fp = fopen("/sys/class/pwm/pwmchip1/pwm-1:0/period", "w");
    fwrite(period, 1, sizeof(period), fp);
    fclose(fp);

    std::string dutyS = std::to_string(dutyInt);
    char const *duty = dutyS.c_str(); 

    printf("%d",sizeof(dutyS));

    fp = fopen("/sys/class/pwm/pwmchip1/pwm-1:0/duty_cycle", "w");
    fwrite(duty, 1, sizeof(dutyS), fp);
    fclose(fp);

    fp = fopen("/sys/class/pwm/pwmchip1/pwm-1:0/enable", "w");
    fwrite(&ptr, 1, 1, fp);
    fclose(fp);

    
}
