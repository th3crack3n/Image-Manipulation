#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "act.h"
 
int main(int argc, char* argv[]){
	
	if (argc != 3) {
		printf("Usage: ./meme file.mem file.act\n");
		exit(0);
	}
	
	mem newMem = readMemFile(argv[1]);
	act newAct = readActFile(argv[2]);
	meme newMeme = getMeme(newMem, newAct.meme);
	font newFont = getFont(newMem, newAct.font);

	char* top = strdup(newAct.topText);
	char* bottom = strdup(newAct.bottomText);

	int topWidth = 0;
	int topIndex = 0;
	while (topIndex < strlen(top)){
		topWidth += findCharImg(newFont, top[topIndex]).width;
		topIndex++; 
	}
	int startTopX = newMeme.topX - (topWidth / 2);

	int bottomWidth = 0;
        int bottomIndex = 0;
        while (bottomIndex < strlen(bottom)){
                bottomWidth += findCharImg(newFont, bottom[bottomIndex]).width;
                bottomIndex++;
        }
	int startBottomX = newMeme.bottomX - (bottomWidth / 2);

	simp_image img = readFromSIMP(newMeme.file);
	simp_image images[strlen(top) + strlen(bottom)];

	if (topWidth >= img.width){
		printf("Top text width exceeds image width\n");
		exit(0);
	}
	if (bottomWidth >= img.width){
                printf("Bottom text width exceeds image width\n");
                exit(0);
        }

	int currentTopX = startTopX;
	int currentBottomX = startBottomX;

	images[0] = overlayImage(img, findCharImg(newFont, top[0]), startTopX, newMeme.topY - findCharImg(newFont, top[0]).height);
	currentTopX += findCharImg(newFont, top[0]).width;


	int i = 1;
	while (i < strlen(top)){	 
		images[i] = overlayImage(images[i-1], findCharImg(newFont, top[i]), currentTopX, newMeme.topY - findCharImg(newFont, top[i]).height);
		currentTopX += findCharImg(newFont, top[i]).width;
		i++;
	}
	int newI = 0;
	while (i < (strlen(top) + strlen(bottom))){
                images[i] = overlayImage(images[i-1], findCharImg(newFont, bottom[newI]), currentBottomX, newMeme.bottomY - findCharImg(newFont, bottom[newI]).height);
                currentBottomX += findCharImg(newFont, bottom[newI]).width;
                i++;
		newI++;
        }

	printToSimp(newAct.output, images[i - 1]);

	return 0;
}
