#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * map = (TreeMap *)malloc(sizeof(TreeMap));
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode *nuevo = createTreeNode(key, value);
    if (nuevo == NULL) return;

    if (tree->root == NULL) {
        // Tree is empty, make the new node the root
        tree->root = nuevo;
        tree->current = nuevo;
        nuevo->parent = NULL; // Root has no parent
        return;
    }

    TreeNode *actual = tree->root;
    TreeNode *parent = NULL;

    // Traverse the tree to find the correct position
    while (actual != NULL) {
        parent = actual;
        if (tree->lower_than(key, actual->pair->key)) {
            actual = actual->left;
        } else if (tree->lower_than(actual->pair->key, key)) {
            actual = actual->right;
        } else {
            // Key already exists, do not insert
            free(nuevo->pair);
            free(nuevo);
            return;
        }
    }

    // Insert the new node as a child of the parent
    nuevo->parent = parent;
    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = nuevo;
    } else {
        parent->right = nuevo;
    }

    // Update tree->current to the newly inserted node
    tree->current = nuevo;
}

TreeNode * minimum(TreeNode * x){
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
