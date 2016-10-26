#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"

#define DEBUG 1

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

#define MIN_NUM_BYTES_INDEX 0
#define MAX_NUM_BYTES_INDEX 1
#define MIN_NUM_SHORTS_INDEX 2
#define MAX_NUM_SHORTS_INDEX 3
#define MIN_NUM_LONGS_INDEX 4
#define MAX_NUM_LONGS_INDEX 5


#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

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
    printf("\nInput the number of chunks (it must be a positive integer between 1 and 49):");

    //todo account for chars
    scanf("%d", &userInput);
    while (userInput<=0 || userInput>=50)
    {
        printf("\nPlease input a positive integer between 1 and 49:");
        scanf("%d", &userInput);
    }

    //open the files to write to
    dataFile = fopen(DATA_FILE, "w");
    statsFile = fopen(STATS_FILE, "w");

    //start outputting to the files
    fwrite(&userInput, sizeof(userInput), 1, dataFile);
    fprintf(statsFile, "User chose %d section(s)\n", userInput);

    //seed the the random generator
    srand((unsigned)time(NULL));

    for (int k = 0; k < userInput; k++)
    {
        //write intro
        fprintf(statsFile, "\nSection %d\n", k+1);

        //get random numbers for number of bytes, shorts and longs
        numBytes = getRandomNumber(ranges[MIN_NUM_BYTES_INDEX], ranges[MAX_NUM_BYTES_INDEX]);
        numShorts = getRandomNumber(ranges[MIN_NUM_SHORTS_INDEX], ranges[MAX_NUM_SHORTS_INDEX]);
        numLongs = getRandomNumber(ranges[MIN_NUM_LONGS_INDEX], ranges[MAX_NUM_LONGS_INDEX]);
#if DEBUG
        printf("Chunk %d:\n Number of bytes is %d, number of shorts is %d , number of longs is %d\n", k+1, numBytes, numShorts, numLongs);
#endif // DEBUG

        //add the ranges of this section to the data file
        fwrite(&numBytes, sizeof(numBytes), 1, dataFile);
        fwrite(&numShorts, sizeof(numShorts), 1, dataFile);
        fwrite(&numLongs, sizeof(numLongs), 1, dataFile);

        //create and populate a bytes array
        BYTE* bytesArray = (BYTE*)calloc(numBytes, sizeof(BYTE));

        //prepare for average calculation
        unsigned int total = 0;

        for (unsigned int i = 0; i < numBytes; i++)
        {
            // get a random number
            BYTE number = (BYTE) getRandomNumber(MIN_BYTES_VALUE, MAX_BYTES_VALUE);
            *(bytesArray + i) = number;
            total += number;
        }
        //add the bytes data to the data file
        fwrite(bytesArray, sizeof(BYTE),numBytes, dataFile);

        free(bytesArray);

        //account for the padding
        BYTE paddingByte;

        int bytesPadding =numBytes % 4;
        if (bytesPadding)
        {
            bytesPadding = 4 - bytesPadding;
            for (int i = 0; i < bytesPadding; i++)
            {
                paddingByte = 'p';
                fwrite(&paddingByte, sizeof(BYTE), 1, dataFile);
            }
        }
        printf("bytes padding: %d\n", bytesPadding);

        //calculate bytes average
        float average = (float)total / (float)numBytes;

        //add stats
        fprintf(statsFile, "%d bytes, average value %.2f\n", numBytes, average);

        //create and populate the shorts array
        unsigned short* shortsArray = (unsigned short*)calloc(numShorts, sizeof(short));

        total = 0;
        for (unsigned int i = 0; i < numShorts; i++)
        {
            // get a random number
            unsigned short number = (unsigned short)getRandomNumber(MIN_SHORTS_VALUE, MAX_SHORTS_VALUE);
            *(shortsArray + i) = number;
            total += number;
        }
        //add the shorts data to the data file
        fwrite(shortsArray, sizeof(short), numShorts, dataFile);

        free(shortsArray);

        int shortsPadding = numShorts % 2;
        if (shortsPadding)
        {
            for (int i = 0; i < shortsPadding*2; i++)
            {
                paddingByte = 'p';
                fwrite(&paddingByte, sizeof(BYTE), 1, dataFile);
            }
        }
        printf("shorts padding: %d\n", shortsPadding);

        //calculate short average
        average = (float)total / (float)numShorts;

        //add stats
        fprintf(statsFile, "%d shorts, average value %.2f\n", numShorts, average);


        //create and populate longs array
        unsigned int* longsArray = (unsigned int*)calloc(numLongs, sizeof(int));

        total = 0;
        for (unsigned int i = 0; i < numLongs; i++)
        {
            // get a random number
            unsigned int number = (unsigned int)getRandomNumber(MIN_LONGS_VALUE, MAX_LONGS_VALUE);
            *(longsArray + i) = number;
            total += number;
        }
        //add the longs data to the data file
        fwrite(longsArray, sizeof(int), numLongs, dataFile);

        free(longsArray);

        //calculate longs average
        average = (float)total / (float)numLongs;

        //add stats
        fprintf(statsFile, "%d longs, average value %.2f\n", numLongs, average);

    }
    //close files
    fclose(dataFile);
    fclose(statsFile);

    //halt execution 
    char cTemp;
    printf("\nPress Space to exit the program:");
    cTemp = getchar();
    while (cTemp != ' ')
    {
        cTemp = getchar();
    }

    return 0;
}

int getRandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
