#include "image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){

	int opcao;
	int escolha;
	char *arquivo = malloc(20 * sizeof(char));
	image *figura = malloc(sizeof(image*));

  	image *cinza = malloc(sizeof(image *));

	printf("Escolha sua opcao: \n");
	printf("1) Carregar imagem\n" );
	printf("2) Converter imagem para cinza\n");
	printf("3) Escrever imagem\n" );
	printf("4) Sair\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);

	while(opcao != 4){
		switch(opcao){
			case 1:
				printf("\nDeseja usar a imagem predeterminada?(\n");
				printf("1) Sim\n");
				printf("2) Nao\n");
				printf("Digite sua opcao: ");
				scanf("%d", &escolha);
				
				if (escolha == 1){
					figura = load_from_ppm("a.ppm");
				}
				else{
					printf("\nDigite o nome do arquivo que deseja usar: ");
					scanf("%s", arquivo);
					figura = load_from_ppm(arquivo);
				}
				break;
			case 2:
				rgb_to_gray(figura, cinza);
				break;
			case 3:
				printf("\nDigite o nome que deseja colocar na imagem: ");
				scanf("%s", arquivo);
				write_to_ppm(figura, arquivo);
				break;
		}
		printf("Escolha sua opcao: \n");
		printf("1) Carregar imagem\n" );
		printf("2) Converter imagem para cinza\n" );
		printf("3) Escrever imagem\n" );
		printf("4) Sair\n" );
		printf("Digite sua opcao: ");
		scanf("%d", &opcao);
	}

	return 0;
}