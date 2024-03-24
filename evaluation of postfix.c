//evaluation of postfix expression
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arraystackadt.h"


bool isoperator(char token)
{
    if(token=='*'||token=='/'||token=='+'||token=='-')
        return true;
    return false;
}
int calculate(int opd1,int opd2,char token)
{
    switch(token)
    {
        case '+':return(opd1+opd2);
        case '-':return(opd1-opd2);
        case '*':return(opd1*opd2);
        case '/':return(opd1/opd2);
        default:  return 0;
    }
}
int main()
{
    int opd1,opd2,result,i=0;
    int *pd;
    AST *ph;
    char postfix[25],token;

    ph=(AST*)createstack();
    printf("enter the postfix expression to evaluate:\n");
    scanf("%s",postfix);
    while(postfix[i]!='\0')
    {
    	token=postfix[i];
        if(isoperator(postfix[i]))
        {
            pd=(int*)popstack(ph);
            opd2=*pd;
            free(pd);
            pd=(int*)popstack(ph);
            opd1=*pd;
            result=calculate(opd1,opd2,token);
            *pd=result;
            pushstack(ph,pd);
        }
        else
        {
           pd=(int*)malloc(sizeof(int));
           *pd=postfix[i]-'0';
           pushstack(ph,pd);
        }
        i++;
    }
    pd=(int*)popstack(ph);
    printf("Result=%d",*pd);
    free(pd);
    destory(ph);
    return 0;
}
        

