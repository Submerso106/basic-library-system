#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct livro // Struct para armazenar os dados dos livros.
{
    int codigo;
    char titulo[50];  
    char autor[30];
    char area[30];
    char editora[30];
    int ano;
};

#define TAMANHO_ACERVO 20
struct livro acervo[TAMANHO_ACERVO]; // Acervo de livros.
int livrosCadastrados = 0; // Contador de livros cadastrados usado para controlar o acervo.

/* 
    Essa função pede os dados do livro a ser cadastrado ao usuário.
    Caso não haja espaço no acervo, a função avisa o usuário e da a opção de retornar ao menu principal.
    Ao finalizar o cadastro, a função é reativada, dando a opção de cadastrar mais livros ou retornar.
*/
int cadastrarLivros() {

    int espaçoDisponivel = TAMANHO_ACERVO - livrosCadastrados;

    if (espaçoDisponivel <= 0) { // Faz controle do espaço do acervo.
        printf("\nEspaço insuficiente no acervo!\n");
        int opção;
        printf("0 - Retornar ao menu\n");
        scanf("%d", &opção);
        return 0;
    }

    // Para cada livro a ser cadastrado, solicita os dados ao usuário.
    
    printf("\nCadastro do livro %d. - Espaço disponível: %d\n", livrosCadastrados + 1, espaçoDisponivel);
    printf("0 - Retornar ao menu\n");
    printf("1 - Começar cadastro\n");
    int opção;
    scanf("%d", &opção);
    if (opção == 0) {
        return 0;
    }

    printf("\nCódigo: "); // Solicita os dados ao usuário.
    scanf("%d", &acervo[livrosCadastrados].codigo); 
    fflush(stdin);
    printf("Título: ");
    scanf(" %[^\n]s", acervo[livrosCadastrados].titulo); // Lê uma string com espaços.
    fflush(stdin);
    printf("Autor: ");
    scanf(" %[^\n]s", acervo[livrosCadastrados].autor);
    fflush(stdin);
    printf("Área: ");
    scanf(" %[^\n]s", acervo[livrosCadastrados].area);
    fflush(stdin);
    printf("Editora: ");
    scanf(" %[^\n]s", acervo[livrosCadastrados].editora);
    fflush(stdin);
    printf("Ano de publicação: ");
    scanf("%d", &acervo[livrosCadastrados].ano);
    fflush(stdin);

    livrosCadastrados++;
    
    cadastrarLivros(); // Retorna para o menu de cadastro.
}

int imprimirLivros() { // Imprime no terminal os livros cadastrados.

    printf("\n\tAcervo\n\n");
    for (int i = 0; i < livrosCadastrados; i++) { // Percorre o acervo e imprime os dados de cada livro.
        printf("Codigo: %d\n", acervo[i].codigo);
        printf("Título: %s\n", acervo[i].titulo);
        printf("Autor: %s\n", acervo[i].autor);
        printf("Área: %s\n", acervo[i].area);
        printf("Editora: %s\n", acervo[i].editora);
        printf("Ano de publicação: %d\n\n", acervo[i].ano);
    }
    printf("0 - Retornar ao menu\n");
    int retorno; // Utilizada para aguardar a entrada do usuário para retornar ao menu.
    scanf("%d", &retorno);
    fflush(stdin);
    return 0;
}

int pesquisarLivro() { // Pesquisa o livro no acervo pelo seu código

    int codigo;
    printf("\n\tPesquisa de Livro por Código\n\n");
    printf("0 - Retornar ao menu\n");
    printf("Digite o código do livro: ");
    scanf("%d", &codigo);
    fflush(stdin);
    if (codigo == 0) {
        return 0;
    }

    for (int i = 0; i < livrosCadastrados; i++) { // Percorre o acervo em busca do código informado.
        if (acervo[i].codigo == codigo) { // Se encontrar um livro com o código informado, imprime os dados.
            printf("\n\nLivro encontrado:\n");
            printf("Código: %d\n", acervo[i].codigo);
            printf("Título: %s\n", acervo[i].titulo);
            printf("Autor: %s\n", acervo[i].autor);
            printf("Área: %s\n", acervo[i].area);
            printf("Editora: %s\n", acervo[i].editora);
            printf("Ano de publicação: %d\n", acervo[i].ano);
            printf("\n0 - Retornar o menu\n");
            scanf("%d", &codigo);
            fflush(stdin);
            return 0;
        }
    }
    printf("\n\n\tLivro não encontrado!\n"); // Caso não encontre o livro, avisa o usuário.
    printf("0 - Retornar ao menu\n");
    printf("1 - Tentar Novamente\n");
    int opção;
    scanf("%d", &opção);
    if (opção == 1) {
        pesquisarLivro();
    }
    return 0;
}

int ordenarLivros() {

    bool ordenado = false; 
    while (!ordenado) // Equanto não estiver ordenado, continua o loop.
    {
        ordenado = true; // Inicia como ordenado. Caso não haja nenhuma troca, o loop termina.
        for (int i = 1; i < livrosCadastrados; i++)
        {
            if (acervo[i-1].ano > acervo[i].ano) {
                struct livro temp = acervo[i-1];
                acervo[i-1] = acervo[i];
                acervo[i] = temp;
                ordenado = false; // Se houve troca, ainda não está ordenado, reinicia o loop.
            }
        }  
    }
    printf("\nLivros ordenados!\n");
    printf("0 - Retornar ao menu\n");
    int retorno; // Utilizada para aguardar a entrada do usuário para retornar ao menu.
    scanf("%d", &retorno);
    return 0;
}

void main() {

    int opcao;
    printf("\nO que você deseja fazer?\n"); // Menu principal.
    printf("1 - Cadastrar livros\n");
    printf("2 - Imprimir acervo de livros\n");
    printf("3 - Pesquisar livro por código\n");
    printf("4 - Ordenar livros por data de publicação\n");
    printf("0 - Finalizar Programa\n");
    scanf("%d", &opcao);
    fflush(stdin);

    int returnValue; // Variável usada para retornar o usuário ao menu principal.

    switch (opcao) { // Chama a função escolhida pelo usuário.
        case 0:
            printf("Finalizando programa...\n");
            returnValue = -1;
            break;
        case 1:
            returnValue = cadastrarLivros();
            break;
        case 2:
            returnValue = imprimirLivros();
            break;
        case 3:
            returnValue = pesquisarLivro();
            break;
        case 4:
            returnValue = ordenarLivros();
            break;
        default:
            printf("Opção inválida!\n");
            returnValue = 0;
    }

    if (returnValue == 0) { // Caso alguma função retorne 0, o usuário volta ao menu principal.
        main();
    }

}
