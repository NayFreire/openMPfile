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
	int tamanho;
}FILA;

void inicializaFila(FILA *f){
	f->ini = NULL;
	f->fim = NULL;
	f->tamanho = 0;
}

void enfileira(char linha[1000], FILA *f){
	NO *ptr = (NO*) malloc(sizeof(NO)); //Aloca o novo nó da fila
//	printf("\tlinha: %s", linha);
	if(ptr == NULL){
		printf("Erro de alocacao\n");
		return;
	}
	else{ //SEMPRE QUE UM NÓ É ALOCADO, INICIALIZA-SE O DADO E SEU PONTEIRO PRÓXIMO APONTA PARA NULL
		strcpy(ptr->linha, linha);
		ptr->prox = NULL;
		
		if(f->ini == NULL){ //CASO SEJA O PRIMEIRO NÓ DA FILA, O PONTEIRO INÍCIO DA FILA TEM QUE APONTAR PARA ESSE NÓ
			f->ini = ptr;
//			printf("\t\tprimeiro a ser enfileirado: %s\n", ptr->linha);
//			printf("\n\t *******enfileirando o primeiro no******* \n");
		}
		else{//CASO NÃO SEJA O PRIMEIRO NÓ A SER INSERIDO NA FILA, O PRÓXIMO DO ÚLTIMO NÓ INSERIDO VAI SER APONTADO PARA PTR
			f->fim->prox = ptr;
//			printf("\n\t *******proximo no a ser enfileirado*******\n");
		}
		
		f->fim = ptr;
		f->tamanho++;
//		printf("\n\t\ttam: %d\n\n", f->tamanho);
		return;
	}
}

char desenfileirar(FILA *f){
	NO *ptr = f->ini;
//	printf("\t\nLinha des: %s\n", ptr->linha);
	char linhaDes[1000];
	
	if(ptr!=NULL){
		f->ini = ptr->prox; //ATUALIZA O VALOR DO INÍCIO DA FILA COM O PRÓXIMO NÓ
		ptr->prox = NULL; //DESCONECTANDO O NÓ DA FILA
		strcpy(linhaDes, ptr->linha); //FAZENDO UM BACKUP COM O DADO DO NÓ EXCLUÍDO
		free(ptr);
		
		if(f->ini == NULL){ //CASO O INÍCIO DA FILA APONTE PRA NULL, SIGNIFICA QUE NÃO HÁ MAIS NÓS PARA DESENFILEIRAR
			f->fim = NULL; //ENTÃO O FIM DA FILA TAMBÉM DEVE APONTAR PARA NULL
		}	
		
		f->tamanho--;
//		printf("\t\t\ttam: %d", f->tamanho);

		#pragma omp critical
		{
			int numThread = omp_get_thread_num();
			int totalThreads = omp_get_num_threads();
			
			printf("\n------------------------------------------------------------------------------------------------\n");
			printf("\t\tThread %d de %d\n", numThread, totalThreads);
			buscaPalavra(linhaDes, palavra);
		}
		
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
	char palavrasSeparadas[1000];
	
	int qtd, i;
	int tamLinha=strlen(linha);
	int j,Npalavras,k;
	printf("\n\t\tBusca na linha: %s\n", linha);
	char *token = strtok(linha, " ");
	qtd=0;
    while(token != NULL) {
//        printf("\n\t%s --- %s\n", tolower(token), palavra);
        if(strncmp(tolower(token), tolower(palavra),strlen(palavra))==0){
        	printf("\t\t\t\t\t ACHOU\n\n");
        	qtdVezes++;
		}
        token = strtok(NULL, " ");
        qtd++;
    }
    int qtdPalavras = qtd;
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
			int l=0, i;
		
			printf("Digite a palavra a ser encontrada: ");
			scanf("%s", &palavra);
		
			arquivo = fopen("doomed.txt", "r");
			
			if(arquivo == NULL){
				perror("Nao foi possivel abrir o arquivo\n");
				exit(1);
			}
			
			char linha[1000];
			
			while(fgets(linha, sizeof(linha), arquivo)){
//				printf("linha: %s\n", linha);
				enfileira(&linha, f1);
			}
			printf("\n\t\t ++++++++++++++++++ Imprimindo as linhas na fila ++++++++++++++++++\n\n");
			imprimeFila(f1);
			
			int tamFila = f1->tamanho;
			
			for(i=0;i<tamFila;i++){
				desenfileirar(f1);
			}
			
			printf("Quantidade de vezes que %s apareceu: %d", palavra, qtdVezes);
		}

	}	
	
}
