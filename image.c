#include "image.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct image_struct {
	char tipo[3];
	int colunas;
	int linhas;
	unsigned char **pixels;
};


image* create(int rows, int cols, const char type[]){
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

	strcpy(pic->tipo, type);
	pic->colunas = cols;
	pic->linhas = rows;
	pic->pixels = matriz;
	

	return pic;
}


image* load_from_ppm(const char* filename){

	FILE* ptr = fopen(filename, "a+");

	char type[4];
	fgets(type, 20, ptr);

	char tamanho[10];
	fgets(tamanho, 50, ptr);

	char* coluna = strtok(tamanho, " ");
    char* linha = strtok(NULL, " ");

    int cols = atoi(coluna);
    int rows = atoi(linha);

    unsigned char **matriz = malloc(rows * sizeof(unsigned char *));
	
	for (int k = 0; k < rows; k++) {
    	matriz[k] = malloc(cols * sizeof(unsigned char));
  	}

  	fgets(tamanho, 50, ptr);

  	char *elemento = malloc(sizeof(char *));
  	char aux2[50];
  	int convertido = 0;  
  	
  	for(int i = 0; i < rows; i++){ 		
  		
  		fgets(aux2, 50, ptr);
  		elemento = strtok(aux2, " ");
  		convertido = atoi(elemento);
  		matriz[i][0] = (unsigned char)convertido;
  		
  		for(int j = 1; j < cols; j++){
  			
  			elemento = strtok(NULL, " ");
  			convertido = atoi(elemento);
  			matriz[i][j] = (unsigned char)convertido;
  		}
  	}
 
  	image *pic = malloc(sizeof(image));

	strcpy(pic->tipo, type);
	pic->colunas = cols;
	pic->linhas = rows;
	pic->pixels = matriz;

	printf("%s", pic->tipo);
	printf("%d\n", pic->colunas);
	printf("%d\n", pic->linhas);

	return pic;
}


void write_to_ppm(image* image, const char* filename){
	
	FILE *file = fopen(filename, "w");
  	if (!file) {
    	fprintf(stderr, "Error opening file for writing: %s\n", filename);
    	return;
  	}


	int width = image->colunas;
	int height = image->linhas;
	//unsigned char image_data = image->pixels;

	fprintf(file, "P2\n");
	fprintf(file, "%d %d\n", width, height);
	fprintf(file, "255\n"); 


  	for (int i = 0; i < height; i++) {
    	for (int j = 0; j < width; j++) {
      		fprintf(file, "%d", image->pixels[i][j]);
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