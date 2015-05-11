/*
 * overlay.c
 *
 *  Created on: Jan 27, 2014
 *      Author: sean
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simp.h"

int main(int argc, char *argv[]) {
	char* usage = "Usage: ./overlay fileInOne.simp fileInTwo.simp fileOut.simp x_position y_position\n";

	if (argc != 6) {
		printf("%s", usage);
	} else {
		
		int x = atoi(argv[4]);
		int y = atoi(argv[5]);

		simp_image imgOne = readFromSIMP(argv[1]);
		simp_image imgTwo = readFromSIMP(argv[2]);

		if (x < 0){
			printf("x value cannot be less than zero\n");
			printf("%s", usage);
			exit(0);
		}
		if (y < 0){
                        printf("y value cannot be less than zero\n");
                        printf("%s", usage);
                        exit(0);
                }
		if (x + imgTwo.width >= imgOne.width){
                        printf("Second image area exceeds original image width by %d pixels\n", x + imgTwo.width - imgOne.width);
                        printf("%s", usage);
			exit(0);
                }
                if (y + imgTwo.height >= imgOne.height){
                        printf("Second image area exceeds original image height by %d pixels\n", y + imgTwo.height - imgOne.height);
                        printf("%s", usage);
                	exit(0);
		}

		simp_image imgThree = overlayImage(imgOne, imgTwo, x, y);		
		printToSimp(argv[3], imgThree);

		free(imgOne.bits);
		free(imgTwo.bits);
	}
}
