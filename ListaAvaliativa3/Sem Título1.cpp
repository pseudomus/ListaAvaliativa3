#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de uma estrutura para um nó da fila
struct Node {
    char title[100];
    char author[100];
    struct Node* next;
};

// Função para criar um novo nó da fila
struct Node* createNode(char title[], char author[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->next = NULL;
    return newNode;
}

// Função para salvar a fila em um arquivo
void saveQueueToFile(struct Node* front) {
    FILE *arquivo = fopen("fila_de_livros.txt", "w");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo da fila para escrita.\n");
        return;
    }
    
    struct Node* current = front;
    while (current != NULL) {
        fprintf(arquivo, "%s;%s\n", current->title, current->author);
        current = current->next;
    }
    
    fclose(arquivo);
}

// Função para enfileirar (adicionar um nó à fila)
void enqueue(struct Node** front, struct Node** rear, char title[], char author[]) {
    struct Node* newNode = createNode(title, author);
    if (*rear == NULL) {
        *front = newNode;
        *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
    // Salva a fila no arquivo após adicionar um livro
    saveQueueToFile(*front);
}

// Função para desenfileirar (remover um nó da fila)
void dequeue(struct Node** front) {
    if (*front == NULL) {
        printf("A fila de livros está vazia.\n");
    } else {
        struct Node* temp = *front;
        *front = (*front)->next;
        free(temp);
        // Salva a fila no arquivo após retirar um livro
        saveQueueToFile(*front);
    }
}

// Função para imprimir a fila
void printQueue(struct Node* front) {
    struct Node* current = front;
    while (current != NULL) {
        printf("Livro: %s, Autor: %s\n", current->title, current->author);
        current = current->next;
    }
}

// Definição de uma estrutura para um nó da pilha
struct StackNode {
    char title[100];
    char author[100];
    struct StackNode* next;
};

// Função para salvar a pilha em um arquivo
void saveStackToFile(struct StackNode* top) {
    FILE *arquivo = fopen("pilha_de_livros.txt", "w");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo da pilha para escrita.\n");
        return;
    }
    
    struct StackNode* current = top;
    while (current != NULL) {
        fprintf(arquivo, "%s;%s\n", current->title, current->author);
        current = current->next;
    }
    
    fclose(arquivo);
}

// Função para criar um novo nó da pilha
struct StackNode* createStackNode(char title[], char author[]) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->next = NULL;
    return newNode;
}

// Função para empilhar (adicionar um nó à pilha)
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

// Função para desempilhar (remover o último nó da pilha)
void pop(struct StackNode** top) {
    if (*top == NULL) {
        printf("A pilha de livros está vazia.\n");
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
        // Salva a pilha no arquivo após retirar um livro
        saveStackToFile(*top);
    }
}

// Função para imprimir a pilha
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

    // Carrega a fila a partir do arquivo no início
    FILE *fila_arquivo = fopen("fila_de_livros.txt", "r");
    if (fila_arquivo != NULL) {
        while (fscanf(fila_arquivo, "%99[^;];%99[^\n]\n", title, author) == 2) {
            enqueue(&front, &rear, title, author);
        }
        fclose(fila_arquivo);
    }

    // Carrega a pilha a partir do arquivo no início
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
        printf("\nOpções:\n");
        printf("1. Adicionar um livro à fila\n");
        printf("2. Retirar um livro da fila\n");
        printf("3. Visualizar a fila\n");
        printf("4. Adicionar um livro à pilha\n");
        printf("5. Remover um livro da pilha\n");
        printf("6. Visualizar a pilha\n");
        printf("7. Sair\n");
        printf("Escolha a opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o título do livro: ");
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
                    printf("A fila de livros está vazia.\n");
                } else {
                    printf("Fila de Livros:\n");
                    printQueue(front);
                }
                break;

            case 4:
                printf("Digite o título do livro: ");
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
                    printf("A pilha de livros está vazia.\n");
                } else {
                    printf("Pilha de Livros (último a entrar - primeiro a sair):\n");
                    printStack(top);
                }
                break;

            case 7:
                // Libera a memória alocada para a fila (desaloca os nós)
                while (front != NULL) {
                    struct Node* temp = front;
                    front = front->next;
                    free(temp);
                }
                // Salva a fila no arquivo antes de sair
                saveQueueToFile(front);

                // Libera a memória alocada para a pilha (desaloca os nós)
                while (top != NULL) {
                    struct StackNode* temp = top;
                    top = top->next;
                    free(temp);
                }
                // Salva a pilha no arquivo antes de sair
                saveStackToFile(top);
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}

