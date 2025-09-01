#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DELIMS " \t\n"

typedef struct list {
    void *data;
    struct list *next;
} list;

static void prompt(void) 
{
    printf("shell-0.1$ ");
} 

static list * parse(char *line) 
{
    list * head = malloc(sizeof(list));
    head->data = NULL;
    head->next = NULL;
    list * ptr = head;
    
    char *token = strtok(line, DELIMS);
    while (token != NULL)
    {
        list *p = malloc(sizeof(list));
        p->data = malloc(sizeof(token));
        memcpy(p->data, token, strlen(token) + 1);
        p->next = NULL;
        ptr->next = p;
        ptr = p;

        token = strtok(NULL, DELIMS);
    } 
    return head;
}

int main(int argc, char* argv[]) 
{
    char linebuf[1024];
    size_t linebuf_size = 0;

    while (1)
    {
        prompt();

        if (fgets(linebuf, 1024, stdin) == NULL) {
            break;
        }
        list *head = parse(linebuf);

        list *ptr = head->next;
        char buf[1024] = {'\0'};

        while (ptr != NULL)
        {
            strcat(buf,(char *)ptr->data);  
            strcat(buf, " ");  
            
            if (head->data != NULL) free(head->data);
            free(head);
            head = ptr;

            ptr = ptr->next; 
        }
        if (head->data != NULL) free(head->data);
        free(head);
        head = NULL;
        

        if(0) {
            // 本程序内部 doing work...
        }
        else{
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork fail");
                exit(1);
            }
            if (pid == 0) {
                system(buf);
                break;
                exit(0);
            }
            else{
                wait(NULL);
            }
        }
    }
    return 0;
}