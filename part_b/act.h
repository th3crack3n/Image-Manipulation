#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	char *output;
	char *meme;
	char *font;
	char *topText;
	char *bottomText;
} act;

act readActFile(char* filename){

	FILE* actFile;
	if ((actFile = fopen(filename, "r")) == NULL){
		printf("File open failed\n");
		exit(0);
	};

	char *line = NULL;
	char *output = malloc(100 * sizeof(char));;
	char *meme = malloc(100 * sizeof(char));;
	char *font = malloc(100 * sizeof(char));;
	char *topText = malloc(100 * sizeof(char));;
	char *bottomText = malloc(100 * sizeof(char));;	
	size_t len = 0;
	ssize_t read;

	char *token;

	if ((read = getline(&line, &len, actFile)) != -1) {
		sscanf(line, "OUTFILE:%s\n", output);
	}
	if ((read = getline(&line, &len, actFile)) != -1) {
                sscanf(line, "MEME:%s\n", meme);
        }
	if ((read = getline(&line, &len, actFile)) != -1) {
                sscanf(line, "FONT:%s\n", font);
        }
	if ((read = getline(&line, &len, actFile)) != -1) {
		token = strtok(line, ":\n");
                token = strtok(NULL, ":\n");
                topText = strdup(token);		
        }
	if ((read = getline(&line, &len, actFile)) != -1) {
		token = strtok(line, ":\n");                
                token = strtok(NULL, ":\n");
                bottomText = strdup(token);
        }

	act activity = {output, meme, font, topText, bottomText};

	fclose(actFile);
	
	return activity;
}
