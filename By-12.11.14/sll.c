/* Single-linked list
 by Sokolova Polina */

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

/* GLOBAL VARIABLES */
typedef struct node_t {
    int v;
    struct node_t *next;
} node_t;
int e1;
node_t *hd = 0;
node_t *p;

/* MAKE A NEW SLL (add to the top of a list)*/
void addall () {
    int val = 0;
    printf("Введите элементы списка\n");
    while (1) {
        scanf("%d", &val);
        if (val) {
            node_t *p = (node_t*) malloc (sizeof (node_t));
            if (p) {
                p -> v = val;
                p -> next = hd;
                hd = p;
            }
            else {
                printf("Недостаточно памяти!\n");
                break;
            }
        }
        else {
            break;
        }
    }
}

/* ADD A NEW ELEMENT */
void add1 (int el) {
    if (el) {
        node_t *p = (node_t*) malloc (sizeof (node_t));
        if (p) {
            p -> v = el;
            p -> next = hd;
            hd = p;
        }
    }
}
/* LIST STATE */
void st() {
    p = hd;
    if (!p) {
        printf ("Список пуст!");
    }
    while (p) {
        printf ("%d", p -> v);
        p = p -> next;
        if (p) {
            printf(", ");
        }
    }
    printf("\n");
}

/* DELETE AN ELEMENT */
void del(int el) {
    node_t *p1;
    p1 = hd;
    for (p = hd; p && (p -> v != el); p1 = p, p = p1 -> next) {}
    if (!p) {
        printf("Элемента %d в списке нет\n", el);
    }
    else {
        if (hd) {
            if (p != p1) {
                p1 -> next = p -> next;
            }
            else {
                hd = p -> next;
            }
            p1 = hd;
            free(p);
        }
    }
}

/* CLEAR AND EXIT */
void quit() {
    while (hd) {
        p = hd;
        hd = hd -> next;
        free (p);
    }
    exit (0);
}

/* READ USER'S COMMAND */
void readit() {
    char com;
    int i;
    scanf("%c", &com);
    while (com != 'q') {
        if (com != ' ' && com != '\n') {
            switch (com) {
                case 'a':
                    scanf("%d", &i);
                    add1(i);
                    break;
                case 'r':
                    scanf("%d", &i);
                    del(i);
                    break;
                case 'p':
                    st();
                    break;
                case 'q':
                    quit();
                    break;
                default:
                    printf("%c - Такой команды не существует!\n", com);
                    break;
            }
        }
        scanf("%s", &com);
    }
}
int main() {
    addall();
    readit();
    quit();
}
