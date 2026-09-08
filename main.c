#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Todo {
    char title[100];
    bool completed;
};

int main() {
    int dataSize = 0;
    struct Todo *todos = NULL; 

    FILE *pFile = fopen("todolist.txt", "r");
    if (pFile == NULL) {
        pFile = fopen("todolist.txt", "w+");
        if (pFile == NULL) {
            printf("Error creating file!\n");
            return 1;
        }
    }

    char buffer[128];
    while(fgets(buffer, sizeof(buffer), pFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *token = strtok(buffer, "|");
        char *tokens[2];
        int count = 0;
        while(token != NULL) {
            tokens[count] = token;
            count++;
            token = strtok(NULL, "|");
        }

        dataSize++;
        struct Todo newTodo;
        strcpy(newTodo.title, tokens[0]);
        newTodo.completed = strcmp(tokens[1],"1") == 0;
        struct Todo *temp = (struct Todo *) realloc(todos, dataSize * sizeof(struct Todo));

        if(temp == NULL) return 1;
        todos = temp;
        temp = NULL;
        todos[dataSize - 1] = newTodo;  
    }
    
    for(int i = 0; i < dataSize; i++) {
        printf("%s | %s\n", todos[i].title, todos[i].completed ? "Completed" : "Not Completed");
    }
    
    free(todos);
    todos = NULL;

    fclose(pFile);

    return 0;
}