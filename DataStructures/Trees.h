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

#define ALLOCATE_BINARYTREE       (BINARY_TREE*)        malloc(sizeof(BINARY_TREE))
#define ALLOCATE_BINARYSEARCHTREE (BINARY_SEARCH_TREE*) malloc(sizeof(BINARY_SEARCH_TREE))

BINARY_SEARCH_TREE* AddToBinarySearchTree(BINARY_SEARCH_TREE* root, int num)
{
    if (root == NULL)
    {
        root = ALLOCATE_BINARYSEARCHTREE;

        root->left = NULL;
        root->n    = num;
        root->right = NULL;

        return root;
    }

    if (num < root->n)
    {
        root->left = AddToBinarySearchTree(root->left, num);
    }

    if (num > root->n)
    {
        root->right = AddToBinarySearchTree(root->right, num);
    }

    return root;
}

BINARY_SEARCH_TREE* FindNumberAddress(BINARY_SEARCH_TREE* root, int num)
{
    if (root == NULL)
        return NULL;

    if (num < root->n)
        return FindNumberAddress(root->left, num);

    if (num > root->n)
        return FindNumberAddress(root->right, num);

    return root;
}

BINARY_SEARCH_TREE* GetSmallest(BINARY_SEARCH_TREE* root)
{
    if (root->left == NULL)
        return root;

    return GetSmallest(root->left);
}

BINARY_SEARCH_TREE* GetGreatest(BINARY_SEARCH_TREE* root)
{
    if (root->right == NULL)
        return root;

    return GetGreatest(root->right);
}


void ListTreePreorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        printf("%d ", root->n);
        ListTreePreorder(root->left);
        ListTreePreorder(root->right);
    }
}

void ListTreeInorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        ListTreeInorder(root->left);
        printf("%d ", root->n);
        ListTreeInorder(root->right);
    }
}

void ListTreePostorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        ListTreePostorder(root->left);
        ListTreePostorder(root->right);
        printf("%d ", root->n);
    }
}


void ListLastLeaves(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            printf("%d ", root->n);
            return;
        }

        ListLastLeaves(root->left);
        ListLastLeaves(root->right);
    }
}

void ListLastLeavesReverse(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            printf("%d ", root->n);
            return;
        }

        ListLastLeavesReverse(root->right);
        ListLastLeavesReverse(root->left);
    }
}


int BinaryTreeSum(BINARY_TREE* root)
{
    if (root == NULL)
        return 0;

    return root->n + BinaryTreeSum(root->left) + BinaryTreeSum(root->right);
}

int BinaryTreeSum(BINARY_SEARCH_TREE* root)
{
    if (root == NULL)
        return 0;

    return root->n + BinaryTreeSum(root->left) + BinaryTreeSum(root->right);
}
