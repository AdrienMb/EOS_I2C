#include <iostream>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    FILE *fp;

    char *value;
    for (int i = 1; i < argc; i++)
    {
        value = argv[i];
        if (argc > 2)
        {
            printf("Too many arguments provided.\n");
            exit(99);
        }
    }

    char out[] = "out";
    fp = fopen("/sys/class/gpio/gpio49/direction", "w");
    fwrite(out, 1, sizeof(out), fp);
    fclose(fp);

    fp = fopen("/sys/class/gpio/gpio49/value", "w");
    fwrite(value, 1, sizeof(value), fp);
    fclose(fp);
}
