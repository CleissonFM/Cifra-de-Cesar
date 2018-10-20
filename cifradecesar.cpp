#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CIFRA 3

void rmQuebra(char *str){ //remove quebra de linha(\n) na leitura do fgets
	int tam;
	tam = strlen(str);
	if( str[tam-1] == '\n' )
		str[tam-1] = '\0';
}
void limpa_buffer(){
	setbuf(stdin, NULL);
}
char encripta( char caractere, int x ){//nesta função o 'caractere' será criptografado com a cifra 'x'
	int num = 0;
	char saida = caractere; // o caractere de saida por padrão é o de entrada para o caso seja um caracterer estranho
	char ALFABETO[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//26 caracteres (de 0 a 25)
	char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
	char numeros[] = "1234567890"; // 10 caracteres (de 0 a 9)

	for( num=0; num<=25; num++ )
	{
		if ( ALFABETO[num] == caractere )
			saida = ALFABETO[ ( num+x ) % 26 ];

		if ( alfabeto[num] == caractere )
			saida = alfabeto[ ( num+x ) % 26 ];
		if( num<=9 )
		{
			if ( numeros[num] == caractere )
				saida = numeros[ ( num+x ) % 10 ];
		}
	}// nesse for os caracteres são rotacionados para frente no alfabeto no loop em que forem encontrados (símbolos estranhos simplesmente não são encontrados)
return saida;
}

char decripta( char caractere, int x ){//nesta função o 'caractere' será criptografado com a cifra 'x'
	int num = 0;
	char saida = caractere;
	char ALFABETO[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//26 caracteres (0 a 25)
	char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
	char numeros[] = "1234567890";

	for( num=0; num<=25; num++ )
	{
		if ( ALFABETO[num] == caractere )
			saida = ALFABETO[ ( 26+num-x ) % 26 ];
		if ( alfabeto[num] == caractere )
			saida = alfabeto[ ( 26+num-x ) % 26 ];
		if(num<=9){
			if ( numeros[num] == caractere )
				saida = numeros[ ( 10+num-x ) % 10 ];
		}
	}// nesse for os caracteres são rotacionados para trás no alfabeto no loop em que forem encontrados (símbolos estranhos simplesmente não são encontrados)

return saida;
}


int main(int argc, char *argv[]){

	FILE *arquivo;
	char linha[1000], nomeArq[200]="", str[1000];
	str[0]='\0';
	int i, op, tam;

	if(argc == 2){
		tam = strlen(argv[1]);

		if( argv[1][tam-4]=='.' && argv[1][tam-3]=='t' && argv[1][tam-2]=='x' &&  argv[1][tam-1] =='t' )
			strcpy(nomeArq, argv[1]);
	}

	system ( "clear" ); // system ( "cls" ); para windows
	printf ( "\t####################\n" );
	printf ( "\t#  Cifra de Cesar  #\n" );
	printf ( "\t#  1-Encr  2-Decr  #\n" );
	printf ( "\t####################\n" );

	printf ( "[*] Digite sua escolha: " );
	scanf ( "%d", &op );
	limpa_buffer();

	if(strlen(nomeArq) == 0){
		printf ( "[*] Digite o nome do arquivo de texto: " );
		fgets ( nomeArq, 200, stdin );

		rmQuebra(nomeArq);
	}

	arquivo = fopen ( nomeArq, "r");	//abre arquivo de entrada

	if ( arquivo==NULL ){	//confere se abriu
		printf ( "%s\n", nomeArq );
		perror ( "[!] Se lascou, o arquivo nao foi aberto" );
	return -1;
	}

	while ( fgets ( linha , 1000 , arquivo )!=NULL ){	//faz leitura do arquivo onde str guarda todo o arquivo contatenando as linhas
		strcat ( str, linha );
	}

	system("clear");
	printf ( "\n	#####\tEntrada:\t#####	\n%s", str );
	fclose ( arquivo );

	switch ( op ){
		case 1:
			tam = strlen ( str );

			for ( i = 0; i < tam; i++ ){	//trabalha um caractere por vez ao longo de toda string
				str[i] = encripta( str[i], CIFRA );	//função encripta, desenvolvida lá em cima
			}

			printf( "\n\n	#####\tResultado:\t#####	\n%s\n\n", str );
			break;
		case 2:
			tam = strlen ( str );

			for( i = 0; i < tam; i++ ){	//trabalha um caractere por vez ao longo de toda string
					str[i] = decripta ( str[i], CIFRA );	//função decripta, desenvolvida lá em cima
			}

			printf( "\n\n	#####\tResultado:\t#####	\n%s\n\n", str );	//mostra resultado
			break;
		default:
			printf( "[!]Opção invalida.\n" );	//reclama quando usuario entra com uma opção não existente
			break;
	}

	if ( op==1 || op==2 )	//se fez alguma das duas operações, pergunta se quer a saida em um arquivo de texto
	{
		FILE *novoArq;
		int t, op2;

		t = strlen ( nomeArq );
		if ( nomeArq[t-4]=='.' )
			nomeArq[t-4]='\0';	//retira o ".txt" para dar nome ao arquivo novo

		printf ( "[*] Deseja criar um arquivo de texto com o resultado?\n" );
		printf ( "\t1 - sim | 0 - nao\n[*] Escolha: " );
		scanf ( "%d", &op2 );

		if ( op2==0 ){
			printf ( "[*] Nao criamos arquivo.\nacenos!\n" );
		}
		else if ( op2==1 )
		{
			if ( op==1 )
			{
				strcat ( nomeArq, "-enc.txt" );
				novoArq = fopen ( nomeArq, "w+" );
				fputs ( str, novoArq );
				fclose ( novoArq );

			}
			else if(op==2){
				strcat ( nomeArq, "-dec.txt" );
				novoArq = fopen ( nomeArq, "w+" );
				fputs ( str, novoArq );
				fclose ( novoArq );
			}

			if( novoArq==NULL ){
				perror ( "[!] Se lascou, erro em criar novo arquivo" );
			}else{
				printf ( "[*] Arquivo \'%s\' criado com sucesso.\nacenos!\n", nomeArq );
			}
		}
		else{
			puts ( "[!] Opcao desconhecida." );
			return -1;
		}
	}


return 0;
}
