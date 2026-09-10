#include <stdbool.h>
#include <stdio.h>

typedef struct Todo {
    char * title;
    bool completed;
}Todo;

void rewriteFile(Todo * todos, int dataSize) {
    FILE *pFile = fopen("todolist.txt", "w");
    for(int i = 0; i < dataSize; i++) {
        fprintf(pFile, "%s|%s\n", todos[i].title, todos[i].completed ? "0" : "1");
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

void completeTodo(Todo * todos, int dataSize, int todoNum ) {
    todos[todoNum].completed = !(todos[todoNum].completed);
    rewriteFile(todos, dataSize);
}