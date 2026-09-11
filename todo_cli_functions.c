#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Todo {
    char title[100];
    bool completed;
}Todo;

void rewriteFile(Todo * todos, int dataSize) {
    FILE *pFile = fopen("todolist.txt", "w");
    for(int i = 0; i < dataSize; i++) {
        fprintf(pFile,"%s|%s\n", todos[i].title, todos[i].completed ? "1" : "0");
    }
    fclose(pFile);
}

void listTodo(Todo * todos, int dataSize) {
    printf("==============================\n");
    for(int i = 0; i < dataSize; i++) {
        printf("%d. %s | %s\n", i + 1, todos[i].title, todos[i].completed ? "Completed" : "Not Completed");
    }
    printf("==============================\n");
}

void completeTodo(Todo *todos, int dataSize, int todoNum ) {
    todos[todoNum - 1].completed = !(todos[todoNum - 1].completed);
    rewriteFile(todos, dataSize);
}

void addTodo(Todo **todos, int *pDataSize, char *title) {
    (*pDataSize)++;
    Todo newTodo = {
        .completed = false
    };
    strcpy(newTodo.title, title);
    *todos = realloc(*todos, *pDataSize * sizeof(Todo));
    (*todos)[*pDataSize - 1] = newTodo;
    rewriteFile(*todos, *pDataSize);
}

void deleteTodo(Todo **todos, int *pDataSize, int todoNum) {
    int index = todoNum - 1;
    for(int i = index; i < (*pDataSize) - 1; i++) {
        (*todos)[i] = (*todos)[i + 1];
    }

    (*pDataSize)--;

    *todos = realloc(*todos, (*pDataSize) * sizeof(Todo));
    rewriteFile(*todos, *pDataSize);
}