#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DISPLAY(...) do { \
    fprintf(stdout, "[%s][%s][%d]", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stdout, __VA_ARGS__); \
    fprintf(stdout, "\n"); \
} while (0)


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// iterative traversal by stack
struct StackNode {
    struct TreeNode *pTree;
    struct StackNode *next;
};

void push(struct StackNode** pTop, struct TreeNode* pTree)
{
    struct StackNode* pNew = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (pNew == NULL)
    {
        perror("malloc");
        return;
    }
    pNew->pTree  = pTree;
    pNew->next = (*pTop);
    (*pTop) = pNew;
}

struct TreeNode* pop(struct StackNode** pTop)
{
    if (pTop == NULL)
    {
        perror("Stack Underflow");
        return NULL;
    }

    struct StackNode *pCurrent = *pTop;
    struct TreeNode *pTree = pCurrent->pTree;
    *pTop = pCurrent->next;
    free(pCurrent);

    return pTree;
}

// traversal
void preOrder(struct TreeNode* pRoot)
{
    if (pRoot != NULL)
    {
        printf("%4d", pRoot->val);
        preOrder(pRoot->left);
        preOrder(pRoot->right);
    }
}

void inOrder(struct TreeNode* pRoot)
{
    if (pRoot != NULL)
    {
        inOrder(pRoot->left);
        printf("%4d", pRoot->val);
        inOrder(pRoot->right);
    }
}

void inOrder_iterative(struct TreeNode* pRoot)
{
    struct TreeNode* pCurrent = pRoot;
    struct StackNode* pTop = NULL;

    while (1)
    {
        if (pCurrent !=  NULL)
        {
            push(&pTop, pCurrent);
            pCurrent = pCurrent->left;
            continue;
        }

        if (pTop != NULL)
        {
            pCurrent = pop(&pTop);
            printf("%4d", pCurrent->val);
            pCurrent = pCurrent->right;
            continue;
        }

        break;
    }
}

void postOrder(struct TreeNode* pRoot)
{
    if (pRoot != NULL)
    {
        postOrder(pRoot->left);
        postOrder(pRoot->right);
        printf("%4d", pRoot->val);
    }
}

void tree_traversal(struct TreeNode* pRoot)
{
    printf("Recurive  Preorder  Traversal:");
    preOrder(pRoot);
    printf("\n");

    printf("Recurive  Inorder   Traversal:");
    inOrder(pRoot);
    printf("\n");

    printf("Iterative Inorder   Traversal:");
    inOrder_iterative(pRoot);
    printf("\n");

    printf("Recurive  Postorder Traversal:");
    postOrder(pRoot);
    printf("\n");
}

//
struct TreeNode* createNode(int value)
{
    struct TreeNode* pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = value;
    pRetVal->left = NULL;
    pRetVal->right = NULL;

    return pRetVal;
}

void freeNode(struct TreeNode* pRoot)
{
    if (pRoot != NULL)
    {
        freeNode(pRoot->left);
        freeNode(pRoot->right);
        free(pRoot);
    }
}

//
struct TreeNode* binaryTree_insert(struct TreeNode* pRoot, int value)
{
    if (pRoot == NULL)
    {
        return createNode(value);
    }

    if (pRoot->left != NULL)
    {
        pRoot->right = binaryTree_insert(pRoot->right, value);
        DISPLAY("Insert %3d in Right Tree", value);
        return pRoot;
    }

    pRoot->left = binaryTree_insert(pRoot->left, value);
    DISPLAY("Insert %3d in Left Tree", value);
    return pRoot;
}

struct TreeNode* binarySearchTree_insert(struct TreeNode* pRoot, int value)
{
    if (pRoot == NULL)
    {
        return createNode(value);
    }

    if (value <= pRoot->val)
    {
        pRoot->left = binarySearchTree_insert(pRoot->left, value);
        DISPLAY("Insert %3d in  Left Tree", value);
    }
    else if (value > pRoot->val)
    {
        pRoot->right = binarySearchTree_insert(pRoot->right, value);
        DISPLAY("Insert %3d in Right Tree", value);
    }

    return pRoot;
}


int main(int argc, char **argv)
{
    srand(time(NULL));

    struct TreeNode* pBinaryTree = NULL;
    struct TreeNode* pBinarySearchTree = NULL;
    int treeCount = rand()%6 + 2;
    int treeValue;
    int i;
    for (i=0; i<treeCount; ++i)
    {
        treeValue = rand()%100;
        DISPLAY("Insert Value: %4d", treeValue);

        pBinaryTree = binaryTree_insert(pBinaryTree, treeValue);
        DISPLAY("Binary Tree");
        tree_traversal(pBinaryTree);

        pBinarySearchTree = binarySearchTree_insert(pBinarySearchTree, treeValue);
        DISPLAY("Binary Search Tree");
        tree_traversal(pBinarySearchTree);

        printf("\n");
    }
    freeNode(pBinaryTree);
    pBinaryTree = NULL;
    freeNode(pBinarySearchTree);
    pBinarySearchTree = NULL;


    return EXIT_SUCCESS;
}

