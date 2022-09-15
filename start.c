#include <stdio.h>
#include <stdlib.h>

#include "collections/stack.h"


int main(void) {
    Node* stack = initStack();
    push(&stack, "111");
    push(&stack, "222");
    push(&stack, "333");
    printStack(stack);
    printf("pop = %s\n", pop(&stack));
    printf("pop = %s\n", pop(&stack));
    printStack(stack);
}

