#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "collections/stack.h"

#define ARRAY_VALID_LITERALS "+-*/()"


double calc(char* expression);

char* readingSingleToken(char* expression, int* pos);
void readingNumber(char* expression, int* pos, char* token, int* ind_token);
void readingString(char* expression, int* pos, char* token, int* ind_token);
void distributionByStack(Node* stack_operator, Node* stack_number, char* token);
void calcByPolishNotationAlg(Node** stack_number, char* operator);
// При добавлении новой математической функции добавить их в функции ниже
int priorityOperator(char* operator);
int countOperands(char* operator);
double calcBinary(char* operator, double operand_1, double operand_2);
double calcUnary(char* operator, double operand);


int main(void) {
    // double res = calc("2.9+498.9-cos(122*9)+ln(3)");
    double res = calc("-cos(1.17)");
    printf("res = %lf\n", res);
    // Node* stack = initStack();
    // push(&stack, "111");
    // push(&stack, "222");
    // push(&stack, "333");
    // printStack(stack);
    // printf("pop = %s\n", pop(&stack));
    // printf("pop = %s\n", pop(&stack));
    // printStack(stack);
}

// вычисляет резултат математического выражения переданного в виде строки
double calc(char* expression) {
    Node* stack_operator = initStack();
    Node* stack_number = initStack();
    int pos = 0;
    int len_exp = strlen(expression);
    char* token_prev = NULL;

    printf("START\n");
    while (pos < len_exp ) {
        // здесь возращается токен в виде динамической памяти - НУЖНО ОСВОБОДИТЬ ПАМЯТЬ!!!
        char* token = readingSingleToken(expression, &pos);
        // запись токена в соответствующий стек
        if ('0' <= token[0] && token[0] <= '9') {
            push(&stack_number, token);
        } else if (token[0] == '(') {
            push(&stack_operator, token);
        } else if (token[0] == ')') {
            while (stack_operator && strcmp(peek(stack_operator), "(") != 0) {
                calcByPolishNotationAlg(&stack_number, pop(&stack_operator));
            }
            pop(&stack_operator);
        } else if (token[0] == '+' && (token_prev == NULL || token_prev[0] == '+' || token_prev[0] == '-' || token_prev[0] == '/' || token_prev[0] == '*' || token_prev[0] == '(')) {
            token_prev = token;
            continue;
        } else {
            if (token[0] == '-' && (token_prev == NULL || token_prev[0] == '+' || token_prev[0] == '-' || token_prev[0] == '/' || token_prev[0] == '*' || token_prev[0] == '(')) {
                token[0] = '~';
                token[1] = '\0';
            }
            // printf("peek = %s \n", peek(stack_operator));
            // printf("token = %s \n", token);
            while (stack_number && stack_operator && priorityOperator(peek(stack_operator)) >= priorityOperator(token)) {
                calcByPolishNotationAlg(&stack_number, pop(&stack_operator));
            }
            push(&stack_operator, token);
        }

        // printf("2222222222222222");
        // printf("%s \n", token);
        token_prev = token;
        // printStack(stack_number);
        // printStack(stack_operator);
    }

    // разбор операторов оставшихся в стеке
    while (stack_operator) {
        calcByPolishNotationAlg(&stack_number, pop(&stack_operator));
    }

    char* result = pop(&stack_number);
    return strtod(result, NULL);
}

// считывание токена из выражения "expression" с индекса позиции "pos"
char* readingSingleToken(char* expression, int* pos) {
    int ind_buffer = 0;
    char* buffer = (char*)malloc(2 * sizeof(char));

    if (strchr(ARRAY_VALID_LITERALS, expression[*pos])) {
        // токен - одиночный
        buffer[ind_buffer] = expression[*pos];
        *pos += 1;
        ind_buffer += 1;
    } else if ('0' <= expression[*pos] && expression[*pos] <= '9') {
        // токен - число
        readingNumber(expression, pos, buffer, &ind_buffer);
    } else if ('a' <= expression[*pos] && expression[*pos] <= 'z') {
        // токен - строка
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

// ложит токен в стек или вычисляет промежуточный результат и ложит его в стек
void distributionByStack(Node* stack_operator, Node* stack_number, char* token) {
    if ('0' <= token[0] && token[0] <= '9') {
        push(&stack_number, token);
    } else if (token[0] == '(') {
        push(&stack_operator, token);
    } else if (token[0] == ')') {
         while (stack_operator && strcmp(peek(stack_operator), "(") != 0) {
                calcByPolishNotationAlg(&stack_number, pop(&stack_operator));
            }
            pop(&stack_operator);
    }  else {

        push(&stack_operator, token);
    }
    
}


// 
void calcByPolishNotationAlg(Node** stack_number, char* operator) {
    double res;
    if (countOperands(operator) == 2) {
        double last_value = strtod(pop(stack_number), NULL);
        double prev_value = strtod(pop(stack_number), NULL);
        res = calcBinary(operator, prev_value, last_value);
    } else {
        double last_value = strtod(pop(stack_number), NULL);
        res = calcUnary(operator, last_value);
    }
    char* buf = (char*)malloc(12*sizeof(char));
    sprintf(buf, "%f", res);
    push(stack_number, buf);
}


// возвращает приоритет переданного оператора
int priorityOperator(char* operator) {
    int priority = 0;

    if (strcmp(operator, "+") == 0)
        priority = 1;
    else if (strcmp(operator, "-") == 0)
        priority = 1;
    else if (strcmp(operator, "*") == 0)
        priority = 2;
    else if (strcmp(operator, "/") == 0)
        priority = 2;
    else if (strcmp(operator, "sin") == 0)
        priority = 3;
    else if (strcmp(operator, "cos") == 0)
        priority = 3;
    else if (strcmp(operator, "tan") == 0)
        priority = 3;
    else if (strcmp(operator, "ctg") == 0)
        priority = 3;
    else if (strcmp(operator, "sqrt") == 0)
        priority = 3;
    else if (strcmp(operator, "ln") == 0)
        priority = 3;
    else if (strcmp(operator, "~") == 0)
        priority = 4;

    return priority;
};

// возвращает количество операндов для переданного оператора
int countOperands(char* operator) {
    int count = 0;

    if (strcmp(operator, "+") == 0)
        count = 2;
    else if (strcmp(operator, "-") == 0)
        count = 2;
    else if (strcmp(operator, "*") == 0)
        count = 2;
    else if (strcmp(operator, "/") == 0)
        count = 2;
    else if (strcmp(operator, "sin") == 0)
        count = 1;
    else if (strcmp(operator, "cos") == 0)
        count = 1;
    else if (strcmp(operator, "tan") == 0)
        count = 1;
    else if (strcmp(operator, "ctg") == 0)
        count = 1;
    else if (strcmp(operator, "sqrt") == 0)
        count = 1;
    else if (strcmp(operator, "ln") == 0)
        count = 1;
    else if (strcmp(operator, "~") == 0)
        count = 1;

    return count;
};

// вычисляет результат для оператора с двумя операндами
double calcBinary(char* operator, double operand_1, double operand_2) {
    double result;

    if (strcmp(operator, "+") == 0)
        result = operand_1 + operand_2;
    else if (strcmp(operator, "-") == 0)
        result = operand_1 - operand_2;
    else if (strcmp(operator, "*") == 0)
        result = operand_1 * operand_2;
    else if (strcmp(operator, "/") == 0)
        result = operand_1 / operand_2;

    return result;
}

// вычисляет результат для оператора с одним операндом
double calcUnary(char* operator, double operand) {
    double result;
    if (strcmp(operator, "~") == 0)
        result = -1 * operand;
    else if (strcmp(operator, "sin") == 0)
        result = sin(operand);
    else if (strcmp(operator, "cos") == 0)
        result = cos(operand);
    else if (strcmp(operator, "tan") == 0)
        result = tan(operand);
    else if (strcmp(operator, "ctg") == 0)
        result = 1 / tan(operand);
    else if (strcmp(operator, "sqrt") == 0)
        result = sqrt(operand);
    else if (strcmp(operator, "ln") == 0)
        result = log(operand);

    return result;
}

