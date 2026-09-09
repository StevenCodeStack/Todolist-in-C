#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Todo {
    char title[100];
    bool completed;
};

bool rewriteFile(struct Todo* todos, int* dataSize) {
    FILE *pFile = fopen("todolist.txt", "w");
    if(pFile == NULL) return false;
    for(int i = 0; i < *dataSize; i++) {
        fprintf(pFile, "%s|%s\n", todos[i].title, todos[i].completed ? "1" : "0");
    }
    fclose(pFile);
    return true;

}

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

    fclose(pFile);
    
    int choice = 0;
    bool exit = false;

    while(!exit) {
        printf("Welcome to todolist app, terminal based\n");
        printf("1. List all todo-s\n");
        printf("2. Add a new todo\n");
        printf("3. Delete a todo\n");
        printf("4. Complete a todo\n");
        printf("5. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: {
                getchar();

                printf("=========================\n");
                for(int i = 0; i < dataSize; i++) {
                    printf("%d. %s | %s\n",i + 1, todos[i].title, todos[i].completed ? "Completed" : "Not Completed");
                }
                printf("=========================\n");
                break;
            }
  
            case 2: {
                getchar();

                dataSize++;
                char title[100];
                printf("Enter the title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';

                struct Todo newTodo;
                newTodo.completed = false;
                strcpy(newTodo.title, title);
                todos = (struct Todo*) realloc(todos,dataSize * sizeof(struct Todo));
                todos[dataSize - 1] = newTodo;

                FILE *pFile = fopen("todolist.txt", "a");
                fprintf(pFile, "%s|%s\n",newTodo.title, newTodo.completed ? "1" : "0");
                fclose(pFile);

                printf("=========================\n");
                printf("Success!");
                printf("=========================\n");
                break;
            }
   
            case 3: {
                getchar();

                printf("=========================\n");

                for(int i = 0; i < dataSize; i++) {
                    printf("%d. %s | %s\n",i + 1, todos[i].title, todos[i].completed ? "Completed" : "Not Completed");
                }
                printf("=========================\n");

                int index = -1;
                printf("Choose a todo to delete: ");
                scanf("%d", &index);
                if(index < 0 || index > dataSize) {
                    printf("Todo at index %d does not exist", index);
                    break;
                }
                index--;
                while(index < dataSize - 1) {
                    todos[index] = todos[index + 1];
                    index += 1;
                }
                dataSize--;
                todos = (struct Todo*) realloc(todos, dataSize * sizeof(struct Todo));

                bool result = rewriteFile(todos, &dataSize);

                if(!result) {
                    printf("Failed to delete the data");
                    return 1;
                }
                printf("Successfully delete the data");

                break;
            }

            case 4: {
                getchar();

                printf("=========================\n");

                for(int i = 0; i < dataSize; i++) {
                    if(todos[i].completed) continue;
                    printf("%d. %s | %s\n",i + 1, todos[i].title, todos[i].completed ? "Completed" : "Not Completed");
                }
                printf("=========================\n");

                int index = -1;
                printf("Choose a todo to complete: ");
                scanf("%d", &index);
                if(index < 0 || index > dataSize) {
                    printf("Todo at index %d does not exist", index);
                    break;
                }
                todos[index - 1].completed = true;

                bool result = rewriteFile(todos, &dataSize);
                if(result) printf("Success!\n");
                else {
                    printf("Failed\n");
                    return 1;
                }

                break;
            }

            case 5: {
                getchar();

                exit = true;
                printf("Goodbye\n");
                break;
            }
            default: {
                printf("Option %d does not exist", choice);
                break;
            }
          
        }
        choice = 0;
    }
    
    free(todos);
    todos = NULL;


    return 0;
}