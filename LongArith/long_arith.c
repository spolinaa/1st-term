/* Long arithmetics (operations: +, -, *, /)
 by Sokolova Polina */
 
#include <stdio.h>
#include <stdlib.h>
#include "long_arith.h"

void longNum_operations (int sign_1, int size_1, intlist *list_1, int sign_2, int size_2, intlist *list_2, int *sign_res, int *size_res, intlist **list_res, int command) {
    switch(command) {
        case 0: {
            if (sign_1 == sign_2) {
                longNum_addition(size_1, list_1, size_2, list_2, size_res, list_res);
                *sign_res = sign_1;
            }
            else {
                longNum_substraction(sign_1, size_1, list_1, sign_2, size_2, list_2,sign_res, size_res, list_res, command);
            }
            break;
        }
        case 1:
            if (sign_1 != sign_2) {
                longNum_addition(size_1, list_1, size_2, list_2, size_res, list_res);
                *sign_res = sign_1;
            }
            else {
                longNum_substraction(sign_1, size_1, list_1, sign_2, size_2, list_2,sign_res, size_res, list_res, command);
            }
            break;
        case 2: {
            longNum_multiplication(list_1, list_2, size_res, list_res);
            if (sign_1 == sign_2) {
                *sign_res = 0;
            }
            else {
                *sign_res = 1;
            }
            break;
        }
        case 3: {
            longNum_division(size_1, list_1, size_2, list_2, size_res, list_res);
            if (*list_res) {
                if (sign_1 == sign_2) {
                    *sign_res = 0;
                }
                else {
                    *sign_res = 1;
                }
            }
            break;
        }
        case -1:
            printf("Неправильный ввод!\n");
            break;
        case -2:
            printf("Неправильный ввод (слишком много операций)!\n");
            break;
    }
}
void longNum_add (int *sign_1, int *size_1, intlist **list_1, int *sign_2, int *size_2, intlist **list_2, int *sign_res, int *size_res, intlist **list_res, int *command) {
    int i = 0;
    char s = ' ';
    int exit_flag = 1;
    int flag = 0;
    *size_1 = 0;
    *size_2 = 0;
    *size_res = 0;
    *sign_1 = 0;
    *sign_2 = 0;
    *sign_res = 0;
    *list_1 = NULL;
    *list_2 = NULL;
    *list_res = NULL;
    int flag_good = 0;
    printf("Введите выражение (отрицательные числа вводятся в скобках):\n");
    for (i = 0; s != '=' && exit_flag; i++) { //
        scanf("%c", &s);
        switch (s) {
            case '=':
                break;
            case '(':
                flag = 1;
                break;
            case ')':
                if (!flag_good) {
                    if (*command == -1) {
                        *sign_1 = 0;
                    }
                    else {
                        *sign_2 = 0;
                    }
                }
                break;
            case '+':
                if (*command == -1 && exit_flag) {
                    *command = 0;
                }
                else {
                    exit_flag = 0;
                }
                break;
            case '-':
                if (exit_flag) {
                    if (!*list_1 && !flag)  {
                        flag = 1;
                    }
                    else {
                        if (!flag)  {
                            *command = 1;
                        }
                        else {
                            flag_good = 1;
                        }
                    }
                }
                break;
            case '*':
                if (*command == -1 && exit_flag) {
                    *command = 2;
                }
                else {
                    exit_flag = 0;
                }
                break;
            case '/':
                if (*command == -1 && exit_flag) {
                    *command = 3;
                }
                else {
                    exit_flag = 0;
                }
                break;
            case '0'...'9': {
                intlist *p = (intlist*) malloc(sizeof(intlist));
                if (p) {
                    p -> v = s - '0';
                    if (*command == -1) {
                        if (flag) {
                            *sign_1 = 1;
                            flag = 0;
                        }
                        (*size_1)++;
                        p -> next = *list_1;
                        *list_1 = p;
                    }
                    else {
                        if (flag) {
                            *sign_2 = 1;
                            flag = 0;
                        }
                        (*size_2)++;
                        p -> next = *list_2;
                        *list_2 = p;
                    }
                }
                break;
            }
            default:
                if (s != '\n') {
                    printf("Команды '%c' не существует\n", s);
                    exit_flag = 0;
                }
                else {
                    printf("Введите знак '=', если вы закончили ввод выражения\n");
                }
                break;
        }
    }
    if (!exit_flag) {
        if (*command != -1) {
            *command = -2;
        }
    }
    intlist_delzero(list_1, size_1, 1);
    intlist_delzero(list_2, size_2, 1);
}
void longNum_state (intlist *list_1, int sign_1) {
    if (list_1) {
        if (list_1 -> v) {
            if (sign_1) {
                printf("-");
            }
        }
        while (list_1) {
            printf("%d", list_1 -> v);
            list_1 = list_1 -> next;
        }
        printf("\n");
    }
    else {
        printf("no digits\n");
    }
}
void longNum_addition(int size_1, intlist *list_1, int size_2, intlist *list_2, int *size_res, intlist **list_res) {
    int min = longNum_min(size_1, size_2);
    int max = longNum_max(size_1, size_2);
    int flag = 0;
    int i = 0;
    int sum = 0;
    intlist *clone = NULL;
    for (i = 0; i < min; i++) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            sum = list_1 -> v + list_2 -> v;
            if (flag) {
                sum++;
                flag = 0;
            }
            if (sum > 9) {
                flag = 1;
                sum -=10;
            }
            p -> v = sum;
            p -> next = *list_res;
            *list_res = p;
        }
        list_1 = list_1 -> next;
        list_2 = list_2 -> next;
    }
    if (size_2 == max) {
        clone = list_2;
    }
    else {
        clone = list_1;
    }
    i = min;
    for (; i < max; i++) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            sum = clone -> v;
            if (flag) {
                sum++;
                flag = 0;
            }
            if (sum > 9) {
                flag = 1;
                sum -=10;
            }
            p -> v = sum;
            p -> next = *list_res;
            *list_res = p;
        }
        clone = clone -> next;
    }
    *size_res = max;
    if (flag) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            p -> v = 1;
            p -> next = *list_res;
            *list_res = p;
        }
        size_res++;
    }
}
void intlist_copy(intlist *list, intlist **list_clone) {
    while (list) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            p -> v = list -> v;
            p -> next = *list_clone;
            *list_clone = p;
        }
        list = list -> next;
    }
    intlist_swap(list_clone);
}
void longNum_substraction(int sign_1, int size_1, intlist *list_1, int sign_2, int size_2, intlist *list_2, int *sign_res, int *size_res, intlist **list_res, int command) {
    int min = longNum_min(size_1, size_2);
    int max = longNum_max(size_1, size_2);
    int flag = 0;
    int i = 0;
    int dif = 0;
    intlist *cup = NULL;
    intlist *list_clone_1 = NULL;
    intlist *list_clone_2 = NULL;
    *sign_res = sign_1;
    intlist_copy(list_1, &list_clone_1);
    intlist_copy(list_2, &list_clone_2);
    i = longNum_comparison(size_1, &list_clone_1, size_2, &list_clone_2);
    if (!i) {
        cup = list_1;
        list_1 = list_2;
        list_2 = cup;
        *sign_res = sign_2;
        if (command) {
            *sign_res = !*sign_res;
        }
    }
    for (i = 0; i < min; i++) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            dif = list_1 -> v - list_2 -> v;
            if (flag) {
                dif--;
                flag = 0;
            }
            if (dif < 0) {
                flag = 1;
                dif +=10;
            }
            p -> v = dif;
            p -> next = *list_res;
            *list_res = p;
        }
        list_1 = list_1 -> next;
        list_2 = list_2 -> next;
    }
    i = min;
    for (; i < max; i++) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            dif = list_1 -> v;
            if (flag) {
                dif--;
                flag = 0;
            }
            if (dif < 0)  {
                flag = 1;
                dif +=10;
            }
            p -> v = dif;
            p -> next = *list_res;
            *list_res = p;
        }
        list_1 = list_1 -> next;
    }
    *size_res = max;
    intlist_delzero(list_res, size_res, 0);
    intlist_free(&list_clone_1);
    intlist_free(&list_clone_2);
}
void intlist_free(intlist **list_1) {
    intlist *p = NULL;
    while (*list_1) {
        p = *list_1;
        *list_1 = (*list_1) -> next;
        free (p);
    }
}
void longNum_multiplication(intlist *list_1, intlist *list_2, int *size_res, intlist **list_res) {
    intlist *list_temp = NULL;
    int mult = 0;
    int box = 0;
    int j = 0;
    intlist *clone_1 = list_1;
    while (list_2) {
        while (list_1) {
            intlist *p = (intlist*) malloc(sizeof(intlist));
            if (p) {
                mult = list_2 -> v * list_1 -> v + box;
                box = 0;
                if (mult > 9) {
                    box = mult / 10;
                    mult = mult % 10;
                }
                p -> v = mult;
                p -> next = list_temp;
                list_temp = p;
                list_1 = list_1 -> next;
            }
        }
        if (box) {
            intlist *p = (intlist*) malloc(sizeof(intlist));
            if (p) {
                p -> v = box;
                box = 0;
                p -> next = list_temp;
                list_temp = p;
            }
        }
        intlist_addzero(&list_temp, j);
        j++;
       	longNum_sumformult(list_temp, size_res, list_res);
        intlist_free(&list_temp);
        list_2 = list_2 -> next;
        list_1 = clone_1;
    }
    intlist_delzero(list_res, size_res, 1);
    intlist_swap(list_res);
}
void intlist_addzero (intlist **list_1, int j) {
    int i = 0;
    if ((*list_1) -> next) {
        intlist_swap(list_1);
    }
    for (i = 0; i < j; i++) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            p -> v = 0;
            p -> next = *list_1;
            *list_1 = p;
        }
    }
}
void intlist_swap(intlist **list_1) {
    intlist *list_2 = NULL;
    intlist *clone_1 = *list_1;
    if ((*list_1) -> next) {
        while (*list_1) {
            intlist *p = (intlist*) malloc(sizeof(intlist));
            if (p) {
                p -> v = (*list_1) -> v;
                p -> next = list_2;
                list_2 = p;
            }
            *list_1 = (*list_1) -> next;
        }
        *list_1 = list_2;
        intlist_free(&clone_1);
    }
}
void longNum_sumformult(intlist *list_1, int *size_2, intlist **list_2) {
    int flag = 0;
    int sum = 0;
    intlist *clone_2 = *list_2;
    intlist *last = NULL;
    while (list_1) {
        if (*list_2) {
            sum = (list_1 -> v) + ((*list_2) -> v);
            if (flag) {
                sum++;
                flag = 0;
            }
            if (sum > 9) {
                flag = 1;
                sum -=10;
            }
            (*list_2) -> v = sum;
            list_1 = list_1 -> next;
            if (!(*list_2) -> next && list_1) {
                intlist *p = (intlist*) malloc(sizeof(intlist));
                if (p) {
                    p -> v = 0;
                    (*list_2) -> next = p;
                    (*size_2)++;
                }
            }
            if (list_1) {
                *list_2 = (*list_2) -> next;
            }
        }
        else {
            intlist *p = (intlist*) malloc(sizeof(intlist));
            if (p) {
                sum = list_1 -> v;
                if (flag) {
                    sum++;
                    flag = 0;
                }
                if (sum > 9) {
                    flag = 1;
                    sum -=10;
                }
                p -> v = sum;
                (*size_2)++;
                if (last) {
                    while (last -> next) {
                        last = last -> next;
                    }
                }
                if (!clone_2) {
                    clone_2 = p;
                    clone_2 -> next = NULL;
                    last = clone_2;
                }
                else {
                    last -> next = p;
                }
                list_1 = list_1 -> next;
            }
        }
    }
    if (*list_2) {
        while ((*list_2) -> next) {
            *list_2 = (*list_2) -> next;
            sum = (*list_2) -> v;
            if (flag) {
                sum++;
                flag = 0;
            }
            if (sum > 9) {
                flag = 1;
                sum -=10;
            }
            (*list_2) -> v = sum;
        }
    }
    if (flag) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            p -> v = 1;
            (*list_2) -> next = p;
        }
        (*size_2)++;
    }
    *list_2 = clone_2;
}
void diffordiv(int *size_1, intlist **list_1, intlist *list_2) {
    int dif = 0;
    int flag = 0;
    intlist *clone_1 = *list_1;
    *size_1 = 0;
    while (list_2) {
        dif = (clone_1 -> v) - (list_2 -> v);
        if (flag) {
            dif--;
            flag = 0;
        }
        if (dif < 0) {
            flag = 1;
            dif +=10;
        }
        clone_1 -> v = dif;
        clone_1 = clone_1 -> next;
        list_2 = list_2 -> next;
        (*size_1)++;
    }
    while (clone_1) {
        dif = clone_1 -> v;
        if (flag) {
            dif--;
            flag = 0;
        }
        if (dif < 0) {
            flag = 1;
            dif +=10;
        }
        clone_1 -> v = dif;
        clone_1 = clone_1 -> next;
        (*size_1)++;
    }
    intlist_delzero(list_1, size_1, 1);
}
void intlist_delzero (intlist **list_1, int *size_1, int com) {
    intlist *p_1 = NULL;
    if ((*list_1) -> next) {
        if (com) {
            intlist_swap(list_1);
        }
        while ((*list_1) -> next && !(*list_1) -> v) {
            p_1 = *list_1;
            *list_1 = (*list_1) -> next;
            free(p_1);
            (*size_1)--;
        }
        if (com) {
            intlist_swap(list_1);
        }
    }
}
void longNum_division(int size_1, intlist *list_1, int size_2, intlist *list_2, int *size_res, intlist **list_res) {
    int i = 0;
    intlist *list_sum = NULL;
    int size_sum = 0;
    intlist *p_one = NULL;
    *size_res = 0;
    intlist *list_clone_1 = NULL;
    intlist *list_clone_2 = NULL;
    if (!list_2 -> v && !list_2 -> next) {
        printf("Деление на ноль!\n");
        *list_res = 0;
    }
    else {
        if (!list_1 -> v && !list_1 -> next) {
            *list_res = list_1;
            *size_res = size_1;
        }
        else {
            intlist_copy(list_1, &list_clone_1);
            intlist_copy(list_2, &list_clone_2);
            i = longNum_comparison(size_1, &list_clone_1, size_2, &list_clone_2);
            if (!i) {
                intlist *p = (intlist*) malloc(sizeof(intlist));
                if (p) {
                    p -> v = 0;
                    *list_res = p;
                    *size_res = 1;
                }
            }
            else {
                intlist *p = (intlist*) malloc(sizeof(intlist));
                if (p) {
                    p -> v = 1;
                    p_one = p;
                }
                while (i) {
                    diffordiv(&size_1, &list_clone_1, list_clone_2);
                    longNum_sumformult(p_one, &size_sum, &list_sum);
                    i = longNum_comparison(size_1, &list_clone_1, size_2, &list_clone_2);
                }
                intlist_swap(&list_sum);
                *size_res = size_sum;
                *list_res = list_sum;
                intlist_free(&p_one);
                intlist_free(&list_clone_1);
                intlist_free(&list_clone_2);
            }
        }
    }
}
int longNum_comparison(int size_1, intlist **list_1, int size_2, intlist **list_2) {
    int res = 2;
    intlist *clone_1 = NULL;
    intlist *clone_2 = NULL;
    if (size_1 > size_2) {
        res = 1;
    }
    else {
        if (size_1 == size_2) {
            intlist_swap(list_1);
            clone_1 = *list_1;
            intlist_swap(list_2);
            clone_2 = *list_2;
            while (clone_1) {
                if (clone_1 -> v > clone_2 -> v) {
                    res = 1;
                    break;
                }
                else {
                    if (clone_1 -> v < clone_2 -> v) {
                        res = 0;
                        break;
                    }
                }
               	clone_1 = clone_1 -> next;
                clone_2 = clone_2 -> next;
            }
            intlist_swap(list_1);
            intlist_swap(list_2);
        }
        else {
            res = 0;
        }
    }
    return res;
}
int longNum_max(int size_1, int size_2) {
    if (size_1 > size_2) {
        return size_1;
    }
    else {
        return size_2;
    }
}
int longNum_min(int size_1, int size_2) {
    if (size_1 < size_2) {
        return size_1;
    }
    else {
        return size_2;
    }
}
void intlist_add (longNum **hd, char value) {
    intlist *p = (intlist*) malloc(sizeof(intlist));
    if (p) {
        p -> v = value - '0';
        p -> next = (*hd) -> digits;
        (*hd) -> digits = p;
        ((*hd) -> size)++;
    }
}
int main() {
    longNum x;
    longNum y;
    longNum res;
    longNum *hd1 = &x;
    longNum *hd2 = &y;
    longNum *hdres = &res;
    int com = -1;
    longNum_add(&(hd1) -> sign, &(hd1) -> size, &(hd1) -> digits, &(hd2) -> sign, &(hd2) -> size, &(hd2) -> digits, &(hdres) -> sign, &(hdres) -> size, &(hdres) -> digits, &com);
    longNum_operations(hd1 -> sign, hd1 -> size, hd1 -> digits, hd2 -> sign, hd2 -> size, hd2 -> digits, &(hdres) -> sign, &(hdres) -> size, &(hdres) -> digits, com);
    longNum_state(hdres -> digits, hdres -> sign);
    if (hd1 -> digits != hdres -> digits) {
        intlist_free(&hdres -> digits);
    }
    intlist_free(&hd2 -> digits);
    intlist_free(&hd1 -> digits);
    exit(0);
}
