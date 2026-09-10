#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "todo_cli_functions.c"



int main(int argc, char *argv[]) {

    char * commands[] = {"ls", "complete", "add"};
    int commandsLength = sizeof(commands) / sizeof(commands[0]);

    if(argc <= 1) {
        printf("Welcome to Todolist Terminal based.\n");
        printf("Basic commands:\n");
        for(int i = 0; i < commandsLength; i++) {
            printf("%d. %s\n", i + 1, commands[i]);
        }
        return 0;
    }

    FILE *pFile = fopen("todolist.txt", "r");
    if(pFile == NULL) {
        pFile = fopen("todolist.txt", "w+");
        if(pFile == NULL) {
            printf("Failed to open or create a file");
            return 1;
        }
    }
    
    int dataSize = 0;
    Todo *todos = (Todo *) malloc(dataSize * sizeof(Todo)); // NULL

    char buffer[100];
    char delimiter[] = "|";

    while(fgets(buffer, sizeof(buffer), pFile) != NULL) {
        Todo newTodo;
        char *token = strtok(buffer, delimiter);
        strcpy(newTodo.title, token);

        token = strtok(NULL, delimiter);
        char *completedNum = token;
        completedNum[strcspn(completedNum, "\n")] = '\0';

        // printf("data: %s\n", completedNum);
        // printf("comparison:%d\n", strcmp(completedNum, "1"));

        newTodo.completed = (strcmp(completedNum, "1") == 0);

        dataSize++;
        todos = realloc(todos, dataSize * sizeof(Todo));
        todos[dataSize - 1] = newTodo;
    }

    fclose(pFile);

    char * command = argv[1];
    int index = -1;
    for(int i = 0; i < commandsLength; i++) {
        if(strcmp(command, commands[i]) == 0) index = i; 
    }

    switch(index) {
        case -1: {
            printf("Command does not exist\n");
            break;
        }
        case 0: {
            listTodo(todos, dataSize);
            break;
        }
        case 1: {
            if(argc <= 2) {
                printf("Command: todo complete <todo number>\n");
                break;
            }
            int todoNum = atoi(argv[2]);
            if(todoNum == 0) {
                printf("Enter a positive number (num >= 1)\n");
                break;
            }
            if(todoNum > dataSize) {
                printf("Out of bounds. Datasize is only %d\n", dataSize);
                break;
            }
            completeTodo(todos, dataSize, todoNum);
            break;
        }
        case 2: {
            if(argc <= 2) {
                printf("Command: todo add \"<title>\"\n");
                break;
            }
            char *check = strstr(argv[2], "|");
            if(check != NULL) {
                printf("Title cannot contain '%s' as it is used as delimiter\n", delimiter);
                break;
            }
            addTodo(todos, &dataSize, argv[2]);
            break;
        }
    }

    free(todos);
    todos = NULL;
    return 0;
}

