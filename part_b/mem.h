#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "font.h"


typedef struct {
	char *name;
	char *file;
	int topX;
	int topY;
	int bottomX;
	int bottomY;
} meme;

typedef struct {
	meme memes[10];
	int numMemes;
	font fonts[10];
	int numFonts;
} mem;

mem readMemFile(char* filename){

	FILE* memFile;
	if ((memFile = fopen(filename, "r")) == NULL){
		printf("File open failed\n");
		exit(0);
	};

	mem memory;
	char *line = NULL;
	char *name = malloc(100 * sizeof(char));;
	char *image = malloc(100 * sizeof(char));;
	size_t len = 0;
	ssize_t read;
	int num;

	char *memeToken;

	int i = 0;
	if ((read = getline(&line, &len, memFile)) != -1) {
		memeToken = strtok(line, " :\n");
		while(memeToken){
			if (strcmp(memeToken, "MEMES") != 0){
				meme newMeme = {memeToken};
				memory.memes[i] = newMeme;
				i++;
			}
			memeToken = strtok(NULL, " :\n");
		}
	}
	memory.numMemes = i;

	if ((read = getline(&line, &len, memFile)) != -1) {
		/* SKIP LINE */
	};

	char *fontToken;
	line = NULL;

        i = 0;
        if ((read = getline(&line, &len, memFile)) != -1) {
                fontToken = strtok(line, " :\n");
                while(fontToken){
                        if (strcmp(fontToken, "FONTS") != 0){
                                font newFont = readFontFile(fontToken);
                                memory.fonts[i] = newFont;
                                i++;
                        }
                        fontToken = strtok(NULL, " :\n");
                }
        }
	memory.numFonts = i;

	i = 0;
	while (i < memory.numMemes){
		if ((read = getline(&line, &len, memFile)) != -1) {
        	        /* SKIP LINE */
        	};
		if ((read = getline(&line, &len, memFile)) != -1) {
			char *memeFileToken;
			memeFileToken = strtok(line, " :\n");
			memeFileToken = strtok(NULL, " :\n");
			memeFileToken = strtok(NULL, " :\n");
			memory.memes[i].file = strdup(memeFileToken);
			memeFileToken = NULL;
		}
		if ((read = getline(&line, &len, memFile)) != -1) {
                        char *memeTopToken;

                        memeTopToken = strtok(line, " :\n");
                        memeTopToken = strtok(NULL, " :\n");
                        memeTopToken = strtok(NULL, " :\n");
                        memory.memes[i].topX = atoi(memeTopToken);
			memeTopToken = strtok(NULL, " :\n");
                        memory.memes[i].topY = atoi(memeTopToken);
                }
		if ((read = getline(&line, &len, memFile)) != -1) {
                        char *memeBottomToken;

			memeBottomToken = strtok(line, " :\n");
                        memeBottomToken = strtok(NULL, " :\n");
                        memeBottomToken = strtok(NULL, " :\n");
                        memory.memes[i].bottomX = atoi(memeBottomToken);
                        memeBottomToken = strtok(NULL, " :\n");
                        memory.memes[i].bottomY = atoi(memeBottomToken);	
                }

		i++;
	}


	fclose(memFile);
	
	return memory;
}

meme getMeme(mem memory, char *memeName){
        int i = 0;
        while (i < 10){
                if (strcmp(memory.memes[i].name, memeName) == 0){
                        return memory.memes[i];
                }
                i++;
        }
        return memory.memes[0];
}

font getFont(mem memory, char *fontName){
        int i = 0;
        while (i < 10){
                if (strcmp(memory.fonts[i].name, fontName) == 0){
                        return memory.fonts[i];
                }
                i++;
        }
        return memory.fonts[0];
}
