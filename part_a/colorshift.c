/*
 * colorshift.c
 *
 *  Created on: Jan 27, 2014
 *      Author: sean
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simp.h"

int main(int argc, char *argv[]) {
	char* usage = "Usage: ./colorshift fileIn.simp fileOut.simp pattern\n";

	if (argc != 4) {
		printf("%s", usage);
	} else {

		simp_image img = readFromSIMP(argv[1]);
			
		char* pattern = argv[3];

		if (!(strcmp(pattern, "RGB") == 0 || strcmp(pattern, "GBR") == 0 || strcmp(pattern, "BRG") == 0 || strcmp(pattern, "RBG") == 0 || strcmp(pattern, "BGR") == 0 || strcmp(pattern, "GRB") == 0 || strcmp(pattern, "RB") == 0 || strcmp(pattern, "BR") == 0 || strcmp(pattern, "RG") == 0 || strcmp(pattern, "GR") == 0 || strcmp(pattern, "GB") == 0 || strcmp(pattern, "BG") == 0)){
			printf("Error : %s is not a valid choice\n", pattern);
			printf("Shift options : [ RGB , GBR , BRG , RBG , BGR , GRB , RG , GR , RB , BR , GB , BG ]\n");
			printf("%s", usage);
			return 1;
		}

		unsigned char buffer[4];
		int i = 0;
		unsigned char temp;

		while (i < (img.width * img.height)){
			if (strcmp(pattern,"RGB") == 0 || strcmp(pattern,"GBR") == 0 || strcmp(pattern,"BRG") == 0){
				temp = img.bits[i].red;
				img.bits[i].red = img.bits[i].blue;
				img.bits[i].blue = img.bits[i].green;
				img.bits[i].green = temp;
			} else if (strcmp(pattern,"RBG") == 0 || strcmp(pattern,"BGR") == 0 || strcmp(pattern,"GRB") == 0){
				temp = img.bits[i].red;
                                img.bits[i].red = img.bits[i].green;
                                img.bits[i].green = img.bits[i].blue;
                                img.bits[i].blue = temp;
			} else if (strcmp(pattern,"RG") == 0 || strcmp(pattern,"GR") == 0){
				temp = img.bits[i].red;
                                img.bits[i].red = img.bits[i].green;
                                img.bits[i].green = temp;
			} else if (strcmp(pattern,"RB") == 0 || strcmp(pattern,"BR") == 0){
				temp = img.bits[i].red;
                                img.bits[i].red = img.bits[i].blue;
                                img.bits[i].blue = temp;
			} else if (strcmp(pattern,"GB") == 0 || strcmp(pattern,"BG") == 0){
				temp = img.bits[i].blue;
                                img.bits[i].blue = img.bits[i].green;
                                img.bits[i].green = temp;
			} else {
				/* will never reach */
			}

			i++;
		}

		printToSimp(argv[2], img);
		free(img.bits);
	}
}
