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

BINARY_SEARCH_TREE* FindNode(BINARY_SEARCH_TREE* root, int num)
{
    if (root == NULL)
        return NULL;

    if (num < root->n)
        return FindNode(root->left, num);

    if (num > root->n)
        return FindNode(root->right, num);

    return root;
}

BINARY_SEARCH_TREE* GetSmallestNode(BINARY_SEARCH_TREE* root)
{
    if (root->left == NULL)
        return root;

    return GetSmallestNode(root->left);
}

BINARY_SEARCH_TREE* GetGreatestNode(BINARY_SEARCH_TREE* root)
{
    if (root->right == NULL)
        return root;

    return GetGreatestNode(root->right);
}


void ListTreePreorder(BINARY_SEARCH_TREE* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->n);
    ListTreePreorder(root->left);
    ListTreePreorder(root->right);
}

void ListTreeInorder(BINARY_SEARCH_TREE* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->n);
    ListTreeInorder(root->left);
    ListTreeInorder(root->right);
}

void ListTreePostorder(BINARY_SEARCH_TREE* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->n);
    ListTreePostorder(root->left);
    ListTreePostorder(root->right);
}


void ListLeaves(BINARY_SEARCH_TREE* root)
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

void ListLeavesReverse(BINARY_SEARCH_TREE* root)
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


void DeleteTree(BINARY_SEARCH_TREE* root)
{
    if (root == NULL)
        return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    free(root);
}

void DeleteNode(BINARY_SEARCH_TREE* root, BINARY_SEARCH_TREE* leaf)
{
    DeleteTree(leaf);
    
    root->left == leaf ? root->left = NULL : root->right = NULL;
}
