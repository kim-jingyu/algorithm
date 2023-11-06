#include "rbtree.h"
#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  p->nil = (node_t*)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;

  p->root=p->nil;
  
  return p;
}

void delete_node(rbtree *t, node_t *node) {
  if (node->left != t->nil){
    delete_node(t, node->left);
  } else if (node->right != t->nil) {
    delete_node(t, node->right);
  }
  
  free(node);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  node_t *node = t->root;
  if (node != t->nil) {
    delete_node(t, node);
  }
}

void right_rotate(rbtree *t, node_t *y) {
  node_t *x = y->left; // 현재 y가 부모, x가 자식
  node_t *grand_parent = y->parent;

  // x 자식 베타를 y 자식으로 넣어주기
  y->left = x->right; 
  if (x->right != t->nil) {
    x->right->parent = y;
  }

  x->parent = grand_parent;
  if (grand_parent == t->nil) {
    t->root = x;
  } else if (y == grand_parent->left) {
    grand_parent->left = x;
  } else {
    grand_parent->right = y;
  }

  x->right = y;
  y->parent = x;
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right; // 현재 x가 부모, y가 자식
  node_t *grand_parent = x->parent;

  // y 자식 베타를 x 자식으로 넣어주기
  x->right = y->left; 
  if (y->left != t->nil) {
    y->left->parent = x;
  }

  y->parent = grand_parent;
  if (grand_parent == t->nil) {
    t->root = y;
  } else if (x == grand_parent->left) {
    grand_parent->left = y;
  } else {
    grand_parent->right = y;
  }

  y->left = x;
  x->parent = y;
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
