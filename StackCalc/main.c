//
//  main.c
//  Stack calculator for long arithmetics
//
//  Created by Sokolova Polina on 25.12.14.
//  Copyright (c) 2014 PS. All rights reserved.
//

#include "stack.h"

int main() {
    stack *top = NULL;
    int flag = 0;
    stack_read(&top, &flag);
    stack_print(top, flag, 0);
    stack_quit(&top);
    if (flag) {
        return 1;
    }
    else {
        return 0;
    }
}
