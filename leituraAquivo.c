#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct NO{
	char linha;
	struct NO *prox;
}NO;

typedef struct FILA{
	NO *ini;
	NO *fim;
}FILA;

void inicializaFila(FILA *f){
	f->ini = NULL;
	f->fim = NULL;
}

void enfileira(int dado, FILA *f){
	NO *ptr = (NO*) malloc(sizeof(NO)); //Aloca o novo nó da fila
	if(ptr == NULL){
		printf("Erro de alocacao\n");
		return;
	}
	else{ //SEMPRE QUE UM NÓ É ALOCADO, INICIALIZA-SE O DADO E SEU PONTEIRO PRÓXIMO APONTA PARA NULL
		ptr->dado = dado;
		ptr->prox = NULL;
		
		if(f->ini == NULL){ //CASO SEJA O PRIMEIRO NÓ DA FILA, O PONTEIRO INÍCIO DA FILA TEM QUE APONTAR PARA ESSE NÓ
			f->ini = ptr;
		}
		else{//CASO NÃO SEJA O PRIMEIRO NÓ A SER INSERIDO NA FILA, O PRÓXIMO DO ÚLTIMO NÓ INSERIDO VAI SER APONTADO PARA PTR
			f->fim->prox = ptr;
		}
		
		f->fim = ptr;
		return;
	}
}

int desenfileirar(FILA *f){
	NO *ptr = f->ini;
	int dado;
	if(ptr!=NULL){
		f->ini = ptr->prox; //ATUALIZA O VALOR DO INÍCIO DA FILA COM O PRÓXIMO NÓ
		ptr->prox = NULL; //DESCONECTANDO O NÓ DA FILA
		dado = ptr->dado; //FAZENDO UM BACKUP COM O DADO DO NÓ EXCLUÍDO
		free(ptr);
		
		if(f->ini == NULL){ //CASO O INÍCIO DA FILA APONTE PRA NULL, SIGNIFICA QUE NÃO HÁ MAIS NÓS PARA DESENFILEIRAR
			f->fim = NULL; //ENTÃO O FIM DA FILA TAMBÉM DEVE APONTAR PARA NULL
		}	
		return dado;	
	}
	else{
		printf("\nFila vazia");
		return 0;
	}
}

void imprimeFila(FILA *f){
	NO *ptr = f->ini;
	
	if(ptr!=NULL){
		while(ptr!=NULL){ //ENQUANTO HÁ NÓS NA FILA
			printf("%d ", ptr->dado); //O DADO DO NÓ SERÁ MOSTRADO
			ptr = ptr->prox; //E O PONTEIRO INÍCIO DA FILA SERÁ APONTADO PARA O PRÓXIMO NÓ, PARA QUE A FILA CONTINUE SENDO MOSTRADA
		}
	}
	else{
		printf("\nFila vazia\n");
		return;
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
//		libera(FILA);
//		lerLinha(&linha, l, &palavra);
	}
//	free(FILA);
	return 0;
}
