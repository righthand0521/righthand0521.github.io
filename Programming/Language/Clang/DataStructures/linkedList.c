#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DISPLAY(...) do { \
    fprintf(stdout, "[%s][%s][%d]", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stdout, __VA_ARGS__); \
    fprintf(stdout, "\n"); \
} while (0)


struct ListNode {
    int val;
    struct ListNode *next;
};

void display(struct ListNode* pHead)
{
#define TEST_DISPLAY    0
#if (TEST_DISPLAY)
#define STR_LINK    ","
#define STR_END     ""
#else
#define STR_LINK    " -> "
#define STR_END     " -> "
#endif
    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL)
    {
        printf("%d%s", pCurrent->val, (pCurrent->next==NULL)?STR_END:STR_LINK);
        pCurrent = pCurrent->next;
    }
#if (TEST_DISPLAY)
#else
    printf("NULL\n");
#endif
}

void freeNode(struct ListNode* pHead)
{
    struct ListNode* pCurrent = pHead;
    struct ListNode* pFree = NULL;
    while (pCurrent != NULL)
    {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
    }
}

struct ListNode* addValueToEnd(struct ListNode* pHead, int value)
{
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL)
    {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;
    DISPLAY("Insert at Tail: %3d", value);

    if (pHead == NULL)
    {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pCurrent = pHead;
    while (pCurrent->next != NULL)
    {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNew;

    return pHead;
}

struct ListNode* removeValueFromEnd(struct ListNode* pHead)
{
    if (pHead == NULL)
    {
        return pHead;
    }

    if (pHead->next == NULL)
    {
        DISPLAY("Remove at Tail: %3d", pHead->val);
        free(pHead);
        pHead = NULL;
        return pHead;
    }

    struct ListNode *pPrevious = NULL;
    struct ListNode *pFree = pHead;
    while (pFree->next != NULL)
    {
        pPrevious = pFree;
        pFree = pFree->next;
    }
    pPrevious->next = NULL;
    DISPLAY("Remove at Tail: %3d", pFree->val);
    free(pFree);
    pFree = NULL;

    return pHead;
}

struct ListNode* addValueToStart(struct ListNode* pHead, int value)
{
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL)
    {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;
    DISPLAY("Insert at Head: %3d", value);

    if (pHead == NULL)
    {
        pHead = pNew;
        return pHead;
    }

    pNew->next = pHead;
    pHead = pNew;

    return pHead;
}

struct ListNode* removeValueFromStart(struct ListNode* pHead)
{
    if (pHead == NULL)
    {
        return pHead;
    }

    struct ListNode *pFree = pHead;
    if (pHead != NULL)
    {
        pHead = pHead->next;
    }
    DISPLAY("Remove at Head: %3d", pFree->val);
    free(pFree);
    pFree = NULL;

    return pHead;
}

struct ListNode* addValueToMiddle(struct ListNode* pHead, int value)
{
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL)
    {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;
    DISPLAY("Insert at Middle: %3d", value);

    if (pHead == NULL)
    {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL)
    {
        // from small to large
        if (pCurrent->val > value)
        {
            break;
        }
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }
    if (pPrevious == NULL)
    {
        pNew->next = pHead;
        pHead = pNew;
        return pHead;
    }
    pNew->next = pPrevious->next;
    pPrevious->next = pNew;

    return pHead;
}

struct ListNode* removeValueFromMiddle(struct ListNode* pHead, int value)
{
    if (pHead == NULL)
    {
        return pHead;
    }

    struct ListNode* pPrevious = NULL;
    struct ListNode* pFree = pHead;
    while (pFree != NULL)
    {
        if (pFree->val == value)
        {
            break;
        }
        pPrevious = pFree;
        pFree = pFree->next;
    }

    if (pFree == NULL)
    {
        DISPLAY("%3d does not exist", value);
        return pHead;
    }

    if (pPrevious == NULL)
    {
        pHead = pHead->next;
    }
    else
    {
        pPrevious->next = pFree->next;
    }
    DISPLAY("Remove at Middle: %3d", pFree->val);
    free(pFree);
    pFree = NULL;

    return pHead;
}


#define TEST_COUNT      3
int main(int argc, char **argv)
{
    srand(time(NULL));

    typedef struct ListNode* (*executeFunc)(struct ListNode*, int);
    const struct exampleType {
        executeFunc eFunc;
    } example[] = {
        {addValueToEnd}
        , {addValueToStart}
        , {addValueToMiddle}
    };
    int numberOfExample = sizeof(example) / sizeof(example[0]);
    enum Method {
        addEnd = 0
        , addStart
        , addMiddle
    };

    struct ListNode* pHead = NULL;
    int listCount;
    int listValue;
    int removeStart;
    int removeEnd;
    int removeMiddle;
    int i, j;
    for (i=0; i<numberOfExample; ++i)
    {
        listCount = rand()%3 + TEST_COUNT;

        // Add Value to List
        for (j=1; j<=listCount; ++j)
        {
            listValue = rand()%100;
            if (j == 1)
            {
                removeStart = listValue;
            }
            else if (j == listCount)
            {
                removeEnd = listValue;
            }
            else
            {
                removeMiddle = listValue;
            }
            pHead = example[i].eFunc(pHead, listValue);
            display(pHead);
        }

        // Remove Value from List
        switch (i)
        {
            case addEnd:
                for (j=0; j<TEST_COUNT; ++j)
                {
                    pHead = removeValueFromEnd(pHead);
                    display(pHead);
                }
                break;
            case addStart:
                for (j=0; j<TEST_COUNT; ++j)
                {
                    pHead = removeValueFromStart(pHead);
                    display(pHead);
                }
                break;
            case addMiddle:
                pHead = removeValueFromMiddle(pHead, removeMiddle);
                display(pHead);
                pHead = removeValueFromMiddle(pHead, removeStart);
                display(pHead);
                pHead = removeValueFromMiddle(pHead, removeEnd);
                display(pHead);
                break;
            default:
                break;
        }
        printf("\n");

        freeNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}

