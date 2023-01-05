#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct BinaryTree
{
    struct BinaryTree *left;
    int n;
    struct BinaryTree *rite;
}
BINARY_TREE;

BINARY_TREE* AddToBinarySearchTree(BINARY_TREE* root, int num)
{
    if (root == NULL)
    {
        root = (BINARY_TREE*) malloc(sizeof(BINARY_TREE));

        root->left = NULL;
        root->n    = num;
        root->rite = NULL;

        return root;
    }
    
    if (num <= root->n)
    {
        root->left = AddToBinarySearchTree(root->left, num);
    }

    if (num >= root->n)
    {
        root->rite = AddToBinarySearchTree(root->rite, num);
    }

    return root;
}

void ListPreorder(BINARY_TREE* root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->n);

    ListPreorder(root->left);
    ListPreorder(root->rite);
}
void ListInorder(BINARY_TREE* root)
{
    if (root == NULL)
    {
        return;
    }

    ListInorder(root->left);

    printf("%d ", root->n);

    ListInorder(root->rite);
}
void ListPostorder(BINARY_TREE* root)
{
    if (root == NULL)
    {
        return;
    }

    ListPostorder(root->left);
    ListPostorder(root->rite);

    printf("%d ", root->n);
}
