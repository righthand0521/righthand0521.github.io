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


typedef struct ArrayStack {
    unsigned int count;
    unsigned int size;
    int *top;
    int *value;
} ArrayStack;
#define INIT_TOP        (-1)
#define INIT_VALUE      (INT_MIN)

void arrayStack_show(ArrayStack* pArrayStack)
{
    int i, j;
    for (i=0; i<pArrayStack->count; ++i)
    {
        printf("Stack %2d: top is %2d, [", (i+1), pArrayStack->top[i]);
        for (j=0; j<pArrayStack->size; ++j)
        {
            printf("%12d", pArrayStack->value[i * pArrayStack->size + j]);
        }
        printf("]\n");
    }
}

ArrayStack* arrayStack_create(unsigned int stackCount, unsigned int stackSize)
{
    ArrayStack* pRetVal = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }

    int i;

    pRetVal->count = stackCount;

    pRetVal->size = stackSize;

    pRetVal->top = (int*)malloc(sizeof(int) * pRetVal->count);
    if (pRetVal->top  == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    for (i=0; i<pRetVal->count; ++i)
    {
        pRetVal->top[i] = INIT_TOP;
    }

    pRetVal->value = (int*)malloc(sizeof(int) * (pRetVal->count * pRetVal->size));
    if (pRetVal->value == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    for (i=0; i<(pRetVal->count * pRetVal->size); ++i)
    {
        pRetVal->value[i] = INIT_VALUE;
    }

    return pRetVal;
}

void arrayStack_free(ArrayStack* pArrayStack)
{
    free(pArrayStack->top);
    free(pArrayStack->value);
    free(pArrayStack);
}

bool arrayStack_isEmpty(ArrayStack* pArrayStack, unsigned int stackNo)
{
    bool retVal = false;

    int top_idx = stackNo - 1;
    int value_idx = pArrayStack->top[top_idx];
    if (value_idx == INIT_TOP)
    {
        retVal = true;
    }

    return retVal;
}

bool arrayStack_isFull(ArrayStack* pArrayStack, unsigned int stackNo)
{
    bool retVal = false;

    int top_idx = stackNo - 1;
    int value_idx = pArrayStack->top[top_idx];
    int value_max_idx = stackNo * pArrayStack->size - 1;
    if (value_idx >= value_max_idx)
    {
        retVal = true;
    }

    return retVal;
}

void arrayStack_push(ArrayStack* pArrayStack, unsigned int stackNo, int pushValue)
{
    int top_idx = stackNo - 1;
    int value_idx = pArrayStack->top[top_idx];

    if (true == arrayStack_isFull(pArrayStack, stackNo))
    {
        DISPLAY("Stack %2u is Full: top is %2d", stackNo, value_idx);
        return;
    }

    if (value_idx == INIT_TOP)
    {
        value_idx += top_idx * pArrayStack->size;
    }
    value_idx += 1;
    pArrayStack->value[value_idx] = pushValue;
    pArrayStack->top[top_idx] = value_idx;

    DISPLAY("Stack %2u push %3d", stackNo, pushValue);
    arrayStack_show(pArrayStack);
}

int arrayStack_pop(ArrayStack* pArrayStack, unsigned int stackNo)
{
    int retVal = INIT_VALUE;

    int top_idx = stackNo - 1;
    int value_idx = pArrayStack->top[top_idx];
    int value_min_idx = (stackNo - 1) * pArrayStack->size;

    if (true == arrayStack_isEmpty(pArrayStack, stackNo))
    {
        DISPLAY("Stack %2u is Empty: top is %2d", stackNo, value_idx);
        return retVal;
    }

    retVal = pArrayStack->value[value_idx];
    pArrayStack->value[value_idx] = INIT_VALUE;
    if (value_idx == value_min_idx)
    {
        pArrayStack->top[top_idx] = INIT_TOP;
    }
    else
    {
        value_idx -= 1;
        pArrayStack->top[top_idx] = value_idx;
    }

    DISPLAY("stack %2u pop %3d", stackNo, retVal);
    arrayStack_show(pArrayStack);

    return retVal;
}

int arrayStack_peek(ArrayStack* pArrayStack, unsigned int stackNo)
{
    int retVal = INIT_VALUE;

    int top_idx = stackNo - 1;
    int value_idx = pArrayStack->top[top_idx];

    if (value_idx == INIT_TOP)
    {
        DISPLAY("Stack %2u is Empty: top is %2d", stackNo, value_idx);
        return retVal;
    }
    retVal = pArrayStack->value[value_idx];

    return retVal;
}


int main(int argc, char **argv)
{
    srand(time(NULL));

    unsigned int stackNum = 1;
    unsigned int stackSize = 10;
    int i;

    ArrayStack* pArrayStack = arrayStack_create(stackNum, stackSize);
    if (pArrayStack == NULL)
    {
        return EXIT_FAILURE;
    }
    arrayStack_show(pArrayStack);

    if (true == arrayStack_isEmpty(pArrayStack, stackNum))
    {
        printf("[%03d]stack is empty\n", __LINE__);
    }

    int pushCount = rand()%stackSize;
    int pushValue;
    for (i=0; i<pushCount; ++i)
    {
        pushValue = rand()%100;
        arrayStack_push(pArrayStack, stackNum, pushValue);
    }
    if (true == arrayStack_isEmpty(pArrayStack, stackNum))
    {
        arrayStack_free(pArrayStack);
        printf("[%03d]stack is empty\n", __LINE__);
        return EXIT_SUCCESS;
    }

    int peekData = arrayStack_peek(pArrayStack, stackNum);
    printf("[%03d]stack peek value: %3d; ", __LINE__, peekData);
    arrayStack_show(pArrayStack);

    int popCount = rand()%pushCount + 1;
    for (i=0; i<popCount; ++i)
    {
        arrayStack_pop(pArrayStack, stackNum);
    }
    if (true == arrayStack_isEmpty(pArrayStack, stackNum))
    {
        arrayStack_free(pArrayStack);
        printf("[%03d]stack is empty\n", __LINE__);
        return EXIT_SUCCESS;
    }

    peekData = arrayStack_peek(pArrayStack, stackNum);
    printf("[%03d]stack peek value: %3d; ", __LINE__, peekData);
    arrayStack_show(pArrayStack);

    arrayStack_free(pArrayStack);

    return EXIT_SUCCESS;
}

