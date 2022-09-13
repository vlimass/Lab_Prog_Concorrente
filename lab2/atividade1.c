#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[]) {
   float *matriz1, *matriz2; //matrizes que serão carregadas do arquivo
   int linhas1, colunas1, linhas2, colunas2; //dimensoes das matrizes
   long long int tam1, tam2, tamResultante; //qtde de elementos nas matrizes
   FILE * descritorArquivoEntrada1, * descritorArquivoEntrada2, * descritorArquivoSaida; //descritores dos arquivos
   size_t ret1, ret2, retSaida; //retorno da funcao de leitura nos arquivos 

   //recebe os argumentos de entrada
   if(argc < 4) {
      fprintf(stderr, "Digite: %s <arquivo entrada1> <arquivo entrada2> <arquivo saida>\n", argv[0]);
      return 1;
   }

   //abre o arquivo para leitura binaria da entrada 1 
   descritorArquivoEntrada1 = fopen(argv[1], "rb");
   descritorArquivoEntrada2 = fopen(argv[2], "rb");
   if(!descritorArquivoEntrada1 || !descritorArquivoEntrada2) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }

   //le as dimensoes das matrizes
   ret1 = fread(&linhas1, sizeof(int), 1, descritorArquivoEntrada1);
   if(!ret1) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 1\n");
      return 3;
   }
   ret1 = fread(&colunas1, sizeof(int), 1, descritorArquivoEntrada1);
   if(!ret1) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 1\n");
      return 3;
   }
   ret2 = fread(&linhas2, sizeof(int), 1, descritorArquivoEntrada2);
   if(!ret2) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 2\n");
      return 3;
   }
   ret2 = fread(&colunas2, sizeof(int), 1, descritorArquivoEntrada2);
   if(!ret2) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 2\n");
      return 3;
   }
   tam1 = linhas1 * colunas1; //calcula a qtde de elementos da matriz de entrada 1
   tam2 = linhas2 * colunas2; //calcula a qtde de elementos da matriz de entrada 2
   tamResultante = linhas1 * colunas2; //calcula a qtde de elementos da matriz de saida


   //aloca memoria para as matrizes
   matriz1 = (float*) malloc(sizeof(float) * tam1);
   matriz2 = (float*) malloc(sizeof(float) * tam2);
   if(!matriz1 || !matriz2) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arquivo
   ret1 = fread(matriz1, sizeof(float), tam1, descritorArquivoEntrada1);
   ret2 = fread(matriz2, sizeof(float), tam2, descritorArquivoEntrada2);
   if(ret1 < tam1 || ret2 < tam2) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }

   //imprime a matriz na saida padrao
   for(int i=0; i<linhas1; i++) { 
      for(int j=0; j<colunas1; j++)
        fprintf(stdout, "%.6f ", matriz1[i*colunas1+j]);
      fprintf(stdout, "\n");
   }

   printf("\n\n\n\n\n");

   for(int i=0; i<linhas2; i++) { 
      for(int j=0; j<colunas2; j++)
        fprintf(stdout, "%.6f ", matriz2[i*colunas2+j]);
      fprintf(stdout, "\n");
   }

   printf("\n\n\n\n\n");

   // realiza o produto das matrizes
   float matrizResultado[linhas1][colunas2], aux = 0; 

   if(colunas1 == linhas2) {
      for(int i = 0; i < linhas1; i++){
         for(int j = 0; j < colunas2; j++){

            matrizResultado[i][j] = 0;
            for(int z = 0; z < linhas2; z++){
               aux += matriz1[i*linhas1+z] * matriz2[z*linhas2+j];
            }

            matrizResultado[i][j] = aux;
            aux = 0;
         }
      }
   } else {
      fprintf(stderr, "Não é possível multiplicar as matrizes dadas\n");
      return 5;
   }

   // imprime matriz resultante
   for(int i=0; i<linhas1; i++) { 
      for(int j=0; j<colunas2; j++)
        fprintf(stdout, "%.6f ", matrizResultado[i][j]);
      fprintf(stdout, "\n");
   }

   //abre o arquivo para escrita binaria
   descritorArquivoSaida = fopen(argv[3], "wb");
   if(!descritorArquivoSaida) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }

   // escreve a matriz
   retSaida = fwrite(matrizResultado, sizeof(float), tamResultante, descritorArquivoSaida);
   if(retSaida < tamResultante) {
      fprintf(stderr, "Erro de escrita no arquivo\n");
      return 4;
   }


   //finaliza o uso das variaveis
   fclose(descritorArquivoEntrada1);
   fclose(descritorArquivoEntrada2);
   fclose(descritorArquivoSaida);
   free(matriz1);
   free(matriz2);
   return 0;
}
