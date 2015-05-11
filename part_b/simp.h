typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
} simp_pixel;

typedef struct {
	int width;
	int height;
	simp_pixel* bits;
} simp_image;	


simp_image createMap(int w, int h){	
	simp_pixel* arr = malloc(w * h * sizeof(simp_pixel));
	simp_image s = {w, h, arr};
	return s;
}

simp_image readFromSIMP(char* filename){
	if (strstr(filename,".simp") == NULL){
        	printf("%s is not a SIMP file\n", filename);
                exit(0);
        }

        FILE* oldFile = fopen(filename, "r");
        unsigned char largeBuffer[4];

        fread(largeBuffer, 1, 4, oldFile);
        int width = largeBuffer[0] + (largeBuffer[1] << 8) + (largeBuffer[2] << 16) + (largeBuffer[3] << 24);

        fread(largeBuffer, 1, 4, oldFile);
        int height = largeBuffer[0] + (largeBuffer[1] << 8) + (largeBuffer[2] << 16) + (largeBuffer[3] << 24);

        simp_image img = createMap(width,height);

        int i = 0;
        while (i < (height * width)){
                fread(largeBuffer, 1, 4, oldFile);
                simp_pixel pix = {largeBuffer[0],largeBuffer[1],largeBuffer[2],largeBuffer[3]};
                img.bits[i] = pix;
                i++;
        }

        return img;
}

simp_image cropImage(simp_image img, int x, int y, int w, int h){
	simp_image newImg = createMap(w, h);

        int counter, oldI, newI, row;

        oldI = y * img.width;
        newI = 0; 
        counter = 0;
        row = 0;
        while (oldI < (img.width * (y + h + 1))){
        	counter = 0;
                while (counter < w){
                	newImg.bits[newI] = img.bits[x + oldI];
                        oldI++;
                        newI++;
                        counter++;
                }
                row++;
                oldI = (y + row) * img.width;
        }

	return newImg;
}

simp_pixel compute(simp_pixel one, simp_pixel two);

simp_image overlayImage(simp_image imgOne, simp_image imgTwo, int x, int y){
	int counter, oldI, newI, row;

        oldI = y * imgOne.width;
        newI = 0;
        counter = 0;
        row = 0;
        while (oldI < (imgOne.width * (y + imgTwo.height+ 1))){
  	      counter = 0;
              while (counter < imgTwo.width){
            	  imgOne.bits[x + oldI] = compute(imgOne.bits[x + oldI], imgTwo.bits[newI]);
                  oldI++;
                  newI++;
                  counter++;
              }
  	      row++;
  	      oldI = (y + row) * imgOne.width;
  	}

	return imgOne;
}

simp_pixel compute(simp_pixel one, simp_pixel two){
        char red, blue, green, alpha;

        red = ((two.alpha * two.red)/255) + ((one.alpha * (255 - two.alpha) * one.red)/(255 * 255));
        green = ((two.alpha * two.green)/255) + ((one.alpha * (255 - two.alpha) * one.green)/(255 * 255));
        blue = ((two.alpha * two.blue)/255) + ((one.alpha * (255 - two.alpha) * one.blue)/(255 * 255));
        alpha = 255 * two.alpha;
        alpha = alpha + (one.alpha * 255);
        alpha = alpha - (one.alpha * two.alpha);
        alpha = alpha / 255;

        simp_pixel newPixel = {red, green, blue, alpha};

        return newPixel;
}

void printToSimp(char* filename, simp_image img){
	if (strstr(filename,".simp") == NULL){
        	printf("%s is not a SIMP file\n", filename);
                exit(0);
        }

	FILE* simpFile = fopen(filename, "w");
	unsigned char buffer[4];

	int width = img.width;
	int height = img.height;

	buffer[3] = (width >> 24) & 0xFF;
	buffer[2] = (width >> 16) & 0xFF;
	buffer[1] = (width >> 8) & 0xFF;
	buffer[0] = width & 0xFF;
	fwrite(buffer, 1, 4, simpFile);

	buffer[3] = (height >> 24) & 0xFF;
        buffer[2] = (height >> 16) & 0xFF;
        buffer[1] = (height >> 8) & 0xFF;
        buffer[0] = height & 0xFF;
        fwrite(buffer, 1, 4, simpFile);
        
	int i = 0;
	while (i < (height * width)){
		buffer[3] = img.bits[i].alpha;
		buffer[2] = img.bits[i].blue;
		buffer[1] = img.bits[i].green;
		buffer[0] = img.bits[i].red;
		fwrite(buffer, 1, 4, simpFile);
		i++;
	}
}
