#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct BinaryTree
{
    struct BinaryTree* left;
    int n;
    struct BinaryTree* rite;
}
BINARY_TREE;

typedef struct BinaryTree
{
    struct BinaryTree *left;
    int n;
    struct BinaryTree *rite;
}
BINARY_SEARCH_TREE;

BINARY_SEARCH_TREE* AddToBinarySearchTree(BINARY_SEARCH_TREE* root, int num)
{
    if (root == NULL)
    {
        root = (BINARY_SEARCH_TREE*) malloc(sizeof(BINARY_SEARCH_TREE));

        root->left = NULL;
        root->n    = num;
        root->rite = NULL;

        return root;
    }

    if (num < root->n)
    {
        root->left = AddToBinarySearchTree(root->left, num);
    }

    if (num > root->n)
    {
        root->rite = AddToBinarySearchTree(root->rite, num);
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
        return FindNumberAddress(root->rite, num);

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
    if (root->rite == NULL)
        return root;

    return GetGreatest(root->rite);
}


void ListTreePreorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        printf("%d ", root->n);
        ListTreePreorder(root->left);
        ListTreePreorder(root->rite);
    }
}

void ListTreeInorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        ListTreeInorder(root->left);
        printf("%d ", root->n);
        ListTreeInorder(root->rite);
    }
}

void ListTreePostorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        ListTreePostorder(root->left);
        ListTreePostorder(root->rite);
        printf("%d ", root->n);
    }
}


void ListLastLeavesPreorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->rite == NULL)
        {
            printf("%d ", root->n);
            return;
        }

        ListLastLeavesPreorder(root->left);
        ListLastLeavesPreorder(root->rite);
    }
}

void ListLastLeavesInorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        ListLastLeavesInorder(root->left);

        if (root->left == NULL && root->rite == NULL)
        {
            printf("%d ", root->n);
            return;
        }

        ListLastLeavesInorder(root->rite);
    }
}

void ListLastLeavesPostorder(BINARY_SEARCH_TREE* root)
{
    if (root != NULL)
    {
        ListLastLeavesPostorder(root->left);
        ListLastLeavesPostorder(root->rite);

        if (root->left == NULL && root->rite == NULL)
        {
            printf("%d ", root->n);
            return;
        }
    }
}


int BinaryTreeSum(BINARY_TREE* root)
{
    if (root == NULL)
        return 0;

    return root->n + BinaryTreeSum(root->left) + BinaryTreeSum(root->rite);
}

int BinaryTreeSum(BINARY_SEARCH_TREE* root)
{
    if (root == NULL)
        return 0;

    return root->n + BinaryTreeSum(root->left) + BinaryTreeSum(root->rite);
}
