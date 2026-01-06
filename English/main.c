#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct book // Struct para armazenar os dados dos books.
{
    int code;
    char title[50];  
    char author[30];
    char area[30];
    char publisher[30];
    int year;
};

#define COLLECTION_SIZE 20
struct book collection[COLLECTION_SIZE]; // Book collection.
int registredBooks = 0; // Book counter, used to monitor the collection

/* 
    This functions asks for the book's information to the user.
    In case there's no space available, the function warns the user and gives it the option of returning to the main menu.
    Upon finishing, the function gives the option to register another book or to return to the main menu.
*/
int RegisterBooks() {

    int availableSpace = COLLECTION_SIZE - registredBooks;

    if (availableSpace <= 0) { // Manages the available space
        printf("\nNot enough space in the collection!\n");
        int option;
        printf("0 - Return to the menu\n");
        scanf("%d", &option);
        return 0;
    }

    // Para cada book a ser cadastrado, solicita os dados ao usuário.
    
    printf("\nBook number %d. - Available Space: %d\n", registredBooks + 1, availableSpace);
    printf("0 - Return to the menu\n");
    printf("1 - Register Book\n");
    int option;
    scanf("%d", &option);
    if (option == 0) {
        return 0;
    }

    printf("\nCode: "); // Solicita os dados ao usuário.
    scanf("%d", &collection[registredBooks].code); 
    fflush(stdin);
    printf("Title: ");
    scanf(" %[^\n]s", collection[registredBooks].title); // Lê uma string com espaços.
    fflush(stdin);
    printf("Author: ");
    scanf(" %[^\n]s", collection[registredBooks].author);
    fflush(stdin);
    printf("Area: ");
    scanf(" %[^\n]s", collection[registredBooks].area);
    fflush(stdin);
    printf("Publisher: ");
    scanf(" %[^\n]s", collection[registredBooks].publisher);
    fflush(stdin);
    printf("Publish Year: ");
    scanf("%d", &collection[registredBooks].year);
    fflush(stdin);

    registredBooks++; 
    
    RegisterBooks(); // Return to the register menu
}

int PrintBooks() { // Print in the terminal all of the registered books

    printf("\n\tCollection\n\n");
    for (int i = 0; i < registredBooks; i++) { // Iterates over the collection and print the book's information
        printf("Code: %d\n", collection[i].code);
        printf("Title: %s\n", collection[i].title);
        printf("Author: %s\n", collection[i].author);
        printf("Area: %s\n", collection[i].area);
        printf("Publisher: %s\n", collection[i].publisher);
        printf("Publish Year: %d\n\n", collection[i].year);
    }
    printf("0 - Return to the menu\n");
    int returnValue; // Used to wait the user's input to return to the menu
    scanf("%d", &returnValue);
    fflush(stdin);
    return 0;
}

int SearchBook() { // Search the book in the collection by it's code

    int code;
    printf("\n\tSearch Book by Code\n\n");
    printf("0 - Return to the menu\n");
    printf("Type the books code: ");
    scanf("%d", &code);
    fflush(stdin);
    if (code == 0) {
        return 0;
    }

    for (int i = 0; i < registredBooks; i++) { // Iterates over collection looking for the given code
        if (collection[i].code == code) { // If a book is found, print it's information
            printf("\n\nbook encontrado:\n");
            printf("Código: %d\n", collection[i].code);
            printf("Título: %s\n", collection[i].title);
            printf("Author: %s\n", collection[i].author);
            printf("Area: %s\n", collection[i].area);
            printf("Publisher: %s\n", collection[i].publisher);
            printf("Publish Year: %d\n", collection[i].year);
            printf("\n0 - Retornar o menu\n");
            scanf("%d", &code);
            fflush(stdin);
            return 0;
        }
    }
    printf("\n\n\tbook not found!\n"); // If no book is found, warn the user.
    printf("0 - Return to the menu\n");
    printf("1 - Try again\n");
    int option;
    scanf("%d", &option);
    if (option == 1) {
        SearchBook();
    }
    return 0;
}

int OrganizeBooks() {

    bool organized = false; 
    while (!organized) // While not organized, continues the loop.
    {
        organized = true; // Start as organized. If no switch occours, end the loop.
        for (int i = 1; i < registredBooks; i++)
        {
            if (collection[i-1].year > collection[i].year) {
                struct book temp = collection[i-1];
                collection[i-1] = collection[i];
                collection[i] = temp;
                organized = false; // If a switch occours, it is not organized, continues to the next loop.
            }
        }  
    }
    printf("\nbooks organized!\n");
    printf("0 - Return to the menu\n");
    int returnValue; // Used to wait the user's input to return to the menu
    scanf("%d", &returnValue);
    return 0;
}

void main() {

    int option;
    printf("\nWhat do you want to do?\n"); // Main menu.
    printf("1 - Register books\n");
    printf("2 - Print book collection\n");
    printf("3 - Search book by code\n");
    printf("4 - Organize books by publish year\n");
    printf("0 - End program\n");
    scanf("%d", &option);
    fflush(stdin);

    int returnValue; // Variable used to return to the main menu

    switch (option) { // Calls the function desired by the user.
        case 0:
            printf("Finalizando programa...\n");
            returnValue = -1;
            break;
        case 1:
            returnValue = RegisterBooks();
            break;
        case 2:
            returnValue = PrintBooks();
            break;
        case 3:
            returnValue = SearchBook();
            break;
        case 4:
            returnValue = OrganizeBooks();
            break;
        default:
            printf("Invalid Option!\n");
            returnValue = 0;
    }

    if (returnValue == 0) { // In case some function returns 0, return to the main menu.
        main();
    }

}
