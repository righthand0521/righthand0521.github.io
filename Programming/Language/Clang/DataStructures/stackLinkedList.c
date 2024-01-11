#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>


#define DISPLAY(...) do { \
    fprintf(stdout, "[%s][%s][%d]", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stdout, __VA_ARGS__); \
    fprintf(stdout, "\n"); \
} while (0)


typedef struct Node {
    int data;
    struct Node* next;
} Node;

#ifndef METHOD_1
#define METHOD_1    1

void stack_show(struct Node* pTop)
{
    Node* pHead = pTop;
    while (pHead != NULL)
    {
        printf("%3d -> ", pHead->data);
        pHead = pHead->next;
    }
    printf("NULL\n");
}

void stack_push(struct Node** pTop, int value)
{
    Node* pNew = (Node*)malloc(sizeof(struct Node));
    if (pNew == NULL)
    {
        perror("malloc");
        return;
    }
    pNew->data = value;
    pNew->next = (*pTop);
    *(pTop) = pNew;
}

int stack_pop(struct Node** pTop)
{
    int retVal = INT_MIN;

    Node* pHead = (*pTop);
    if (pHead == NULL)
    {
        printf("Stack is Empty");
        return retVal;
    }
    retVal = pHead->data;
    (*pTop) = pHead->next;
    free(pHead);

    return retVal;
}

int stack_peek(struct Node* pTop)
{
    int retVal = INT_MIN;

    Node* pHead = pTop;
    if (pHead == NULL)
    {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}

bool stack_empty(struct Node* pTop)
{
    bool retVal = false;

    Node *pHead = pTop;
    if (pHead == NULL)
    {
        retVal = true;
    }

    return retVal;
}

void stack_free(struct Node** pTop)
{
    Node* pFree = (*pTop);
    while ((*pTop) != NULL)
    {
        (*pTop) = (*pTop)->next;
        free(pFree);
        pFree = (*pTop);
    }
}


int stack_test()
{
    srand(time(NULL));

    Node* pTop = NULL;
    int pushCount = rand()%10 + 1;
    int pushValue;
    int popCount;
    int i;

    if (stack_empty(pTop) == true)
    {
        printf("[%03d]stack is empty\n", __LINE__);
    }
    pushCount = rand()%10 + 1;
    for (i=0; i<pushCount; ++i)
    {
        pushValue = rand()%100;
        stack_push(&pTop, pushValue);
        stack_show(pTop);
    }
    popCount = rand()%pushCount + 1;
    for (i=0; i<popCount; ++i)
    {
        stack_pop(&pTop);
        stack_show(pTop);
    }
    stack_free(&pTop);
    pTop = NULL;

    if (stack_empty(pTop) == true)
    {
        printf("[%03d]stack is empty\n", __LINE__);
    }
    pushCount = rand()%10 + 1;
    for (i=0; i<pushCount; ++i)
    {
        pushValue = rand()%100;
        stack_push(&pTop, pushValue);
        stack_show(pTop);
    }
    while (stack_empty(pTop) == false)
    {
        stack_pop(&pTop);
        stack_show(pTop);
    }
    stack_free(&pTop);
    pTop = NULL;

    return EXIT_SUCCESS;
}
#endif

#ifndef METHOD_2
#define METHOD_2    1

Node *top = NULL;

void linkedListStack_show()
{
    Node *pHead = top;
    while (pHead != NULL)
    {
        printf("%4d -> ", pHead->data);
        pHead = pHead->next;
    }
    printf("NULL\n");
}

void linkedListStack_push(int value)
{
    Node *pNew = (Node *)malloc(sizeof(struct Node));
    if (pNew == NULL)
    {
        perror("malloc");
        return;
    }
    pNew->data = value;
    pNew->next = top;
    top = pNew;
}

int linkedListStack_pop()
{
    int retVal = INT_MIN;

    Node *pHead = top;
    if (pHead == NULL)
    {
        DISPLAY("Stack is Empty");
        return retVal;
    }
    retVal = pHead->data;
    top = pHead->next;
    free(pHead);

    return retVal;
}

int linkedListStack_peek()
{
    int retVal = INT_MIN;

    Node *pHead = top;
    if (pHead == NULL)
    {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}

bool linkedListStack_isEmpty()
{
    bool retVal = false;

    Node *pHead = top;
    if (pHead == NULL)
    {
        retVal = true;
    }

    return retVal;
}


int linkedListStack()
{
    srand(time(NULL));

    if (linkedListStack_isEmpty() == true)
    {
        printf("[%03d]stack is empty\n", __LINE__);
    }

    int i;

    int pushCount = rand()%10 + 1;
    int pushValue;
    for (i=0; i<pushCount; ++i)
    {
        pushValue = rand()%100;
        linkedListStack_push(pushValue);
        printf("[%03d]stack push value: %3d; ", __LINE__, pushValue);
        linkedListStack_show();
    }

    if (linkedListStack_isEmpty() == true)
    {
        printf("[%03d]stack is empty\n", __LINE__);
        return EXIT_SUCCESS;
    }
    int peekData = linkedListStack_peek();
    printf("[%03d]stack peek value: %3d; ", __LINE__, peekData);
    linkedListStack_show();

    int popCount = rand()%pushCount + 1;
    int popValue;
    for (i=0; i<popCount; ++i)
    {
        popValue = linkedListStack_pop();
        printf("[%03d]stack pop  value: %3d; ", __LINE__, popValue);
        linkedListStack_show();
    }

    if (linkedListStack_isEmpty() == true)
    {
        printf("[%03d]stack is empty\n", __LINE__);
        return EXIT_SUCCESS;
    }
    peekData = linkedListStack_peek();
    printf("[%03d]stack peek value: %3d; ", __LINE__, peekData);
    linkedListStack_show();

    return EXIT_SUCCESS;
}
#endif


int main(int argc, char **argv)
{
#if (METHOD_1)
    stack_test();
#endif
#if (METHOD_2)
    printf("================================================================\n");
    sleep(1);
    linkedListStack();
#endif


    return EXIT_SUCCESS;
}

