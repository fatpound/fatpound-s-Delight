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

void ListLeavesReverse(BST* root)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        printf("%d ", root->n);
        return;
    }

    ListLeavesReverse(root->right);
    ListLeavesReverse(root->left);
}


int NodeCount(BST* root)
{
    if (root == NULL)
        return 0;

    return 1 + NodeCount(root->left) + NodeCount(root->right);
}

int BT_Sum(BT* root)
{
    if (root == NULL)
        return 0;

    return root->n + BTSum(root->left) + BTSum(root->right);
}

int BST_Sum(BST* root)
{
    if (root == NULL)
        return 0;

    return root->n + BSTSum(root->left) + BSTSum(root->right);
}


void DeleteTree(BST* root)
{
    if (root == NULL)
        return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    free(root);
}
void DeleteNode(void* rootptr_address, BST* root, int mode)
{
    /// Since we don't use a pointer to the root node, that is an optimized solution
    /// Usage: DeleteNode(&tree, tree, mode)
    /// UNBALANCED

    // -1 = left
    //  0 = self with everything connected to it from under
    //  1 = right

    switch (mode)
    {
        case -1:
        {
            if (root->left == NULL)
                return;

            BST* leaf = root->left;

            if (leaf->left == NULL)
            {
                root->left = leaf->right;
            }
            else
            {
                root->left = leaf->left;

                if (leaf->right != NULL)
                {
                    if (leaf->left->right != NULL)
                    {
                        GetSmallestNode(leaf->right)->left = leaf->left->right;
                        leaf->left->right = leaf->right;
                    }
                }
            }

            free(leaf);
            break;
        }

        case 0:
        {
            DeleteTree(root);

            BST* temp_ptr = (BST*)rootptr_address;

            char* p = 0;
            *temp_ptr = *(BST*)&p;

            break;
        }

        case 1:
        {
            if (root->right == NULL)
                return;

            BST* leaf = root->right;

            if (leaf->right == NULL)
            {
                root->right = leaf->left;
            }
            else
            {
                root->right = leaf->right;

                if (leaf->left != NULL)
                {
                    if (leaf->right->left == NULL)
                    {
                        leaf->right->left = leaf->left;
                    }
                    else
                    {
                        GetSmallestNode(leaf->right)->left = leaf->left;
                    }
                }
            }

            free(leaf);
            break;
        }

        default:
            break;
    }
}
