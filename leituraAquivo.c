#include <stdio.h>
#include <string.h>
#include<ctype.h>

struct Linha{
 	char *linha;
struct Linha *prox;
};
typedef struct Linha noLinha;

int tam;

void inicia(noLinha *FILA){
	printf("Entrou em inicia\n");
	FILA->prox = NULL;
	tam=0;
}

int vazia(noLinha *FILA){
	if(FILA->prox == NULL)
	  	return 1;
	else
	  	return 0;
}

noLinha *aloca(noLinha *FILA){
//	printf("Entrou no aloca\n");
	noLinha *nova=(noLinha *) malloc(sizeof(noLinha));
//	printf("Alocou");
	if(!nova){
		printf("Sem memoria disponivel!\n");
	  	exit(1);
	}
	else{
//		printf("Entrou no else aloca\n");
		nova->linha = FILA->linha;
	  	return nova;
	}
}

void insere(noLinha *FILA){
//	printf("Entrou no insere\n");
	noLinha *nova=aloca(FILA);
 	nova->prox = NULL;

 	if(vazia(FILA)){
 		FILA->prox=nova;
//  		printf("********* Inseriu na fila vazia *********\n");
	}
 	else{
// 		printf("Fila n�o estava vazia\n");
  		noLinha *tmp = FILA->prox;

  		while(tmp->prox != NULL)
   		tmp = tmp->prox;

  		tmp->prox = nova;
  		printf("LINHA: %s", FILA->linha);
 	}
 	tam++;
 	printf("\n--- tamanho: %d ---\n", tam);
 	exibe(FILA);
}

void exibe(noLinha *FILA){
 	if(vazia(FILA)){
	  	printf("Fila vazia!\n\n");
	  	return ;
 	}

	noLinha *tmp;
	tmp = FILA->prox;
	printf("\n************* Fila *************\n");
	while( tmp != NULL){
  		printf("%s\n", tmp->linha);
  		tmp = tmp->prox;
 	}
//	printf("\n        ");
//	int count;
//	for(count=0 ; count < tam ; count++)
//		printf("  ^  ");
//	printf("\nOrdem:");
//	for(count=0 ; count < tam ; count++)
//  		printf("%5d", count+1);

 printf("\n\n");
}

noLinha *retira(noLinha *FILA)
{
	if(FILA->prox == NULL){
	  	printf("Fila ja esta vazia\n");
	  	return NULL;
	}
	else{
	  	noLinha *tmp = FILA->prox;
	  	FILA->prox = tmp->prox;
	  	tam--;
	  	return tmp;
 	}
}

void libera(noLinha *FILA){
 	if(!vazia(FILA)){
  		noLinha *proxLinha,
     	*atual;

  		atual = FILA->prox;
  		while(atual != NULL){
   			proxLinha = atual->prox;
   			free(atual);
   			atual = proxLinha;
  		}
 	}
}

int tiraCaracteresEspeciais(char *token){
	int i=0;
//	printf("p: %s\n", token);
//	for(i=0;i<strlen(token);i++){
//		printf("T[%d] = %c", i, token[i]);
//	}
}

int lerLinha(char *linha, int l, char *palavra){
	char *token, *palavrasSeparadas[1000] = {};
	const char espaco[2] = " ";
	int i=0;
	printf("frase[%d]: %s", l, linha);
	
//	insere(linha);
	
	/* get the first token */
   	token = strtok(linha, espaco);
   	palavrasSeparadas[i] = tolower(strdup(token));
   	
   
   	/* walk through other tokens */
   	while(token!=NULL){
//      	printf(" %s\n", token);
    	palavrasSeparadas[i] = tolower(token);
//      	tiraCaracteresEspeciais(&token);
      	token = strtok(NULL, espaco);
   		i++;
   	}
   	
   	int count = i;
   	
   	for(i=0;i<count;i++){
   		printf("palavra[%d]: %s\n", i, palavrasSeparadas[i]);
	}
}

int main(){
	noLinha *FILA = (noLinha *) malloc(sizeof(noLinha));
	
	if(!FILA){
  		printf("Sem memoria disponivel!\n");
  		exit(1);
 	}
	else{
 		inicia(FILA);
 	}
	
	FILE *arquivo;
	char palavra[20];
	int l=0;
	
	printf("Digite a palavra a ser encontrada: ");
	scanf("%s", &palavra);
//	palavra = tolower(palavra);
	
	arquivo = fopen("teste123.txt", "r");
	
	if(arquivo == NULL){
		perror("Nao foi possivel abrir o arquivo\n");
		exit(1);
	}
	
	char linha[1000];
	while(fgets(linha, sizeof(linha), arquivo)){
		printf("linha: %s\n", linha);
//		l++;
		FILA->linha = linha;
		insere(FILA);
//		
//		lerLinha(&linha, l, &palavra);
	}
	free(FILA);
	return 0;
}
