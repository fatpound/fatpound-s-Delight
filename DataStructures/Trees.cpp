#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct BinaryTree
{
    struct BinaryTree *left;
    int n;
    struct BinaryTree *right;
}
BINARY_TREE;

typedef struct BinarySearchTree
{
    struct BinarySearchTree *left;
    int n;
    struct BinarySearchTree *right;
}
BINARY_SEARCH_TREE;

typedef BINARY_TREE BT;
typedef BINARY_SEARCH_TREE BST;

#define ALLOCATE_BT  (BT*)  malloc(sizeof(BT))
#define ALLOCATE_BST (BST*) malloc(sizeof(BST))

BST* AddToBST(BST* root, int num)
{
    if (root == NULL)
    {
        root = ALLOCATE_BST;

        root->left = NULL;
        root->n    = num;
        root->right = NULL;

        return root;
    }

    if (num < root->n)
    {
        root->left = AddToBST(root->left, num);
    }

    if (num > root->n)
    {
        root->right = AddToBST(root->right, num);
    }

    return root;
}
BST* FindNode(BST* root, int num)
{
    if (root == NULL)
        return NULL;

    if (num < root->n)
        return FindNode(root->left, num);

    if (num > root->n)
        return FindNode(root->right, num);

    return root;
}
BST* FindParent(BST* root, BST* node)
{
    if (root == NULL || root == node || root->left == node || root->right == node)
        return root;

    if (FindParent(root->left, node) != NULL)
        return FindParent(root->left, node);

    if (FindParent(root->right, node) != NULL)
        return FindParent(root->right, node);
}
BST* GetSmallestNode(BST* root)
{
    if (root->left == NULL)
        return root;

    return GetSmallestNode(root->left);
}
BST* GetGreatestNode(BST* root)
{
    if (root->right == NULL)
        return root;

    return GetGreatestNode(root->right);
}

void ListTreePreorder(BST* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->n);
    ListTreePreorder(root->left);
    ListTreePreorder(root->right);
}
void ListTreeInorder(BST* root)
{
    if (root == NULL)
        return;

    ListTreeInorder(root->left);
    printf("%d ", root->n);
    ListTreeInorder(root->right);
}
void ListTreePostorder(BST* root)
{
    if (root == NULL)
        return;

    ListTreePostorder(root->left);
    ListTreePostorder(root->right);
    printf("%d ", root->n);
}
void ListLeaves(BST* root)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        printf("%d ", root->n);
        return;
    }

    ListLeaves(root->left);
    ListLeaves(root->right);
}

void ListTreePreorder_Reverse(BST* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->n);
    ListTreePreorder_Reverse(root->right);
    ListTreePreorder_Reverse(root->left);
}
void ListTreeInorder_Reverse(BST* root)
{
    if (root == NULL)
        return;

    ListTreeInorder_Reverse(root->right);
    printf("%d ", root->n);
    ListTreeInorder_Reverse(root->left);
}
void ListTreePostorder_Reverse(BST* root)
{
    if (root == NULL)
        return;

    ListTreePostorder_Reverse(root->right);
    ListTreePostorder_Reverse(root->left);
    printf("%d ", root->n);
}
void ListLeaves_Reverse(BST* root)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        printf("%d ", root->n);
        return;
    }

    ListLeaves_Reverse(root->right);
    ListLeaves_Reverse(root->left);
}

int NodeCount(BT* root)
{
    if (root == NULL)
        return 0;

    return 1 + NodeCount(root->left) + NodeCount(root->right);
}
int NodeCount(BST* root)
{
    if (root == NULL)
        return 0;

    return 1 + NodeCount(root->left) + NodeCount(root->right);
}
int TreeSum(BT* root)
{
    if (root == NULL)
        return 0;

    return root->n + TreeSum(root->left) + TreeSum(root->right);
}
int TreeSum(BST* root)
{
    if (root == NULL)
        return 0;

    return root->n + TreeSum(root->left) + TreeSum(root->right);
}

void DeleteTree(BST* root)
{
    if (root == NULL)
        return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    free(root);
}
void DeleteNode(void* rootptr_address, BST* node, int mode)
{
    /// Since we don't use a pointer to the parent node, that is a good solution
    /// Usage: DeleteNode(&tree, tree, mode)

    // 0 = self
    // 1 = self with everything connected to it from under

    switch (mode)
    {
        case 0:
        {
            if (node->left == NULL)
            {
                if (node->right == NULL)
                {
                    char* p = 0;
                    *(BST*)rootptr_address = *(BST*)&p;
                }
                else
                {
                    *(BST*)rootptr_address = *(BST*)&node->right;
                }
            }
            else
            {
                *(BST*)rootptr_address = *(BST*)&node->left;
                node->left->right = node->right;
            }

            break;
        }

        case 1:
        {
            DeleteTree(node);

            char* p = 0;
            *(BST*)rootptr_address = *(BST*)&p;

            break;
        }

        default:
            break;
    }
}
