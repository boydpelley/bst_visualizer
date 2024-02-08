//
// Created by boydj on 2/8/2024.
//

#ifndef BST_VISUALIZER_BINARY_SEARCH_TREE_H
#define BST_VISUALIZER_BINARY_SEARCH_TREE_H

typedef struct node
{
    short key;
    struct node *left, *right;
} node;

node *new_node(short item);
node *insert(node *new, short key);
node *search(node *root, short key);

#endif //BST_VISUALIZER_BINARY_SEARCH_TREE_H
