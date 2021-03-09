#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Linha{
 char linha;
 struct Linha *prox;
};
typedef struct Linha linha;

int tam;

void inicia(linha *FILA)
{
 FILA->prox = NULL;
 tam=0;
}

int vazia(linha *FILA)
{
	if(FILA->prox == NULL)
	  	return 1;
	else
	  	return 0;
}

linha *aloca(){
	linha *nova=(linha *) malloc(sizeof(linha));
	if(!nova){
		printf("Sem memoria disponivel!\n");
	  	exit(1);
	}
	else{
	  	printf("Nova linha: "); 
		scanf("%s", &nova->linha);
	  	return nova;
	}
}

void insere(linha *FILA)
{
	linha *nova=aloca();
 	nova->prox = NULL;

 	if(vazia(FILA))
  		FILA->prox=nova;
 	else{
  		linha *tmp = FILA->prox;

  		while(tmp->prox != NULL)
   		tmp = tmp->prox;

  		tmp->prox = nova;
 	}
 	tam++;
}

linha *retira(linha *FILA)
{
	if(FILA->prox == NULL){
	  	printf("Fila ja esta vazia\n");
	  	return NULL;
	}
	else{
	  	linha *tmp = FILA->prox;
	  	FILA->prox = tmp->prox;
	  	tam--;
	  	return tmp;
 	}
}

void libera(linha *FILA){
 	if(!vazia(FILA)){
  		linha *proxLinha,
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
	printf("p: %s\n", token);
//	for(i=0;i<strlen(token);i++){
//		printf("T[%d] = %c", i, token[i]);
//	}
}

int lerLinha(char *linha, int l, char *palavra){
	char *token, *palavrasSeparadas[1000] = {};
	const char espaco[2] = " ";
	int i=0;
	printf("frase[%d]: %s", l, linha);
	
	/* get the first token */
   	token = strtok(linha, espaco);
   	palavrasSeparadas[i] = tolower(strdup(token));
   	
   
   	/* walk through other tokens */
   	while(token!=NULL){
//      	printf(" %s\n", token);
    	palavrasSeparadas[i] = tolower(token);
      	tiraCaracteresEspeciais(&token);
      	token = strtok(NULL, espaco);
   		i++;
   	}
   	
   	int count = i;
   	
   	for(i=0;i<count;i++){
   		printf("palavra[%d]: %s\n", i, palavrasSeparadas[i]);
	}
}

int main(){
	linha *FILA = (linha *) malloc(sizeof(linha));
	
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
	
	arquivo = fopen("arquivo.txt", "r");
	
	if(arquivo == NULL){
		perror("Não foi possível abrir o arquivo");
		exit(1);
	}
	
	char linha[1000];
	while(fgets(linha, sizeof(linha), arquivo)){
//		printf("linha: %s\n", linha);
		l++;
		lerLinha(&linha, l, &palavra);
	}
	
	return 0;
}
