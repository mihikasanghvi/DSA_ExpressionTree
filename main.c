#include "expTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char s[] = "(((9+3)-7)*(3+4))/5";
    //((1+2)*(9-(4/5)))
    //char s1[30];
    //printf("Enter Infix Expression : ");
    //fgets(s1,20,stdin);
    struct node* root;
    char q[30];
    strcpy(q,infixToPostfix(&s));
    root = init_tree(&q);
    inorder_r(root);
    printf("\n");
    float a;
    a = compute(root);
    printf("\n%0.2f",a);
    return 0;
}
