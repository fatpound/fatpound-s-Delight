#pragma once

#include <iostream>

template <typename T>
class BinarySearchTree
{
private:
    class BST_node
    {
    private:


    protected:


    public:
        BST_node* left = nullptr;
        BST_node* right = nullptr;
        T item;

        BST_node();
        ~BST_node();
        BST_node(T new_item);
    };


    BST_node* root = nullptr;
    int item_count = 0;

    BST_node* add_private(BST_node* node, T new_item);

    void list_preorder_private(BST_node* node);
    void list_inorder_private(BST_node* node);
    void list_postorder_private(BST_node* node);
    void list_leaves_private(BST_node* node);

    void list_preorder_reverse_private(BST_node* node);
    void list_inorder_reverse_private(BST_node* node);
    void list_postorder_reverse_private(BST_node* node);
    void list_leaves_reverse_private(BST_node* node);


protected:


public:
    BinarySearchTree();
    ~BinarySearchTree();

    void add(T new_item);

    void list_preorder();
    void list_inorder();
    void list_postorder();
    void list_leaves();

    void list_preorder_reverse();
    void list_inorder_reverse();
    void list_postorder_reverse();
    void list_leaves_reverse();
};

template <typename T> BinarySearchTree<T>::BST_node::BST_node()
{

}
template <typename T> BinarySearchTree<T>::BST_node::~BST_node()
{

}
template <typename T> BinarySearchTree<T>::BST_node::BST_node(T new_item)
{
    this->item = new_item;
}

template <typename T> typename BinarySearchTree<T>::BST_node* BinarySearchTree<T>::add_private(BST_node* node, T new_item)
{
    if (node == nullptr)
    {
        node = new BST_node(new_item);
        return node;
    }

    if (new_item < node->item)
    {
        node->left = this->add_private(node->left, new_item);
    }

    if (new_item > node->item)
    {
        node->right = this->add_private(node->right, new_item);
    }
}

template <typename T> BinarySearchTree<T>::BinarySearchTree()
{

}
template <typename T> BinarySearchTree<T>::~BinarySearchTree()
{

}

template <typename T> void BinarySearchTree<T>::list_preorder_private(BST_node* node)
{
    if (node == nullptr)
        return;

    std::cout << node->item << ' ';
    this->list_preorder_private(node->left);
    this->list_preorder_private(node->right);
}
template <typename T> void BinarySearchTree<T>::list_inorder_private(BST_node* node)
{
    if (node == nullptr)
        return;

    this->list_preorder_private(node->left);
    std::cout << node->item << ' ';
    this->list_preorder_private(node->right);
}
template <typename T> void BinarySearchTree<T>::list_postorder_private(BST_node* node)
{
    if (node == nullptr)
        return;

    this->list_preorder_private(node->left);
    this->list_preorder_private(node->right);
    std::cout << node->item << ' ';
}
template <typename T> void BinarySearchTree<T>::list_leaves_private(BST_node* node)
{
    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr)
    {
        std::cout << node->item << ' ';
        return;
    }

    list_leaves_private(root->left);
    list_leaves_private(root->right);
}

template <typename T> void BinarySearchTree<T>::list_preorder_reverse_private(BST_node* node)
{
    if (node == nullptr)
        return;

    std::cout << node->item << ' ';
    this->list_preorder_private(node->right);
    this->list_preorder_private(node->left);
}
template <typename T> void BinarySearchTree<T>::list_inorder_reverse_private(BST_node* node)
{
    if (node == nullptr)
        return;

    this->list_preorder_private(node->right);
    std::cout << node->item << ' ';
    this->list_preorder_private(node->left);
}
template <typename T> void BinarySearchTree<T>::list_postorder_reverse_private(BST_node* node)
{
    if (node == nullptr)
        return;

    this->list_preorder_private(node->right);
    this->list_preorder_private(node->left);
    std::cout << node->item << ' ';
}
template <typename T> void BinarySearchTree<T>::list_leaves_reverse_private(BST_node* node)
{
    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr)
    {
        std::cout << node->item << ' ';
        return;
    }

    list_leaves_private(root->right);
    list_leaves_private(root->left);
}

template <typename T> void BinarySearchTree<T>::add(T new_item)
{
    this->add_private(this->root, new_item);
    this->item_count++;
}

template <typename T> void BinarySearchTree<T>::list_preorder()
{
    this->list_preorder_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_inorder()
{
    this->list_inorder_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_postorder()
{
    this->list_postorder_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_leaves()
{
    this->list_leaves_private(this->root);
}

template <typename T> void BinarySearchTree<T>::list_preorder_reverse()
{
    this->list_preorder_reverse_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_inorder_reverse()
{
    this->list_inorder_reverse_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_postorder_reverse()
{
    this->list_postorder_reverse_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_leaves_reverse()
{
    this->list_leaves_reverse_private(this->root);
}