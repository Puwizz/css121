#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int coeff;
    int pow;
    struct Node *next;
};
 
struct Node* createNode(int c, int p)
{ 
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->pow = p;
    newNode->next = NULL;
    return newNode;
}
void insertTerm(struct Node **head, int c, int p)
{
    if(c == 0) return;
    struct Node *newNode = createNode(c, p);
    if(*head == NULL || (*head)->pow < p)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct Node *cur = *head;
    struct Node *prev = NULL;
    while(cur != NULL && cur->pow > p)
    {
        prev = cur;
        cur = cur->next;
    }
    if(cur != NULL && cur->pow == p)
    {
        cur->coeff += c;
        if(cur->coeff == 0)
        {
            if(prev == NULL)
            {
                *head = cur->next;
            }else
            {
                prev->next = NULL;
            }
            
        }
    }else
    {
        //struct Node *newNode = createNode(c, p);
        newNode->next = cur;
        if(prev != NULL)
        {
            prev->next = newNode;
        }
    }

    
}
struct Node* add(struct Node* p1, struct Node* p2)
{
    struct Node* head = NULL;
    struct Node* tail = NULL;
    while(p1 != NULL || p2 != NULL)
    {
        int c,p;
        if(p1 == NULL)
        {
            c = p2->coeff; p = p2->pow;
            p2 = p2->next;
        }else if(p2 == NULL)
        {
            c = p1->coeff; p = p1->pow;
            p1 = p1->next;
        }else if(p1->pow > p2->pow)
        {
            c = p1->coeff; p = p1->pow;
            p1 = p1->next;
        }else if(p2->pow > p1->pow)
        {
            c = p2->coeff; p = p2->pow;
            p2 = p2->next;
        }else
        {
            c = p1->coeff + p2->coeff;
            p = p1->pow;
            p1 = p1->next;
            p2 = p2->next;
        }
        if(c != 0)
        {
            struct Node* newNode = createNode(c, p);
            if(head == NULL)
            {
                head = newNode;
                tail = newNode;
            }else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }
    return head;
}

void printPoly(struct Node* head)
{
    if(head == NULL)
    {
        printf("0\n");
        return;
    }
    struct Node *temp = head;
    int first = 1;
    while(temp != NULL)
    {
        if(first)
        {
            if(temp->pow == 0) printf("%d",temp->coeff);
            else printf("%dx^%d",temp->coeff, temp->pow);
            first = 0;
        }else
        {
            if(temp->coeff >= 0) printf("+");
            else printf(" ");
            if(temp->pow == 0) printf("%d",temp->coeff);
            else printf("%dx^%d",temp->coeff, temp->pow);
        }
        temp = temp->next;
    }
    printf("\n");
    return;
}
int main()
{
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    insertTerm(&poly1, 2, 0);
    insertTerm(&poly1, 4, 3);
    insertTerm(&poly1, 3, 2);
    insertTerm(&poly1, 5, 0);
    printPoly(poly1);
    return 0;
}