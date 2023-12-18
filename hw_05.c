#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *link;
} node;
typedef node *link_list;
link_list head;

void printlist();
void ADD(link_list *head, int data);
void INSERT(link_list *head, int data, int index);
void DELETE(link_list *head, int index);
void REVERSE(link_list *head);

int main()
{
    char str[100], s[50];
    int num, index;
    head = (link_list)malloc(sizeof(node));
    head = NULL;
    while (scanf("%s", str) != EOF)
    {
        if (str[0] == 'A')
        {
            scanf("%d", &num);
            ADD(&head, num);
            printlist();
        }
        else if (str[0] == 'I')
        {
            scanf("%d %s %d", &num, s, &index);
            INSERT(&head, num, index);
            printlist();
        }
        else if (str[0] == 'D')
        {
            scanf("%d", &num);
            DELETE(&head, num);
            printlist();
        }
        else if (str[0] == 'R')
        {
            REVERSE(&head);
            printlist();
        }
    }
    return 0;
}
void printlist()
{
    node *temp = head;
    while (temp->link != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("%d\n", temp->data);
}
void ADD(link_list *head, int data)
{
    node *ttmp = malloc(sizeof(node));
    ttmp->data = data;
    ttmp->link = NULL;
    if ((*head) == NULL)
        *head = ttmp;
    else
    {
        node *temp = *head;
        while (temp->link != NULL)
            temp = temp->link;
        temp->link = ttmp;
    }
}
void INSERT(link_list *head, int data, int index)
{
    node *padd = malloc(sizeof(node));
    node *temp = *head;
    padd->data = data;
    padd->link = NULL;
    if (index == 0)
    {
        padd->link = *head;
        *head = padd;
        return;
    }
    for (int i = 1; i < index; i++)
    {
        temp = temp->link;
        if (temp == NULL)
        {
            printf("Index is out of range!!\n");
            return;
        }
    }
    padd->link = temp->link;
    temp->link = padd;
}
void DELETE(link_list *head, int index)
{
    node *temp = *head;
    node *ptr = NULL;
    for (int i = 1; i < index; i++)
    {
        if (temp == NULL)
            break;
        ptr = temp;
        temp = temp->link;
    }
    if (temp == *head)
    {
        *head = temp->link;
        free(temp);
        temp = NULL;
    }
    else if (temp == NULL)
        printf("Index is out of range!!\n");
    else
    {
        ptr->link = temp->link;
        free(temp);
        temp = NULL;
    }
}
void REVERSE(link_list *head)
{
    node *temp = *head;
    node *trail;
    node *middle = NULL;
    while (temp)
    {
        trail = middle;
        middle = temp;
        temp = temp->link;
        middle->link = trail;
    }
    *head = middle;
}
/*
ADD 5
ADD 10
ADD 90
INSERT 11 BEHIND 1
DELETE 4
INSERT 9 BEHIND 5
REVERSE
*/
/*
out put
5
5 10
5 10 90
5 11 10 90
5 11 10
Index is out of range!!
5 11 10
10 11 5
*/
/*
ADD 10
INSERT 6 BEHIND 5
INSERT 6 BEHIND 0
REVERSE
ADD 1
REVERSE
ADD 3
DELETE 2
DELETE 5
INSERT 11 BEHIND 3
REVERSE
*/
/*out put
10
Index is out of range!!
10
6 10
10 6
10 6 1
1 6 10
1 6 10 3
1 10 3
Index is out of range!!
1 10 3
1 10 3 11
11 3 10 1
*/