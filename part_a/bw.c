/*
 * bw.c
 *
 *  Created on: Jan 27, 2014
 *      Author: sean
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simp.h"

int main(int argc, char *argv[]) {
	char* usage = "Usage: ./bw fileIn.bmp fileOut.simp\n";

		if (argc != 3) {
			printf("%s", usage);
	} else {

		simp_image img = readFromSIMP(argv[1]);
		
		int i, average;
		i = 0;
		while (i < (img.height * img.width)){
			average = (img.bits[i].red + img.bits[i].blue + img.bits[i].green)/3;
			img.bits[i].red = average;
			img.bits[i].blue = average;
			img.bits[i].green = average;
			i++;
		}

		printToSimp(argv[2], img);
		free(img.bits);
	}
}

