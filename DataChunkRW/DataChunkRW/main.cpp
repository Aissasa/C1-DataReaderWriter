#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


#define CONFIG_FILE "config.txt"
#define DATA_FILE "data.bin"
#define STATS_FILE "stats.txt"

#define MIN_BYTES_VALUE 50
#define MAX_BYTES_VALUE 150

#define MIN_SHORTS_VALUE 1000
#define MAX_SHORTS_VALUE 2000

#define MIN_LONGS_VALUE 3000
#define MAX_LONGS_VALUE 5000

#define MIN_NUM_CHUNKS 0
#define MAX_NUM_CHUNKS 50

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef unsigned char BYTE;


int main()
{
    // files to work with
    FILE* configFile;
    FILE* dataFile;
    FILE* statsFile;

    //ranges
    unsigned int ranges[6];

    //the actual numbers of bytes, shorts and longs
    unsigned int numBytes;
    unsigned int numShorts;
    unsigned int numLongs;

    //read the config file and store the ranges in an array
    configFile = fopen(CONFIG_FILE, "rb");
    char buffer[5];
    for (BYTE i = 0; i < NELEMS(ranges); i++)
    {
        fscanf(configFile, "%s", buffer);
        ranges[i] = atoi(buffer);
    }
    fclose(configFile);

    // get the user input for the number of chunks of data
    int userInput = 0;
    printf("\nInput the number of chunks (it must be a positive integer in [1,49]):");

    //todo add input control
    scanf("%d", &userInput);


    // begin a for loop depending on the input
    // for each chunk, make a for loop that adds a number to the file
    // store these numbers as you go or calculate their means
    // after that output the results to the stats file


    //halt execution 
    char cTemp;
    printf("\nPress Enter to exit the program:");
    cTemp = getchar();
    while (cTemp != 0x0a)
    {
        cTemp = getchar();
    }

    return 0;
}
