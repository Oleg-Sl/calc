#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collections/stack.h"

#define ARRAY_VALID_LITERALS "+-*/()"


double calc(char* expression);
char* readingSingleToken(char* expression, int* pos);
void readingNumber(char* expression, int* pos, char* token, int* ind_token);
void readingString(char* expression, int* pos, char* token, int* ind_token);
int parsingString(char*);


int main(void) {
    calc("2+4");
    // Node* stack = initStack();
    // push(&stack, "111");
    // push(&stack, "222");
    // push(&stack, "333");
    // printStack(stack);
    // printf("pop = %s\n", pop(&stack));
    // printf("pop = %s\n", pop(&stack));
    // printStack(stack);
}


double calc(char* expression) {
    int pos = 0;
    int len_exp = strlen(expression);
    printf("START\n");
    while (pos < len_exp ) {
        char* token = readingSingleToken(expression, &pos);
        printf("%s \n", token);
        printf("=> \n");
    }

    return 0;
}

// считывание токена из выражения "expression" с индекса позиции "pos"
char* readingSingleToken(char* expression, int* pos) {
    int ind_buffer = 0;
    char* buffer = (char*)malloc(2 * sizeof(char));

    if (strchr(ARRAY_VALID_LITERALS, expression[*pos])) {
        // токен - одиночный
        printf("токен - одиночный = %c \n", expression[*pos]);
        buffer[ind_buffer] = expression[*pos];
        *pos += 1;
        ind_buffer += 1;
    } else if ('0' <= expression[*pos] && expression[*pos] <= '9') {
        // токен - число
        printf("токен - число = %c \n", expression[*pos]);
        readingNumber(expression, pos, buffer, &ind_buffer);
    } else if ('a' <= expression[*pos] && expression[*pos] <= 'z') {
        // токен - строка
        printf("токен - строка = %c \n", expression[*pos]);
        readingString(expression, pos, buffer, &ind_buffer);
    }

    buffer[ind_buffer] = '\0';
    return buffer;
}

// считывает число из строки "expression" с позиции "pos" и записывает считанное числа в "token"
void readingNumber(char* expression, int* pos, char* token, int* ind_token) {
    int ready = 0;
    token[*ind_token] = expression[*pos];
    *pos += 1;
    *ind_token += 1;
    
    while (*pos < (int)strlen(expression) && !ready) {
        if (('0' <= expression[*pos] && expression[*pos] <= '9') || expression[*pos] == '.') {
            token = (char*) realloc(token, (*ind_token + 1)*sizeof(char));
            token[*ind_token] = expression[*pos];
            *pos += 1;
            *ind_token += 1;
        } else {
            ready = 1;
        }
    }
}

// считывает строку из строки "expression" с позиции "pos" и записывает считанную строку в "token"
void readingString(char* expression, int* pos, char* token, int* ind_token) {
    int ready = 0;
    token[*ind_token] = expression[*pos];
    *pos += 1;
    *ind_token += 1;
    
    while (*pos < (int)strlen(expression) && !ready) {
        if ('a' <= expression[*pos] && expression[*pos] <= 'z') {
            token = (char*) realloc(token, (*ind_token + 1)*sizeof(char));
            token[*ind_token] = expression[*pos];
            *pos += 1;
            *ind_token += 1;
        } else {
            ready = 1;
        }
    }
}

