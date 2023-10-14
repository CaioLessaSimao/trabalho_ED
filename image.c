#include "image.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct image_struct {
	char tipo[3];
	int colunas;
	int linhas;
	unsigned char **pixels;
};


image* create(int rows, int cols, char type[]){
	unsigned char **matriz = malloc(rows * sizeof(unsigned char *));
	
	for (int k = 0; k < rows; k++) {
    matriz[k] = malloc(cols * sizeof(unsigned char));
  	}

	srand(time(NULL));
	int random;


  	for (int i = 0; i < rows; i++) {
    	for (int j = 0; j < cols; j++) {
    		random = rand() % 256;
    		matriz[i][j] = (unsigned char)random;
    	}
  }


	image *pic = malloc(sizeof(image));

	image->tipo = type;
	image->colunas = cols;
	image->linhas = rows;
	image->pixels = matriz;

	return pic;
}

void write_to_ppm(Image* image, const char* filename){
	
	FILE *file = fopen(filename, "w");
  	if (!file) {
    	fprintf(stderr, "Error opening file for writing: %s\n", filename);
    	return;
  	}


	int width = image->colunas;
	int height = image->linhas;

	fprintf(file, "P2\n");
	fprintf(file, "%d %d\n", width, height);
	fprintf(file, "255\n"); 


  	for (int i = 0; i < height; i++) {
    	for (int j = 0; j < width; j++) {
      		fprintf(file, "%d", image_data[i][j]);
      		if (j < width - 1) {
       			fprintf(file, " ");
      		}
      		else {
        		fprintf(file, "\n");
      		}
    	}
  	}
  	fclose(file);
}
