#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stacklladt.h"

bool isoperator(char token)
{
    switch(token)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
    }
    return false;
}

int priority(char token)
{   
    if(token=='^')
        return 3;
    else if(token=='*' || token=='/')
        return 2;
    else if(token=='+' || token=='-')
        return 1;
    return 0;
}

int main()
{
    STACK *ph;
    char postfix[25], token;
    char *pt;
    int i = 0;

    ph = creatstack();
    printf("Enter the infix expression\n");
    while((token = getchar()) != '0')
    {
        if(token == '(')
        {
			pt=(char*)malloc(sizeof(char));
			*pt=token;
            pushstack(ph,pt);
        }
        else if(token == ')')
        {
            pt = (char*)popstack(ph);
            while(*pt != '(')
            {
                postfix[i++] = *pt;
                free(pt);
                pt = (char*)popstack(ph);
            }
            free(pt); // Free the '(' character
        }
        else if(isoperator(token))
        {
            pt = (char*)stacktop(ph);
            while(!emptystack(ph) && priority(token) <= priority(*pt))
            {
                pt = (char*)popstack(ph);
                postfix[i++] = *pt;
                free(pt);
                pt = (char*)stacktop(ph);
            }
            pt = (char*)malloc(sizeof(char));
            *pt = token;
            pushstack(ph, (void*)pt);
        }
        else
        {
            postfix[i++] = token;
        }
    }

    // Pop any remaining operators from the stack
    while(!emptystack(ph))
    {
        pt = (char*)popstack(ph);
        postfix[i++] = *pt;
        free(pt);
    }

    postfix[i] = '\0';
    printf("Postfix expression: %s", postfix);
    
    destorystack(ph);
    return 0;
}

