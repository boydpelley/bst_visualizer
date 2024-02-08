//
// Created by boydj on 2/8/2024.
// Work partly cited from geeksforgeeks.org
//

#include <malloc.h>
#include "binary_search_tree.h"

node * new_node(short item)
{
    struct node * temp = (struct node *)malloc(sizeof(struct node *));
    temp->key = item;
    temp->left = temp->right = NULL;

    return temp;
}

node * insert(node * new, short key)
{
    // Base case
    if (new == NULL) return new_node(key);

    // Recursively search for the right spot to add the new node
    if (key < new->key) new->left = insert(new->left, key);
    else if (key > new->key) new->right = insert(new->right, key);

    return new;
}

node * search(node * root, short key)
{
    // Base cases
    if (root == NULL || root->key == key) return root;

    // Recursively search for the applicable nodes
    if (root->key < key) search(root->left, key);
    else if (root->key > key) search(root->right, key);

    return NULL;
}

node * delete(node * root, short key)
{
    // Base case
    if (root == NULL) return root;

    // Recursively search for the node to be deleted
    if (root->key < key)
    {
        delete(root->left, key);
        return root;
    }
    else if (root->key > key)
    {
        delete(root->right, key);
        return root;
    }

    // Covering the cases where only one of the children are empty
    if (root->left == NULL)
    {
        node * temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL)
    {
        node * temp = root->left;
        free(root);
        return temp;
    }
    // Otherwise there is two children
    else
    {
        node * successor_parent = root;

        node * successor = root->right;
        // Search for successor
        while (successor->left != NULL)
        {
            successor_parent = successor;
            successor = successor->left;
        }

        // Delete the successor
        if (successor_parent != root)
        {
            successor_parent->left = successor->right;
        }
        else
        {
            successor_parent->right = successor->right;
        }

        root->key = successor->key;

        free(successor);

        return root;
    }
}


