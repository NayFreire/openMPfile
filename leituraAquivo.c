#include <stdio.h>
#include <string.h>
#include <ctype.h>

char palavra[20];
int qtdVezes = 0;

typedef struct NO{
	char linha[1000];
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

void enfileira(char linha[1000], FILA *f){
	NO *ptr = (NO*) malloc(sizeof(NO)); //Aloca o novo nó da fila
	printf("\tlinha: %s", linha);
	if(ptr == NULL){
		printf("Erro de alocacao\n");
		return;
	}
	else{ //SEMPRE QUE UM NÓ É ALOCADO, INICIALIZA-SE O DADO E SEU PONTEIRO PRÓXIMO APONTA PARA NULL
//		printf("\n\t alocacao check\n");
		strcpy(ptr->linha, linha);
//		printf("\taaLinha: %s\n", ptr->linha);
		ptr->prox = NULL;
		
		if(f->ini == NULL){ //CASO SEJA O PRIMEIRO NÓ DA FILA, O PONTEIRO INÍCIO DA FILA TEM QUE APONTAR PARA ESSE NÓ
			f->ini = ptr;
			printf("\t\tprimeiro a ser enfileirado: %s\n", ptr->linha);
			printf("\n\t *******enfileirando o primeiro no******* \n");
		}
		else{//CASO NÃO SEJA O PRIMEIRO NÓ A SER INSERIDO NA FILA, O PRÓXIMO DO ÚLTIMO NÓ INSERIDO VAI SER APONTADO PARA PTR
			f->fim->prox = ptr;
			printf("\n\t *******proximo no a ser enfileirado*******\n");
		}
		
		f->fim = ptr;
		printf("\n\tfim: %s\n\n", f->fim->linha);
		return;
	}
}

char desenfileirar(FILA *f){
	NO *ptr = f->ini;
//	printf("\taaLinha des: %s\n", ptr->linha);
	char linhaDes[1000];
	
	if(ptr!=NULL){
//		printf("\tEntrou no if do desenfileira\n");
		f->ini = ptr->prox; //ATUALIZA O VALOR DO INÍCIO DA FILA COM O PRÓXIMO NÓ
		ptr->prox = NULL; //DESCONECTANDO O NÓ DA FILA
		strcpy(linhaDes, ptr->linha); //FAZENDO UM BACKUP COM O DADO DO NÓ EXCLUÍDO
		free(ptr);
		
//		printf("backup: %s\n\n", linhaDes);
		
		if(f->ini == NULL){ //CASO O INÍCIO DA FILA APONTE PRA NULL, SIGNIFICA QUE NÃO HÁ MAIS NÓS PARA DESENFILEIRAR
			f->fim = NULL; //ENTÃO O FIM DA FILA TAMBÉM DEVE APONTAR PARA NULL
//			printf("if f->ini == null");
		}	

		buscaPalavra(linhaDes, palavra);
		
		return linhaDes;	
	}
	else{
		printf("\nFila vazia");
//		return 0;
	}
}

void imprimeFila(FILA *f){
	NO *ptr = f->ini;
	int i=0;
//	printf("\n\t\tNo inicial: %s\n", ptr->linha);
	if(ptr!=NULL){
		while(ptr!=NULL){ //ENQUANTO HÁ NÓS NA FILA
			printf("%s\n", ptr->linha); //O DADO DO NÓ SERÁ MOSTRADO
			ptr = ptr->prox; //E O PONTEIRO INÍCIO DA FILA SERÁ APONTADO PARA O PRÓXIMO NÓ, PARA QUE A FILA CONTINUE SENDO MOSTRADA
			i++;
		}
	}
	else{
		printf("\nFila vazia\n");
		return;
	}
}

void buscaPalavra(char linha[1000], char palavraBuscada){
//	char *token;
	char palavrasSeparadas[1000];
//	const char espaco[2] = " ";
	int qtd, i;
	int tamLinha=strlen(linha);
	int j,Npalavras,k;
	
	char *token = strtok(linha, " ");
	qtd=0;
//	for(i = 0; i < tamLinha; i++) 
//		printf(token[i] == 0 ? "\\0" : "%c", token[i]);
    while(token != NULL) {
//        strcpy(palavrasSeparadas[qtd], tolower(token));
        printf("\n\t%s --- %s\n", tolower(token), palavra);
        if(strcmp(tolower(token), tolower(palavra))==0){
        	printf("\t\t ACHOU\n\n");
        	qtdVezes++;
		}
        token = strtok(NULL, " ");
        qtd++;
//        printf("\ni: %d\n", qtd);
    }
    int qtdPalavras = qtd;
//    printf("qtd: %d", qtdPalavras);
    
//    for(i=0;i<qtdPalavras;i++){
//    	printf("PS[%d] = %s\n", i, palavrasSeparadas[i]);
//	}
}

int lerLinha(char *linha, char *palavra){
	char *token, palavrasSeparadas[1000] = {};
	const char espaco[2] = " ";
	int i=0;
//	printf("frase[%d]: %s", l, linha);
	
//	insere(linha);
	
	/* get the first token */
   	token = strtok(linha, espaco);
   	palavrasSeparadas[i] = tolower(strdup(token));
   	
   
   	/* walk through other tokens */
   	while(token!=NULL){
    	palavrasSeparadas[i] = tolower(token);
      	token = strtok(NULL, espaco);
   		i++;
   	}
}

int main(){
	int numThreads = 1;
	
	FILA *f1 = (FILA*) malloc(sizeof(FILA));
	
	if(f1==NULL){
		printf("Error de alocacao\n");
		exit(-1);
	}
	else{
		inicializaFila(f1);	
		#pragma omp parallel num_threads(numThreads)
		{
		
			FILE *arquivo;
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
			//	l++; 
	//			FILA->linha = linha;
	//			insere(FILA);
				enfileira(&linha, f1);
			//	libera(FILA);
			//	lerLinha(&linha, l, &palavra);
			}
			//	free(FILA);
			printf("\n\t\tImprimindo as linhas na fila\n");
			imprimeFila(f1);
			desenfileirar(f1);
			imprimeFila(f1);
			
			printf("quantidade de vezes que %s apareceu: %d", palavra, qtdVezes);
		}

	}	
	
}
