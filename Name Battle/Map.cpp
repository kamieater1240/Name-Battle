#define _CRT_SECURE_NO_WARNINGS
#define objectnum(obj) (sizeof(obj)/sizeof(obj[0]))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include "Map.h"
using namespace std;

void loadMap() {

	FILE *fload;
	fload = fopen("map.txt", "ab+");

	char printMap[100];
	while (fscanf(fload, "%s", printMap) != EOF) {

		if (printMap == "\0")
			continue;
		for (size_t i = 0; i < strlen(printMap); i++) {
			if (printMap[i] == '0')
				printf("¡");
			else if (printMap[i] == '1')
				printf("@");
			else if (printMap[i] == '3')
				printf("Ÿ");
		}
		printf("\n");
	}
	fclose(fload);
}