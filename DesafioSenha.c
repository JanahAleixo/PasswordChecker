#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Fun��o para verificar se uma palavra � um pal�ndromo */
int is_palindrome(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

/* Fun��o para verificar se uma palavra cont�m uma letra mai�scula */
int has_uppercase(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (isupper(str[i])) {
            return 1;
        }
    }
    return 0;
}

/* Fun��o para verificar se uma palavra cont�m uma letra min�scula */
int has_lowercase(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (islower(str[i])) {
            return 1;
        }
    }
    return 0;
}

/* Fun��o para verificar se uma palavra cont�m um n�mero */
int has_number(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            return 1;
        }
    }
    return 0;
}

/* Fun��o para verificar se uma palavra cont�m um s�mbolo */
int has_symbol(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == '!' || str[i] == '?' || str[i] == '#' || str[i] == '@' || str[i] == '$') {
            return 1;
        }
    }
    return 0;
}

/* Fun��o para escrever as palavras reservadas*/
char** tiping_reserved_word() {
    int i, num_reserved_words = 0;
    printf("Para comecar, digite a quantidade de palavras reservadas que nao poderao estar inclusas na senha: ");
    scanf("%d", &num_reserved_words);
    char** reserved_words = malloc(num_reserved_words * sizeof(char*)); // aloca��o din�mica do array de ponteiros
    for (i = 0; i < num_reserved_words; i++) {
        printf("Digite uma palavra reservada: ");
        reserved_words[i] = malloc(50 * sizeof(char)); // aloca��o din�mica da string
        scanf("%s", reserved_words[i]); // ler a palavra completa com %s
        getchar();
    }
    return reserved_words; // retornar o pr�prio array
}

/* Fun��o para verificar se uma palavra � uma palavra reservada */
int is_reserved_word(char *reserved_words[], int num_reserved_words, char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    for (int i = 0; i < num_reserved_words; i++) {
        if (strstr(str, reserved_words[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

/*Fun��o para verificar se o usu�rio quer digitar outra senha*/
int continuar() {
    char opcao;
    printf("Deseja digitar uma nova senha? Digite S para sim ou N para nao: ");
    scanf("%s", &opcao);
    if(opcao == 'S' || opcao == 's'){
        return 1;
    }
    printf("O programa sera encerrado.");

    return 0;
}

/* Fun��o principal que chama todas as fun��es*/
int funcaoPrincipal(){
    char password[100];
    int len, valid = 1;
    char *words = tiping_reserved_word();
    int lengthWords = sizeof(words) / sizeof(int);
    if(lengthWords < 2){
        lengthWords = 1;
    }

    /* Leitura da senha */
    printf("Digite a senha: ");
    scanf("%s", &password);

    /* Verifica��o do tamanho da senha */
    len = strlen(password);
    if (len < 8) {
        valid = 0;
        printf("Senha deve conter pelo menos 8 caracteres.\n");
    }

    /* Verifica��o de mai�sculas, min�sculas, n�meros, s�mbolos e pal�ndromo */
    if (!has_uppercase(password)) {
        valid = 0;
        printf("Senha deve conter pelo menos uma letra maiuscula.\n");
    }
    if (!has_lowercase(password)) {
        valid = 0;
        printf("Senha deve conter pelo menos uma letra minuscula.\n");
    }
    if (!has_number(password)) {
        valid = 0;
        printf("Senha deve conter pelo menos um numero.\n");
    }
    if (!has_symbol(password)) {
        valid = 0;
        printf("Senha deve conter pelo menos um dos seguintes simbolos: !, ?, #, @, $.\n");
    }
    if (is_palindrome(password)) {
        valid = 0;
        printf("Senha nao pode ser um palindromo.\n");
    }

    /* Verifica��o de palavra reservada*/
    if (is_reserved_word(words, lengthWords, password)) {
        valid = 0;
        printf("Senha nao pode conter uma palavra reservada.\n");
    }

    /* Verifica��o final */
    if (valid) {
        printf("Senha valida.\n");
    }
    else {
        printf("Senha invalida.\n");
    }
}

/* Chamada da Main */
int main() {
    printf("Este programa e um desafio feito para a materia de LP do segundo semestre. \n O mesmo foi elaborado por: \n Janaina Aleixo RA: 2760482221013 \n Mirela Neder RA: 2760482221001 \n Thalita Thie RA: 2760482221004 \n O principal objetivo do programa e testar uma senha e ver se ela se enquadra nos requisitos. \n ");
    /*La�o de repeti��o para rodas o programa quantas vezes o usu�rio quiser*/
    do{
        funcaoPrincipal();
    }
    while(continuar());
    return 0;
}
