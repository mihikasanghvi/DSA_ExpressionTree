#include "expTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct node* init_tree(char* q){
    if (strlen(q) == 0) {
        return NULL;
    }
    struct stack* s1 = createstack(MAX_SIZE);
    int i;
    for (i = 0; i < strlen(q); i++)
    {
        // if the current token is an operator
        if (isOperator(q[i]))
        {
            // pop two nodes `x` and `y` from the stack
            struct node* x = pop(s1);

            struct node* y = pop(s1);

            struct node* node = newNode(q[i]);
            node->left = y;
            node->right = x;
            // push the current node into the stack
            push(s1, node);
        }
        else {
            if(!isdigit(q[i]))
                return NULL;
            push(s1, newNode(q[i]));
        }
    }
    return pop(s1);
}

struct node* newNode(char data){
    struct node* n = malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void inorder_r(struct node* root){
    if (root == NULL) {
        return;
    }

    // if the current token is an operator, print open parenthesis
    if (isOperator(root->data)) {
        printf("(");
    }

    inorder_r(root->left);
    printf("%c",root->data);
    inorder_r(root->right);

    // if the current token is an operator, print close parenthesis
    if (isOperator(root->data)) {
        printf(")");
    }
}

char* infixToPostfix(char* exp){
    int i, k;

    struct Stack* stack = createStack_itp(strlen(exp));
    if(!stack) // See if stack was created successfully
        return -1;

    for (i = 0, k = -1; exp[i]; ++i)
    {

        // If the scanned character is
        // an operand, add it to output.
        if (isdigit(exp[i]))
            exp[++k] = exp[i];

        // If the scanned character is an
        // �(�, push it to the stack.
        else if (exp[i] == '(')
            push_itp(stack, exp[i]);

        // If the scanned character is an �)�,
        // pop and output from the stack
        // until an �(� is encountered.
        else if (exp[i] == ')')
        {
            while (!isEmpty_itp(stack) && peek_itp(stack) != '(')
                exp[++k] = pop_itp(stack);
            if (!isEmpty_itp(stack) && peek_itp(stack) != '(')
                return NULL; // invalid expression
            else
                pop_itp(stack);
        }
        else // an operator is encountered
        {
            while (!isEmpty_itp(stack) &&
                 Prec(exp[i]) <= Prec(peek_itp(stack)))
                exp[++k] = pop_itp(stack);
            push_itp(stack, exp[i]);
        }

    }

    // pop all the operators from the stack
    while (!isEmpty_itp(stack))
        exp[++k] = pop_itp(stack);

    exp[++k] = '\0';
    //printf( "%s", exp);
    return exp;
}

//Evaluation Functions

float compute(struct node* root){
    char c;
    float z;

    if (root == NULL) {
        return 0;
    }

    if (isLeaf(root)) {
        c = root->data;
        z = c - '0';
        return z;
    }

    float x = compute(root->left);
    inorder_r(root->left);
    printf("\n");
    float y = compute(root->right);
    inorder_r(root->right);
    printf("\n");
    return process(root->data, x, y);
}

float process(char op, float x, float y){
    if (op == '+') {
            return x + y; }
    if (op == '-') {
        return x - y; }
    if (op == '*') {
        return x * y; }
    if (op == '/') {
        return x / y; }

    return 0;
}

bool isLeaf(struct node* root){
    return root->left == NULL && root->right == NULL;
}

//Utility Functions

int Prec(char ch){
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

bool isOperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

//Stack Functions for Infix to Postfix

struct Stack* createStack_itp( unsigned capacity ){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));

    if (!stack)
        return NULL;

    stack->top = -1;
    stack->capacity = capacity;

    stack->array = (int*) malloc(stack->capacity * sizeof(int));

    return stack;
}

int isEmpty_itp(struct Stack* stack){
    return stack->top == -1;
}


char peek_itp(struct Stack* stack){
    return stack->array[stack->top];
}

char pop_itp(struct Stack* stack){
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}

void push_itp(struct Stack* stack, char op){
    stack->array[++stack->top] = op;
}

//Stack Functions for Construction

struct stack* createstack(int size){
    struct stack* Stack = malloc(sizeof(struct stack));
    Stack->size = size;
    Stack->top = -1;
    Stack->array = (struct stack*)malloc(Stack->size * sizeof(struct node));
    return Stack;
}

int isFull(struct stack* stack){
    return stack->top == stack->size - 1;
}

int isEmpty(struct stack* stack){
    return stack->top == -1;
}

void push(struct stack* stack, struct stack* node){
    if(isFull(stack))
        return;
    stack->array[++stack->top] = node;
}

struct node* pop(struct stack* stack){
    if(isEmpty(stack))
        return;
    return stack->array[stack->top--];
}

