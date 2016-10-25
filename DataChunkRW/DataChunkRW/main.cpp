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

	//read the config file and store the ranges 
	configFile = fopen(CONFIG_FILE, "rb");
	
	char buffer[5];

	for (BYTE i = 0; i < NELEMS(ranges); i++)
	{
		fscanf(configFile, "%s", buffer);
		ranges[i] = atoi(buffer);
	}

	fclose(configFile);

	// get user input

	// begin a for loop depending on the input
	// for each chunk, make a for loop that add a number to the file
	// store these numbers as you go or calculate their means
	// after that output the results to the stats file

	return 0;
}
