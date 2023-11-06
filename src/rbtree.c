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

void insert_fixup(rbtree *t, node_t *node) {
  node_t *parent = node->parent;
  node_t *grand_parent = parent->parent;
  node_t *uncle;

  if (node == t->root) {
    node->color = RBTREE_BLACK;
    return;
  }

  if (parent->color == RBTREE_BLACK) {
    return;
  }

  while (parent->color == RBTREE_RED)
  {
    parent = node->parent;
    grand_parent = parent->parent;
    if (parent == grand_parent->left) { // 부모가 할아버지의 왼쪽에 위치할때
      uncle = grand_parent->right; // 삼촌은 오른쪽에 위치
      if (uncle->color == RBTREE_RED) { // CASE1 : 부모, 삼촌 모두 RED
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grand_parent->color = RBTREE_RED;
        node = grand_parent;
      } else {
        if (node == parent->right) { // CASE2 : 꺾여있을 때
          node = parent;
          left_rotate(t, node);
        }
        // CASE2 : 펴져있을 때
        parent->color = RBTREE_BLACK;
        grand_parent->color = RBTREE_RED;
        right_rotate(t, grand_parent);
      }
    } else { // 부모가 할아버지의 오른쪽에 위치할 때
      uncle = grand_parent->left;
      if (uncle->color == RBTREE_RED) { // CASE1
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grand_parent->color = RBTREE_RED;
        node = grand_parent;
      } else {
        if (node == parent->left) { // CASE2 : 꺽여있을 때
          node = parent;
          right_rotate(t, node);
        }
        // CASE2 : 펴져있을 때
        parent->color = RBTREE_BLACK;
        grand_parent->color = RBTREE_RED;
        left_rotate(t, grand_parent);
      }
    }
  }
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *new_node = (node_t*)calloc(1, sizeof(node_t));
  new_node->left = new_node->right=t->nil;
  new_node->key = key;
  new_node->color = RBTREE_RED;
  
  // 새 노드 삽입 위치 탐색
  node_t *location_of_now = t->root;
  node_t *location_of_update = t->nil;
  while (location_of_now != t->nil) {
    location_of_update = location_of_now;
    if (key < location_of_now->key) { // key를 왼쪽으로 삽입해야 하는 경우
      location_of_now = location_of_now->left;
    } else { // key를 오른쪽으로 삽입해야 하는 경우
      location_of_now = location_of_now->right;
    }
  }
  
  new_node->parent = location_of_update;

  if (location_of_update == t->nil) {
    t->root = new_node;
  }

  insert_fixup(t, new_node);
  t->root->color = RBTREE_BLACK;
  return new_node;
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
