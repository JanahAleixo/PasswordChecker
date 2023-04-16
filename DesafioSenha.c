#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Função para verificar se uma palavra é um palíndromo */
int is_palindrome(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

/* Função para verificar se uma palavra contém uma letra maiúscula */
int has_uppercase(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (isupper(str[i])) {
            return 1;
        }
    }
    return 0;
}

/* Função para verificar se uma palavra contém uma letra minúscula */
int has_lowercase(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (islower(str[i])) {
            return 1;
        }
    }
    return 0;
}

/* Função para verificar se uma palavra contém um número */
int has_number(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            return 1;
        }
    }
    return 0;
}

/* Função para verificar se uma palavra contém um símbolo */
int has_symbol(char *str) {
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == '!' || str[i] == '?' || str[i] == '#' || str[i] == '@' || str[i] == '$') {
            return 1;
        }
    }
    return 0;
}

/* Função para escrever as palavras reservadas*/
char** tiping_reserved_word() {
    int i, num_reserved_words = 0;
    printf("Para comecar, digite a quantidade de palavras reservadas que nao poderao estar inclusas na senha: ");
    scanf("%d", &num_reserved_words);
    char** reserved_words = malloc(num_reserved_words * sizeof(char*)); // alocação dinâmica do array de ponteiros
    for (i = 0; i < num_reserved_words; i++) {
        printf("Digite uma palavra reservada: ");
        reserved_words[i] = malloc(50 * sizeof(char)); // alocação dinâmica da string
        scanf("%s", reserved_words[i]); // ler a palavra completa com %s
        getchar();
    }
    return reserved_words; // retornar o próprio array
}

/* Função para verificar se uma palavra é uma palavra reservada */
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

/*Função para verificar se o usuário quer digitar outra senha*/
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

/* Função principal que chama todas as funções*/
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

    /* Verificação do tamanho da senha */
    len = strlen(password);
    if (len < 8) {
        valid = 0;
        printf("Senha deve conter pelo menos 8 caracteres.\n");
    }

    /* Verificação de maiúsculas, minúsculas, números, símbolos e palíndromo */
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

    /* Verificação de palavra reservada*/
    if (is_reserved_word(words, lengthWords, password)) {
        valid = 0;
        printf("Senha nao pode conter uma palavra reservada.\n");
    }

    /* Verificação final */
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
    /*Laço de repetição para rodas o programa quantas vezes o usuário quiser*/
    do{
        funcaoPrincipal();
    }
    while(continuar());
    return 0;
}
