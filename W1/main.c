#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct node {
    char string[MAX_SIZE];
    int count;
    char listLine[MAX_SIZE];
    struct node *next;
} node;
node *head = NULL, *stopw = NULL;


node *sortedInsert(node *head_t, node *newNode) {
    if (head_t == NULL ||
        strcmp(newNode->string, head_t->string) < 0) {
        newNode->next = head_t;   
        head_t = newNode;
    } else {
        node *current = head_t, *previous;
        while (current->next != NULL && strcmp(newNode->string, current->string) > 0) {
            previous = current;
            current = current->next;
        }
        if (current->next == NULL &&
            strcmp(newNode->string, current->string) > 0) {
            current->next = newNode; 
        } else {
            newNode->next = current;
            previous->next = newNode;
        }
    }
    return head_t;
}


node *newAndInsert(node *head_t, char str[], int line) {
    node *temp = head_t;
    int check = 0;
    while (temp != NULL) {
        if (!strcmp(str, temp->string)) {
            check = 1;
            break;
        }
        temp = temp->next;
    }
    if (check == 0) {
        node *newNode = (node *) malloc(sizeof(node));
        strcpy(newNode->string, str);
        newNode->count = 1;
        sprintf(newNode->listLine, " %d", line);
        newNode->next = NULL;
        head_t = sortedInsert(head_t, newNode);
        return head_t;
    } else {
        temp->count++;
        char s[10] = "";
        sprintf(s, " %d", line); 
        for (int i = (int) strlen(s) - 1; i != 0; --i) {
            if (s[i] != temp->listLine[strlen(temp->listLine) + i - strlen(s)]) {
                sprintf(temp->listLine, "%s, %d", temp->listLine, line);
                return head_t;
            }
        }
        return head_t;
    }
}


void printList(node *head_t) {
    node *temp = head_t;
    while (temp != NULL) {
        printf("%s %d,%s\n", temp->string, temp->count, temp->listLine);
        temp = temp->next;
    }
}

void freeList(node *head_t) {
    if(head_t->next != NULL)
        freeList(head_t->next);
    free(head_t);
}


int check(char str[]) {
    node *temp = stopw;
    while (temp != NULL) {
        if (!strcmp(str, temp->string))
            return 1;
        temp = temp->next;
    }
    return 0;
}


int main() {
    FILE *f1 = fopen("stopw.txt", "r");
    if (f1 != NULL) {
        while (!feof(f1)) {
            char s[100] = "";
            fscanf(f1, "%s", s);
            stopw = newAndInsert(stopw, s, 0);
        }
    }
    fclose(f1);
    FILE *f2 = fopen("vanban.txt", "r");
    int countLine = 1, dauCau = 1;
    if (f2 != NULL) {
        while (!feof(f2)) {
            char s[100] = ""; 
            int c = 0, curLine = countLine, vietHoa = 0;
            do {
                if (strlen(s) == 0 && c != tolower(c))
                    vietHoa = 1; 
                sprintf(s, "%s%c", s, tolower(c)); 
                c = fgetc(f2); 
                if (c == '\n') 
                    countLine++;
            } while (isalpha(c));
            
            if (strlen(s) != 0 && !check(s) && ((vietHoa && dauCau) || !vietHoa)) {
                head = newAndInsert(head, s, curLine); 
                if (dauCau) 
                    dauCau = 0;
            }
            if (c == '.') 
                dauCau = 1;
        }
    }
    fclose(f2);
    printList(head);
    freeList(head);
    freeList(stopw);
    return 0;
}