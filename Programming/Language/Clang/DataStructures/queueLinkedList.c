#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>


#define DISPLAY(...) do { \
    fprintf(stdout, "[%s][%s][%d]", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stdout, __VA_ARGS__); \
    fprintf(stdout, "\n"); \
} while (0)


typedef struct Node {
    int data;
    struct Node *next;
} Node;
Node *head = NULL;
Node *tail = NULL;

void show()
{
    Node *pHead = head;
    while (pHead != NULL)
    {
        printf("%4d -> ", pHead->data);
        pHead = pHead->next;
    }
    printf("NULL\n");
}

void enqueue(int value)
{
    Node *pNew = (Node *)malloc(sizeof(struct Node));
    if (pNew == NULL)
    {
        perror("malloc");
        return;
    }
    pNew->data = value;
    pNew->next = NULL;

    if (tail != NULL)
    {
        tail->next = pNew;
    }
    tail = pNew;
    if (head == NULL)
    {
        head = tail;
    }
}

int dequeue()
{
    int retVal = INT_MIN;

    Node *pHead = head;
    if (pHead == NULL)
    {
        DISPLAY("Queue is Empty");
        return retVal;
    }
    retVal = pHead->data;

    head = pHead->next;
    if (head == NULL)
    {
        tail = NULL;
    }

    free(pHead);

    return retVal;
}

int peek()
{
    int retVal = INT_MIN;

    Node *pHead = head;
    if (pHead == NULL)
    {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}

bool isEmpty()
{
    bool retVal = false;

    Node *pHead = head;
    if (pHead == NULL)
    {
        retVal = true;
    }

    return retVal;
}


int main(int argc, char **argv)
{
    srand(time(NULL));

    if (isEmpty() == true)
    {
        printf("[%03d]queue is empty\n", __LINE__);
    }

    int i;

    int enqueueCount = rand()%10;
    int enqueueValue;
    for (i=0; i<enqueueCount; ++i)
    {
        enqueueValue = rand()%100;
        enqueue(enqueueValue);
        printf("[%03d]queue enqueue value: %3d; ", __LINE__, enqueueValue);
        show();
    }

    if (isEmpty() == true)
    {
        printf("[%03d]queue is empty\n", __LINE__);
        return EXIT_SUCCESS;
    }
    int peekData = peek();
    printf("[%03d]queue peek    value: %3d; ", __LINE__, peekData);
    show();

    int dequeueCount = rand()%enqueueCount + 1;
    int dequeueValue;
    for (i=0; i<dequeueCount; ++i)
    {
        dequeueValue = dequeue();
        printf("[%03d]queue dequeue value: %3d; ", __LINE__, dequeueValue);
        show();
    }

    if (isEmpty() == true)
    {
        printf("[%03d]queue is empty\n", __LINE__);
        return EXIT_SUCCESS;
    }
    peekData = peek();
    printf("[%03d]queue peek    value: %3d; ", __LINE__, peekData);
    show();

    return EXIT_SUCCESS;
}
