/*
 * crop.c
 *
 *  Created on: Jan 27, 2014
 *      Author: sean
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simp.h"

int main(int argc, char *argv[]) {
	char* usage = "Usage: ./crop fileIn.simp fileOut.simp x_position y_position width height\n";

	if (argc != 7) {
		printf("%s", usage);
	} else {
		int x = atoi(argv[3]);
		int y = atoi(argv[4]);
		int w = atoi(argv[5]);
		int h = atoi(argv[6]);

		simp_image img = readFromSIMP(argv[1]);

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
		if (x + w >= img.width){
			printf("Cropped area exceeds original image bounds by %d pixels\n", x + w - img.width);
			printf("%s", usage);
			exit(0);
		}		
		if (y + h >= img.height){
                        printf("Cropped area exceeds original image bounds by %d pixels\n", y + h - img.height);
                        printf("%s", usage);
			exit(0);
                }

		simp_image newImg = cropImage(img, x, y, w, h);

		printToSimp(argv[2], newImg);
		free(img.bits);
		free(newImg.bits);
	}
}
