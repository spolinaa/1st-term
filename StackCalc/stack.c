//
//  stack.c
//  Stack calculator for long arithmetics
//
//  Created by Sokolova Polina on 25.12.14.
//  Copyright (c) 2014 PS. All rights reserved.
//

#include "stack.h"

void longNum_operations (int sign_1, int size_1, intlist *list_1, int sign_2, int size_2, intlist *list_2, int *sign_res, int *size_res, intlist **list_res, int command, int *f) {
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
            longNum_division(sign_1, size_1, list_1, size_2, list_2, size_res, list_res, f);
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
    }
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
    intlist_swap(list_res);
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
    intlist_swap(list_res);
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
    int size_temp = 0;
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
                size_temp++;
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
                size_temp++;
            }
        }
        intlist_addzero(&size_temp, &list_temp, j);
        intlist_delzero(&list_temp, &size_temp, 1);
        j++;
       	longNum_sumformult(size_temp, list_temp, size_res, list_res);
        intlist_free(&list_temp);
        size_temp = 0;
        list_2 = list_2 -> next;
        list_1 = clone_1;
    }
}
void intlist_addzero (int *size_list, intlist **list_1, int j) {
    int i = 0;
    intlist_swap(list_1);
    for (i = 0; i < j; i++) {
        intlist *p = (intlist*) malloc(sizeof(intlist));
        if (p) {
            p -> v = 0;
            p -> next = *list_1;
            *list_1 = p;
            (*size_list)++;
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
void longNum_sumformult(int size_1, intlist *list_1, int *size_2, intlist **list_2) {
    int flag = 0;
    int sum = 0;
    intlist *p = NULL;
    intlist *result_list = NULL;
    intlist *max_list = NULL;
    intlist *min_list = NULL;
    if (*list_2) {
        if (*size_2 == 1 && !(*list_2) -> v) {
            p = *list_2;
            free(p);
            *list_2 = NULL;
            intlist_copy(list_1, list_2);
            (*size_2) = size_1;
        }
        else {
            if (size_1 == 1 && !list_1 -> v) {}
            else {
                if (size_1 > *size_2) {
                    intlist_copy(list_1, &max_list);
                    min_list = *list_2;
                    *size_2 = size_1;
                }
                else {
                    max_list = *list_2;
                    min_list = list_1;
                }
                result_list = max_list;
                while (min_list) {
                    sum = (min_list -> v) + (max_list -> v);
                    if (flag) {
                        sum++;
                        flag = 0;
                    }
                    if (sum > 9) {
                        flag = 1;
                        sum -=10;
                    }
                    max_list -> v = sum;
                    min_list = min_list -> next;
                    if (min_list) {
                        max_list = max_list -> next;
                    }
                }
                while ((max_list -> next) && flag) {
                    max_list = max_list -> next;
                    sum = max_list -> v;
                    if (flag) {
                        sum++;
                        flag = 0;
                    }
                    if (sum > 9) {
                        flag = 1;
                        sum -=10;
                    }
                    max_list -> v = sum;
                }
                if (flag) {
                    intlist *p = (intlist*) malloc(sizeof(intlist));
                    if (p) {
                        p -> v = 1;
                        max_list -> next = p;
                    }
                    (*size_2)++;
                }
                *list_2 = result_list;
            }
        }
    }
    else {
        intlist_copy(list_1, list_2);
        (*size_2) = size_1;
    }
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
void longNum_division(int sign_1, int size_1, intlist *list_1, int size_2, intlist *list_2, int *size_res, intlist **list_res, int *f) {
    int i = 0;
    intlist *list_sum = NULL;
    int size_sum = 0;
    intlist *p_one = NULL;
    *size_res = 0;
    intlist *list_clone_1 = NULL;
    intlist *list_clone_2 = NULL;
    if (!list_2 -> v && !list_2 -> next) {
        *f = 3;
        *list_res = NULL;
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
                if (sign_1) {
                    (*list_res) -> v = 1;
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
                    longNum_sumformult(1, p_one, &size_sum, &list_sum);
                    i = longNum_comparison(size_1, &list_clone_1, size_2, &list_clone_2);
                }
                if (list_clone_1 -> v && !list_clone_1 -> next) {
                    if (sign_1) {
                        longNum_sumformult(1, p_one, &size_sum, &list_sum);
                    }
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
void intlist_add(longNum **hd, char value) {
    intlist *p = (intlist*) malloc(sizeof(intlist));
    if (p) {
        p -> v = value - '0';
        p -> next = (*hd) -> digits;
        (*hd) -> digits = p;
        ((*hd) -> size)++;
    }
}
void longNum_free(longNum **hd) {
    intlist *list = (*hd) -> digits;
    (*hd) -> size = 0;
    (*hd) -> sign = 0;
    intlist_free(&list);
    (*hd) -> digits = NULL;
}

struct longNum stack_pop(stack **head) {
    stack *digits = NULL;
    stack *p = NULL;
    longNum num;
    p = *head;
    *head = p -> next;
    digits = p;
    num = digits -> number;
    free(p);
    return num;
}
void stack_push(stack **head, longNum *num) {
    stack *p = (stack*) malloc (sizeof (stack));
    if (p) {
        p -> number = *num;
        p -> next = *head;
        *head = p;
    }
    (*num).sign = 0;
    (*num).size = 0;
    (*num).digits = NULL;
}
void stack_read(stack **head, int *f) {
    char buffer = ' ';
    longNum a_num;
    longNum b_num;
    longNum c_num;
    longNum *hd1 = &a_num;
    longNum *hd2 = &b_num;
    longNum *hdres = &c_num;
    hd1 -> digits = NULL;
    hd2 -> digits = NULL;
    hdres -> digits = NULL;
    hd1 -> sign = 0;
    hd2 -> sign = 0;
    hdres -> sign = 0;
    hd1 -> size = 0;
    hd2 -> size = 0;
    hdres -> size = 0;
    int allow_sub = 0;
    int recording = 0;
    int command = -1;
    int another_command = -1;
    int special_print = 0;
    while (buffer != EOF && !*f) {
        buffer = getchar();
        if (recording) {
            if (hd1 -> digits) {
                intlist_delzero(&(hd1) -> digits, &(hd1) -> size, 1);
                stack_push(head, &a_num);
            }
            recording = 0;
        }
        switch (buffer) {
            case '0'...'9':
                intlist_add(&hd1, buffer);
                break;
            case '\r':
            case '\n':
                if (hd1 -> sign && !hd1 -> digits) {
                    allow_sub = 1;
                    command = 1;
                    hd1 -> sign = 0;
                }
                recording = 1;
                break;
            case ' ':
                break;
            case EOF:
                if (hd1 -> sign) {
                    allow_sub = 1;
                    command = 1;
                    hd1 -> sign = 0;
                }
                break;
            case '=':
                special_print = 1;
                stack_print(*head, *f, special_print);
                special_print = 0;
                break;
            default: {
                if (buffer == '-' && !allow_sub) {
                    hd1 -> sign = 1;
                }
                else {
                    if (allow_sub) {
                        command = 1;
                        allow_sub = 0;
                    }
                    if (*head) {
                        if ((*head) -> next) {
                            a_num = stack_pop(head);
                            b_num = stack_pop(head);
                        }
                        else {
                            *f = 1;
                            break;
                        }
                    }
                    else {
                        switch(buffer) {
                            case '+':
                            case '-':
                            case '*':
                            case '/':
                                *f = 1;
                                break;
                        }
                        if (*f) {
                            break;
                        }
                    }
                    switch (buffer) {
                        case '+':
                            if (command == 1) {
                                another_command = 0;
                            }
                            else {
                                command = 0;
                            }
                            break;
                        case '*':
                            if (command == 1) {
                                another_command = 2;
                            }
                            else {
                                command = 2;
                            }
                            break;
                        case '/':
                            if (command == 1) {
                                another_command = 3;
                            }
                            else {
                                command = 3;
                            }
                            break;
                        default:
                            *f = 2;
                            break;
                    }
                    if (!*f) {
                        longNum_operations(hd1 -> sign, hd1 -> size, hd1 -> digits, hd2 -> sign, hd2 -> size, hd2 -> digits, &(hdres) -> sign, &(hdres) -> size, &(hdres) -> digits, command, f);
                        command = -1;
                        longNum_free(&hd1);
                        longNum_free(&hd2);
                        if (hdres -> digits) {
                            stack_push(head, &c_num);
                            longNum_free(&hdres);
                        }
                        recording = 1;
                        if (another_command != -1) {
                            if (*head) {
                                if ((*head) -> next) {
                                    a_num = stack_pop(head);
                                    b_num = stack_pop(head);
                                    longNum_operations(hd1 -> sign, hd1 -> size, hd1 -> digits, hd2 -> sign, hd2 -> size, hd2 -> digits, &(hdres) -> sign, &(hdres) -> size, &(hdres) -> digits, another_command, f);
                                    another_command = -1;
                                    longNum_free(&hd1);
                                    longNum_free(&hd2);
                                    if (hdres -> digits) {
                                        stack_push(head, &c_num);
                                        longNum_free(&hdres);
                                    }
                                }
                                else {
                                    *f = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    if (allow_sub) {
        if (*head) {
            if ((*head) -> next) {
                a_num = stack_pop(head);
                b_num = stack_pop(head);
                longNum_operations(hd1 -> sign, hd1 -> size, hd1 -> digits, hd2 -> sign, hd2 -> size, hd2 -> digits, &(hdres) -> sign, &(hdres) -> size, &(hdres) -> digits, command, f);
                longNum_free(&hd1);
                longNum_free(&hd2);
                if (hdres -> digits) {
                    stack_push(head, &c_num);
                    longNum_free(&hdres);
                }
            }
            else {
                *f = 1;
            }
        }
        
    }
    
}
void stack_print(stack *head, int f, int special_print) {
    if (special_print) {
        if (head) {
            intlist_swap(&(head) -> number.digits);
            longNum_state(head -> number.digits, head -> number.sign);
            intlist_swap(&(head) -> number.digits);
            printf("\n");
        }
        else {
            f = 1;
            printf("Not enough arguments\n");
        }
    }
    else {
        if (!f) {
            if (head) {
                printf("[");
                while (head) {
                    intlist_swap(&(head) -> number.digits);
                    longNum_state(head -> number.digits, head -> number.sign);
                    intlist_swap(&(head) -> number.digits);
                    if (head -> next) {
                        printf("; ");
                    }
                    head = head -> next;
                }
                printf("]\n");
            }
        }
        else {
            switch (f) {
                case 1:
                    printf("Not enough arguments\n");
                    break;
                case 2:
                    printf("Unknown command\n");
                    break;
                case 3:
                    printf("Division by zero\n");
                    break;
            }
        }
    }
}
void stack_quit(stack **head) {
    stack *p;
    longNum *num = NULL;
    while (*head) {
        p = *head;
        num = &(*head) -> number;
        longNum_free(&num);
        *head = (*head) -> next;
        free(p);
    }
    exit (0);
}
