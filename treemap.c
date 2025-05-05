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
    TreeNode *actual = tree->root;
    //revisa si esta vacio
    if (actual == NULL){
        tree->root = nuevo;
        tree->current = nuevo;
        nuevo->parent = NULL;
        return;
    }

    // recorrer el arbol binario
    while (actual != NULL){
        if (is_equal(tree, nuevo->pair->key, actual->pair->key)) return;
        else if (tree->lower_than(nuevo->pair->key, actual->pair->key) == 1) {
            if (actual->left == NULL){
                actual->left = nuevo;
                nuevo->parent = actual;
                break;
            }
            actual = actual->left;
        } 
        else{
            if (actual->right == NULL){
                actual->right = nuevo;
                nuevo->parent = actual;
                break;
            }
            actual = actual->right;
        }
    }
    tree->current = nuevo;
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    TreeNode *actual = x;
    while (actual->left != NULL) actual = actual->left;
    return actual;
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
    TreeNode *actual = tree->root;
    while (actual != NULL){
        if (is_equal(tree, key, actual->pair->key)){
            tree->current = actual;
            return actual->pair;
        }
        else if (tree->lower_than(key, actual->pair->key) == 1) actual = actual->left;
        else actual = actual->right;
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    Pair *MayorQueActual;
    TreeNode *actual = tree->root;
    while (actual != NULL){
        if (is_equal(tree, key, actual->pair->key)){
            tree->current = actual;
            return actual->pair;
        }
        else if (tree->lower_than(key, actual->pair->key) == 1){
            actual = actual->left;
            Pair MayorQueActual;
        }
        else actual = actual->right;
    }
    return MayorQueActual;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
