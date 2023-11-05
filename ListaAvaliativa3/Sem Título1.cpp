#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o de uma estrutura para um n� da fila
struct Node {
    char title[100];
    char author[100];
    struct Node* next;
};

// Fun��o para criar um novo n� da fila
struct Node* createNode(char title[], char author[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->next = NULL;
    return newNode;
}

// Fun��o para salvar a fila em um arquivo
void saveQueueToFile(struct Node* front) {
    FILE *arquivo = fopen("fila_de_livros.txt", "w");
    if (arquivo == NULL) {
        printf("N�o foi poss�vel abrir o arquivo da fila para escrita.\n");
        return;
    }
    
    struct Node* current = front;
    while (current != NULL) {
        fprintf(arquivo, "%s;%s\n", current->title, current->author);
        current = current->next;
    }
    
    fclose(arquivo);
}

// Fun��o para enfileirar (adicionar um n� � fila)
void enqueue(struct Node** front, struct Node** rear, char title[], char author[]) {
    struct Node* newNode = createNode(title, author);
    if (*rear == NULL) {
        *front = newNode;
        *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
    // Salva a fila no arquivo ap�s adicionar um livro
    saveQueueToFile(*front);
}

// Fun��o para desenfileirar (remover um n� da fila)
void dequeue(struct Node** front) {
    if (*front == NULL) {
        printf("A fila de livros est� vazia.\n");
    } else {
        struct Node* temp = *front;
        *front = (*front)->next;
        free(temp);
        // Salva a fila no arquivo ap�s retirar um livro
        saveQueueToFile(*front);
    }
}

// Fun��o para imprimir a fila
void printQueue(struct Node* front) {
    struct Node* current = front;
    while (current != NULL) {
        printf("Livro: %s, Autor: %s\n", current->title, current->author);
        current = current->next;
    }
}

// Defini��o de uma estrutura para um n� da pilha
struct StackNode {
    char title[100];
    char author[100];
    struct StackNode* next;
};

// Fun��o para salvar a pilha em um arquivo
void saveStackToFile(struct StackNode* top) {
    FILE *arquivo = fopen("pilha_de_livros.txt", "w");
    if (arquivo == NULL) {
        printf("N�o foi poss�vel abrir o arquivo da pilha para escrita.\n");
        return;
    }
    
    struct StackNode* current = top;
    while (current != NULL) {
        fprintf(arquivo, "%s;%s\n", current->title, current->author);
        current = current->next;
    }
    
    fclose(arquivo);
}

// Fun��o para criar um novo n� da pilha
struct StackNode* createStackNode(char title[], char author[]) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->next = NULL;
    return newNode;
}

// Fun��o para empilhar (adicionar um n� � pilha)
void push(struct StackNode** top, char title[], char author[]) {
    struct StackNode* newNode = createStackNode(title, author);
    if (*top == NULL) {
        *top = newNode;
    } else {
        newNode->next = *top;
        *top = newNode;
    }
    saveStackToFile(*top);
}

// Fun��o para desempilhar (remover o �ltimo n� da pilha)
void pop(struct StackNode** top) {
    if (*top == NULL) {
        printf("A pilha de livros est� vazia.\n");
    } else {
        struct StackNode* current = *top;
        struct StackNode* prev = NULL;
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        if (prev != NULL) {
            prev->next = NULL;
        } else {
            *top = NULL;
        }
        free(current);
        // Salva a pilha no arquivo ap�s retirar um livro
        saveStackToFile(*top);
    }
}

// Fun��o para imprimir a pilha
void printStack(struct StackNode* top) {
    struct StackNode* current = top;
    while (current != NULL) {
        printf("Livro: %s, Autor: %s\n", current->title, current->author);
        current = current->next;
    }
}

int main() {
    struct Node* front = NULL;
    struct Node* rear = NULL;
    struct StackNode* top1 = NULL;
    struct StackNode* top = NULL;

    int choice;
    char title[100];
    char author[100];

    // Carrega a fila a partir do arquivo no in�cio
    FILE *fila_arquivo = fopen("fila_de_livros.txt", "r");
    if (fila_arquivo != NULL) {
        while (fscanf(fila_arquivo, "%99[^;];%99[^\n]\n", title, author) == 2) {
            enqueue(&front, &rear, title, author);
        }
        fclose(fila_arquivo);
    }

    // Carrega a pilha a partir do arquivo no in�cio
    FILE *pilha_arquivo = fopen("pilha_de_livros.txt", "r");
    if (pilha_arquivo != NULL) {
        while (fscanf(pilha_arquivo, "%99[^;];%99[^\n]\n", title, author) == 2) {
            push(&top1, title, author);
        }
        while (fscanf(pilha_arquivo, "%99[^;];%99[^\n]\n", title, author) == 2) {
            push(&top, title, author);
        }
        fclose(pilha_arquivo);
    }

    while (1) {
        printf("\nOp��es:\n");
        printf("1. Adicionar um livro � fila\n");
        printf("2. Retirar um livro da fila\n");
        printf("3. Visualizar a fila\n");
        printf("4. Adicionar um livro � pilha\n");
        printf("5. Remover um livro da pilha\n");
        printf("6. Visualizar a pilha\n");
        printf("7. Sair\n");
        printf("Escolha a op��o: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o t�tulo do livro: ");
                scanf(" %[^\n]", title);
                printf("Digite o autor do livro: ");
                scanf(" %[^\n]", author);
                enqueue(&front, &rear, title, author);
                break;

            case 2:
                dequeue(&front);
                break;

            case 3:
                if (front == NULL) {
                    printf("A fila de livros est� vazia.\n");
                } else {
                    printf("Fila de Livros:\n");
                    printQueue(front);
                }
                break;

            case 4:
                printf("Digite o t�tulo do livro: ");
                scanf(" %[^\n]", title);
                printf("Digite o autor do livro: ");
                scanf(" %[^\n]", author);
                push(&top, title, author);
                break;

            case 5:
                pop(&top);
                break;

            case 6:
                if (top == NULL) {
                    printf("A pilha de livros est� vazia.\n");
                } else {
                    printf("Pilha de Livros (�ltimo a entrar - primeiro a sair):\n");
                    printStack(top);
                }
                break;

            case 7:
                // Libera a mem�ria alocada para a fila (desaloca os n�s)
                while (front != NULL) {
                    struct Node* temp = front;
                    front = front->next;
                    free(temp);
                }
                // Salva a fila no arquivo antes de sair
                saveQueueToFile(front);

                // Libera a mem�ria alocada para a pilha (desaloca os n�s)
                while (top != NULL) {
                    struct StackNode* temp = top;
                    top = top->next;
                    free(temp);
                }
                // Salva a pilha no arquivo antes de sair
                saveStackToFile(top);
                return 0;

            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    }

    return 0;
}

