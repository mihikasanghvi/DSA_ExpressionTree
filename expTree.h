#ifndef est_H_INCLUDED
#define est_H_INCLUDED
#include <stdbool.h>
/* Prototypes for the functions */

typedef struct node
{
    char data;
    struct node *left, *right;
}node;

#define MAX_SIZE 100

typedef struct stack
{
    int size;
    int top;
    struct node** array;
}stack;

struct Stack
{
    int top;
    unsigned capacity;
    int* array;
}Stack;

struct node* init_tree(char* p);

struct node* newNode(char data);

void inorder_r(struct node* root);

char* infixToPostfix(char* exp);

//Evaluation Functions

float compute(struct node* root);

float process(char op, float x, float y);

bool isLeaf(struct node* root);

//Utility Functions

int Prec(char ch);

bool isOperator(char c);

//Stack Functions for Infix to Postfix

struct Stack* createStack_itp( unsigned capacity );

int isEmpty_itp(struct Stack* stack);

char peek_itp(struct Stack* stack);

char pop_itp(struct Stack* stack);

void push_itp(struct Stack* stack, char op);

//Stack Functions for Construction

struct stack* createstack(int size);

int isFull(struct stack* stack);

int isEmpty(struct stack* stack);

void push(struct stack* stack, struct stack* node);

struct node* pop(struct stack* stack);

#endif // est_H_INCLUDED



