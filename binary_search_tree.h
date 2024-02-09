//
// Created by boydj on 2/8/2024.
//

#ifndef BST_VISUALIZER_BINARY_SEARCH_TREE_H
#define BST_VISUALIZER_BINARY_SEARCH_TREE_H

typedef struct node
{
    int key;
    struct node *left, *right;
} node;

node *new_node(int item);
node *insert(node *new, int key);
node *search(node *root, int key);
node *delete(node *root, int key);

#endif //BST_VISUALIZER_BINARY_SEARCH_TREE_H
