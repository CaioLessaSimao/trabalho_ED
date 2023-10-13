#include "image.h"
#include <stdio.h>

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

	image *pic = malloc(sizeof(image));

	image->tipo = type;
	image->colunas = cols;
	image->linhas = rows;
	image->pixels = matriz;

	return pic;
}
