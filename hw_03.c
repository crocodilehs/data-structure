#include <stdio.h>
#include <string.h>
#define MAX 100

char stack[MAX];
int top = -1;
int priority(char st);

int main()
{
    char infix[MAX];
    char postfix[MAX];
    int i, j, top = -1;
    scanf("%s", infix);
    for (i = 0, j = 0; i <= strlen(infix) - 1; i++)
    {
        switch (infix[i])
        {
        case '+':
            while (priority(stack[top]) >= priority(infix[i]))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
            break;
        case '-':
            while (priority(stack[top]) >= priority(infix[i]))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
            break;
        case '*':
            while (priority(stack[top]) >= priority(infix[i]))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
            break;
        case '/':
            while (priority(stack[top]) >= priority(infix[i]))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
            break;
        case '(':
            stack[++top] = infix[i];
            break;
        case ')':
            while (stack[top] != '(')
            {
                postfix[j++] = stack[top--];
            }
            top--;
            break;
        default:
            postfix[j++] = infix[i];
        }
    }
    while (top > -1)
    {
        postfix[j++] = stack[top--];
    }

    for (int k = 0; k <= strlen(postfix) - 1; k++)
    {
        printf("%c", postfix[k]);
    }
    return 0;
}
int priority(char st)
{
    switch (st)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    default:
        return 0;
    }
}
/* 
1+3*5/4
output->135*4/+

a+(b*c-(1/2-3)*d)*e
output->abc*12/3-d*-e*+
*/