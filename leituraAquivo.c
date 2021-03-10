#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct NO{
	char *linha;
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

void enfileira(char *linha, FILA *f){
	NO *ptr = (NO*) malloc(sizeof(NO)); //Aloca o novo n� da fila
	printf("\tlinha: %s", linha);
	if(ptr == NULL){
		printf("Erro de alocacao\n");
		return;
	}
	else{ //SEMPRE QUE UM N� � ALOCADO, INICIALIZA-SE O DADO E SEU PONTEIRO PR�XIMO APONTA PARA NULL
//		printf("\n\t alocacao check\n");
		ptr->linha = linha;
//		printf("\taaLinha: %s\n", ptr->linha);
		ptr->prox = NULL;
		
		if(f->ini == NULL){ //CASO SEJA O PRIMEIRO N� DA FILA, O PONTEIRO IN�CIO DA FILA TEM QUE APONTAR PARA ESSE N�
			f->ini = ptr;
			printf("\t\tprimeiro a ser enfileirado: %s\n", ptr->linha);
			printf("\n\t *******enfileirando o primeiro no******* \n");
		}
		else{//CASO N�O SEJA O PRIMEIRO N� A SER INSERIDO NA FILA, O PR�XIMO DO �LTIMO N� INSERIDO VAI SER APONTADO PARA PTR
			f->fim->prox = ptr;
			printf("\n\t *******proximo no a ser enfileirado*******\n");
		}
		
		f->fim = ptr;
		printf("\n\tfim: %s\n\n", f->fim->linha);
		return;
	}
}

int desenfileirar(FILA *f){
	NO *ptr = f->ini;
	printf("\taaLinha des: %s\n", ptr->linha);
	char linha;
	if(ptr!=NULL){
		f->ini = ptr->prox; //ATUALIZA O VALOR DO IN�CIO DA FILA COM O PR�XIMO N�
		ptr->prox = NULL; //DESCONECTANDO O N� DA FILA
		linha = ptr->linha; //FAZENDO UM BACKUP COM O DADO DO N� EXCLU�DO
		free(ptr);
		
		if(f->ini == NULL){ //CASO O IN�CIO DA FILA APONTE PRA NULL, SIGNIFICA QUE N�O H� MAIS N�S PARA DESENFILEIRAR
			f->fim = NULL; //ENT�O O FIM DA FILA TAMB�M DEVE APONTAR PARA NULL
		}	
		return linha;	
	}
	else{
		printf("\nFila vazia");
		return 0;
	}
}

void imprimeFila(FILA *f){
	NO *ptr = f->ini;
	int i=0;
	printf("\n\t\tNo inicial: %s\n", ptr->linha);
	if(ptr!=NULL){
		while(ptr!=NULL){ //ENQUANTO H� N�S NA FILA
			printf("L[%d]%s\n", i, ptr->linha); //O DADO DO N� SER� MOSTRADO
			ptr = ptr->prox; //E O PONTEIRO IN�CIO DA FILA SER� APONTADO PARA O PR�XIMO N�, PARA QUE A FILA CONTINUE SENDO MOSTRADA
			i++;
		}
	}
	else{
		printf("\nFila vazia\n");
		return;
	}
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
	int numThreads = 1;
	
	FILA *f1 = (FILA*) malloc(sizeof(FILA));
	
	if(f1==NULL){
		printf("Error de alocacao\n");
		exit(-1);
	}
	else{
		#pragma omp parallel num_threads(numThreads)
		{
			inicializaFila(f1);	
		
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
			printf("Desenfileirado: %s", desenfileirar(f1));
			imprimeFila(f1);
		}

	}	
	
}
