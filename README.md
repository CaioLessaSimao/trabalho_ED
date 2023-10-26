# trabalho_ED
## Funcionalidades

O projeto inclui as seguintes funcionalidades:

1. Criação de Imagens:
   - É possível criar imagens nos formatos P2 (tons de cinza) e P3 (cores) com dimensões específicas.

2. Carregamento de Imagens:
   - O programa permite carregar imagens do tipo P3 a partir de arquivos PPM.

3. Conversão para Tons de Cinza:
   - A função `rgb_to_gray` permite converter imagens coloridas P3 em imagens em tons de cinza P2.

4. Salvamento de Imagens:
   - O código inclui a função `write_to_ppm`, que é capaz de salvar imagens nos formatos P2 ou P3.

## Estrutura do Projeto

- `main.c`: O arquivo principal contendo as funções `main` e chamadas das funções de processamento de imagens.
- `image.h`: O arquivo de cabeçalho contendo a definição da estrutura `image` e assinaturas de funções.
- `image.c`: O arquivo de implementação das funções para criar, carregar, converter e salvar imagens.

## Exemplos de Uso

```c
// Cria uma imagem P2 com 10 colunas, 5 linhas e valores aleatórios.
image *img_p2 = create(5, 10, "P2");

// Carrega uma imagem P3 a partir de um arquivo PPM.
image *img_p3 = load_from_ppm("input.ppm");

// Converte a imagem P3 em tons de cinza e armazena em uma nova imagem P2.
image *img_gray = rgb_to_gray(img_p3);

// Salva a imagem P2 em um arquivo PGM.
write_to_ppm(img_p2, "output.ppm");
