#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct image_struct {
  char tipo[3];
  int colunas;
  int linhas;
  unsigned char ***pixels;
};

void imprimirMatriz(image *pic) {
  if (pic == NULL) {
    printf("Impossível imprimir a matriz, a imagem não foi carregada "
           "corretamente.\n");
    return;
  }

  printf("Tipo: %s\n", pic->tipo);
  printf("Dimensões: %d x %d\n", pic->colunas, pic->linhas);

  // Percorra a matriz e imprima os valores de cada pixel
  for (int i = 0; i < pic->linhas; i++) {
    for (int j = 0; j < pic->colunas; j++) {
      printf("(%3u, %3u, %3u) ", pic->pixels[i][j][0], pic->pixels[i][j][1],
             pic->pixels[i][j][2]);
    }
    printf("\n");
  }
}

image *create(int linhas, int colunas, const char type[]) {
  image *pic = malloc(sizeof(image));
  strcpy(pic->tipo, type);
  pic->colunas = colunas;
  pic->linhas = linhas;

  unsigned char ***matriz = (unsigned char ***)malloc(linhas * sizeof(unsigned char **));

  srand(time(NULL));

  // aloca memoria pro tipo p2
  if (strcmp(type, "P2") == 0) {
    for (int i = 0; i < linhas; i++) {
      matriz[i] = (unsigned char **)malloc(colunas * sizeof(unsigned char *));

      // aloca memoria pros pixels
      for (int j = 0; j < colunas; j++) {
        matriz[i][j] = (unsigned char *)malloc(1 * sizeof(unsigned char));

        // preenche com valores aleatórios
        int random = rand() % 256;
        matriz[i][j][0] = (unsigned char)random;
      }
    }

    // aloca memoria pro tipo p3
  } else if (strcmp(type, "P3") == 0) {
    for (int i = 0; i < linhas; i++) {
      matriz[i] = (unsigned char **)malloc(colunas * sizeof(unsigned char *));

      // aloca memoria pros pixels
      for (int j = 0; j < colunas; j++) {
        unsigned char rgb[3];

        // preenche vetor RGB com valores aleatórios
        for (int k = 0; k < 3; k++) {
          int random = rand() % 256;
          rgb[k] = (unsigned char)random;
        }

        // aloca a memória pro pixel e preenche
        matriz[i][j] = (unsigned char *)malloc(3 * sizeof(unsigned char));
        memcpy(matriz[i][j], rgb, 3);
      }
    }
  }

  pic->pixels = matriz;

  return pic;
}

// lê um arquivo PPM do tipo P3 e retorna uma estrutura imagem
image *load_from_ppm(const char *filename) {

  FILE *ptr = fopen(filename, "a+");

  if (ptr == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return NULL;
  }

  // Primeira linha
  char linha[1000];
  fgets(linha, 1000, ptr);
  char tipo[4];
  sscanf(linha, "%3s", tipo);

  // Segunda linha
  fgets(linha, 1000, ptr);
  int linhas, colunas;
  sscanf(linha, "%d %d", &colunas, &linhas);

  // Terceira linha
  fgets(linha, 1000, ptr);
  int maximo;
  sscanf(linha, "%d", &maximo);

  // Criando a matriz
  unsigned char ***matriz =
      (unsigned char ***)malloc(linhas * sizeof(unsigned char **));
  for (int i = 0; i < linhas; i++) {
    matriz[i] = (unsigned char **)malloc(colunas * sizeof(unsigned char *));
    for (int j = 0; j < colunas; j++) {
      matriz[i][j] = (unsigned char *)malloc(3 * sizeof(unsigned char));
    }
  }

  // Lendo e preenchendo os valores RGB
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      unsigned char r, g, b;
      if (fscanf(ptr, "%hhu %hhu %hhu", &r, &g, &b) == 3) {
        matriz[i][j][0] = r;
        matriz[i][j][1] = g;
        matriz[i][j][2] = b;
      } else {
        printf("Erro na leitura dos valores RGB.\n");
      }
    }
  }

  image *pic = malloc(sizeof(image));
  strcpy(pic->tipo, tipo);
  pic->colunas = colunas;
  pic->linhas = linhas;
  pic->pixels = matriz;

  fclose(ptr);

  // imprimindo antes de retornar
  // imprimirMatriz(pic);
  return pic;
}

void rgb_to_gray(image *image_rgb, image *image_gray) {
  
  // Copia os campos da imagem RGB
  *image_gray = *image_rgb;
  strcpy(image_gray->tipo, "P2");

  for (int i = 0; i < image_rgb->linhas; i++) {
    
    for (int j = 0; j < image_rgb->colunas; j++) {

      //pegando da matriz os valores RGB
      unsigned char r = image_rgb->pixels[i][j][0];
      unsigned char g = image_rgb->pixels[i][j][1];
      unsigned char b = image_rgb->pixels[i][j][2];

      //convertendo pra cinza
      unsigned char intensidade = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
      image_gray->pixels[i][j][0] = intensidade;
    }
  }
}

void write_to_ppm(image *image, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita: %s\n", filename);
        return;
    }

    int colunas = image->colunas;
    int linhas = image->linhas;

    //Imagem P2
    if (strcmp(image->tipo, "P2") == 0) {
        fprintf(file, "P2\n");
        fprintf(file, "%d %d\n", colunas, linhas);
        fprintf(file, "255\n");

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                fprintf(file, "%d", image->pixels[i][j][0]);
                if (j < colunas - 1) {
                    fprintf(file, " ");
                } else {
                    fprintf(file, "\n");
                }
            }
        }

    //Imagem p3
    } else if (strcmp(image->tipo, "P3") == 0) {
        fprintf(file, "P3\n");
        fprintf(file, "%d %d\n", colunas, linhas);
        fprintf(file, "255\n");

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                fprintf(file, "%d %d %d", image->pixels[i][j][0], image->pixels[i][j][1], image->pixels[i][j][2]);
                if (j < colunas - 1) {
                    fprintf(file, " ");
                } else {
                    fprintf(file, "\n");
                }
            }
        }
    } else {
        fprintf(stderr, "Formato de imagem não suportado: %s\n", image->tipo);
    }

    fclose(file);
}
