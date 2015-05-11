#include "simp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        char* name;
        char* filename;
	char letters[84];
        simp_image images[84];
} font;

font readFontFile(char* filename){

	FILE* fontFile;
	if ((fontFile = fopen(filename, "r")) == NULL){
		printf("File '%s'open failed\n", filename);
		exit(0);
	};

	char *line = NULL;
	char *name = malloc(100 * sizeof(char));;
	char *image = malloc(100 * sizeof(char));;
	size_t len = 0;
	ssize_t read;
	int num;

	if ((read = getline(&line, &len, fontFile)) != -1) {
		num =sscanf(line, "NAME:%s\n", name);
		if (num != 1) {
                        printf("Error : incorrectly formatted font file\n");
                        exit(0);
                }
	} else {
		printf("Error : incorrectly formatted font file\n");
		exit(0);
	}	

	if ((read = getline(&line, &len, fontFile)) != -1) {
		num =sscanf(line, "IMAGE:%s\n", image);
		if (num != 1) {
                        printf("Error : incorrectly formatted font file\n");
                        exit(0);
                }
	} else {
                printf("Error : incorrectly formatted font file\n");
                exit(0);
        }

	font newFont = {name, image};
	simp_image img = readFromSIMP(image);

	char letter;
	int x, y, w, h;

	int i = 0;
	while ((read = getline(&line, &len, fontFile)) != -1) { 
		num = sscanf(line, "CHARACTER%c:%d %d %d %d\n", &letter, &x, &y, &w, &h);	      	 
		if (num != 5) {
        	        printf("Error : incorrectly formatted font file\n");
        	        exit(0);
        	}	
		simp_image charImg = cropImage(img, x, y, w, h);		
		newFont.letters[i] = letter;
		newFont.images[i] = charImg;
		i++;
	}

	fclose(fontFile);
	
	return newFont;
}

simp_image findCharImg(font f, char element){
	int i = 0;
	while (i < 84){
		if (f.letters[i] == element){
			return f.images[i];
		}
		i++;
	}
	return f.images[26];;
}
