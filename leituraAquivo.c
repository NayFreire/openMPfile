#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
   		i++;
//      	printf(" %s\n", token);
      	tiraCaracteresEspeciais(&token);
    	palavrasSeparadas[i] = tolower(strdup(token));
      	token = strtok(NULL, espaco);
   	}
   	
   	int count = i;
   	
   	for(i=0;i<count+1;i++){
//   		printf("palavra[%d]: %s\n", i, palavrasSeparadas[i]);
	}
}

int main(){
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
