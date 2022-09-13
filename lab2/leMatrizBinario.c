#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[]) {
   float *matriz1, *matriz2; //matrizes que serão carregadas do arquivo
   int linhas1, colunas1, linhas2, colunas2; //dimensoes das matrizes
   long long int tam1, tam2; //qtde de elementos nas matrizes
   FILE * descritorArquivo1, * descritorArquivo2; //descritores dos arquivos de entrada
   size_t ret1, ret2; //retorno da funcao de leitura no arquivo de entrada
   
   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <arquivo entrada1> <arquivo entrada2> <arquivo saida>\n", argv[0]);
      return 1;
   }

   //abre o arquivo para leitura binaria da entrada 1 
   descritorArquivo1 = fopen(argv[1], "rb");
   descritorArquivo2 = fopen(argv[2], "rb");
   if(!descritorArquivo1 || !descritorArquivo2) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }

   //le as dimensoes das matrizes
   ret1 = fread(&linhas1, sizeof(int), 1, descritorArquivo1);
   if(!ret1) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 1\n");
      return 3;
   }
   ret1 = fread(&colunas1, sizeof(int), 1, descritorArquivo1);
   if(!ret1) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 1\n");
      return 3;
   }
   ret2 = fread(&linhas2, sizeof(int), 1, descritorArquivo2);
   if(!ret2) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 2\n");
      return 3;
   }
   ret2 = fread(&colunas2, sizeof(int), 1, descritorArquivo2);
   if(!ret2) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo 2\n");
      return 3;
   }
   tam1 = linhas1 * colunas1; //calcula a qtde de elementos da matriz de entrada 1
   tam2 = linhas2 * colunas2; //calcula a qtde de elementos da matriz de entrada 2

   //aloca memoria para as matrizes
   matriz1 = (float*) malloc(sizeof(float) * tam1);
   matriz2 = (float*) malloc(sizeof(float) * tam2);
   if(!matriz1 || !matriz2) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arquivo
   ret1 = fread(matriz1, sizeof(float), tam1, descritorArquivo1);
   ret2 = fread(matriz2, sizeof(float), tam2, descritorArquivo2);
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

   //finaliza o uso das variaveis
   fclose(descritorArquivo1);
   fclose(descritorArquivo2);
   free(matriz1);
   free(matriz2);
   return 0;
}
