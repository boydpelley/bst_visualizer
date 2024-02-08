//
// Created by boydj on 2/8/2024.
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
    if (new == NULL) return new_node(key);

    if (key < new->key) new->left = insert(new->left, key);
    else if (key > new->key) new->right = insert(new->right, key);

    return new;
}

node * search(node * root, short key)
{
    if (root == NULL || root->key == key) return root;

    if (root->key < key) search(root->left, key);
    else if (root->key > key) search(root->right, key);

    return NULL;
}


