#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

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

  // x의 오른쪽 서브트리를 y 왼쪽 자식으로 넣어주기
  y->left = x->right; 
  if (x->right != t->nil) {
    x->right->parent = y;
  }

  x->parent = y->parent;
  if (y->parent == t->nil) {
    t->root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  x->right = y;
  y->parent = x;
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right; // 현재 x가 부모, y가 자식

  // y 왼쪽 서브트리를 x 오른쪽 자식으로 넣어주기
  x->right = y->left; 
  if (y->left != t->nil) {
    y->left->parent = x;
  }

  y->parent = x->parent;
  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *node) {
  while (node->parent->color == RBTREE_RED)
  {
    if (node->parent == node->parent->parent->left) { // 부모가 할아버지의 왼쪽에 위치할때
      node_t *uncle = node->parent->parent->right; // 삼촌은 오른쪽에 위치
      if (uncle->color == RBTREE_RED) { // CASE1 : 부모, 삼촌 모두 RED
        node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) { // CASE2 : 꺾여있을 때
          node = node->parent;
          left_rotate(t, node);
        }
        // CASE2 : 펴져있을 때
        node->parent->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        right_rotate(t, node->parent->parent);
      }
    } else { // 부모가 할아버지의 오른쪽에 위치할 때
      node_t *uncle = node->parent->parent->left;
      if (uncle->color == RBTREE_RED) { // CASE1
        node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) { // CASE2 : 꺽여있을 때
          node = node->parent;
          right_rotate(t, node);
        }
        // CASE2 : 펴져있을 때
        node->parent->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        left_rotate(t, node->parent->parent);
      }
    }
  }
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *new_node = (node_t*)calloc(1, sizeof(node_t));
  node_t *y = t->nil;
  node_t *x = t->root;

  while (x != t->nil) {
    y = x;
    if (key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  new_node->parent = y;
  
  if (y == t->nil) {
    t->root = new_node;
  } else if (key < y->key) {
    y->left = new_node;
  } else {
    y->right = new_node;
  }

  new_node->key = key;
  
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;

  rbtree_insert_fixup(t, new_node);
  t->root->color = RBTREE_BLACK;

  return new_node;
}

// RB tree 내에 해당하는 key가 있는지 탐색하여 해당 node pointer를 반환한다. 물론 해당하는 node가 없으면 NULL을 반환한다.
node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  if (t->root == t->nil) {
    return NULL;
  }

  node_t *now = t->root;
  while (now != t->nil) {
    if (key < now->key) {
      now = now->left;
    } else if (key > now->key) {
      now = now->right;
    } else {
      return now;
    }
  }
  return NULL;
}

// RB tree 중 최소값을 가진 node pointer를 반환한다.
node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *now = t->root;

  while (now->left != t->nil) {
    now = now->left;
  }

  return now;
}

// RB tree 중 최대값을 가진 node pointer를 반환한다.
node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *now = t->root;

  while (now->right != t->nil) {
    now = now->right;
  }

  return now;
}

// 삭제하고자 하는 노드를 대체할 노드를 찾아, 삭제하고자 하는 노드에 대입할 동작을 수행하는 함수. (이식)
// u 자리에 v 노드를 심는 의미이고, u의 부모가 가리키는 것이 v이다.
void transplant(rbtree *t, node_t *u, node_t *v) {
  node_t *parent = u->parent;

  if (parent == t->nil) { // u가 루트 노드일 때
    t->root = v;
  } else if (u == parent->left) {
    parent->left = v;
  } else {
    parent->right = v;
  }

  v->parent = parent;
}

node_t *find_successor(rbtree *t, node_t *node) {
  while (node->left != t->nil) {
    node = node->left;
  }
  return node;
}

void erase_fixup(rbtree *t, node_t *x) {
  // x의 형제를 가리키기 위해서 포인터 w 사용
  node_t *w;

  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) { // x가 왼쪽에 있으면
      w = x->parent->right;

      // case1
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      // case2
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      } else {

        // case3
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }

        // case4
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    } else { // x가 오른쪽에 있으면
      w = x->parent->left;

      // case1
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }

      // case2
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      } else {
        // case3
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }

        // case4
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *y = p; // y는 트리에서 삭제된 노드 또는 트리에서 이동한 노드를 가리킨다.
  color_t y_original_color = y->color;
  node_t *x; // y의 오른쪽 자식

  if (p->left == t->nil) { // p의 자식이 오른쪽만 있을때
    x = p->right;
    transplant(t, p, p->right);
  } else if (p->right == t->nil) { // p의 자식이 왼쪽만 있을때
    x = p->left;
    transplant(t, p, p->left);
  } else {
    y = find_successor(t, p->right);
    y_original_color = y->color; // 삭제될 successor의 색 저장
    x = y->right; // successor의 오른쪽 저장

    if (y->parent == p) {
      x->parent = y;
    } else {
      transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }

    transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }

  if (y_original_color == RBTREE_BLACK) {
    erase_fixup(t, x);
  }

  free(p);

  return 0;
}

void inorder_traverse(rbtree *t, node_t *now, int *idx, key_t *arr, size_t n) {
  if(now == t->nil) {
    return;
  }

  inorder_traverse(t, now->left, idx, arr, n);
  if ((*idx) < n) {
    arr[(*idx)++] = now->key;
  } else {
    return;
  }
  inorder_traverse(t, now->right, idx, arr, n);
}

// 트리를 배열로 변환 -> inorder traversing으로 구현!!! 
// traversing 순서: node, node->left, node->right
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  node_t *current = t->root;
  if (current == t->nil) {
    return 0;
  }

  int idx = 0;
  inorder_traverse(t, current, &idx, arr, n);

  return 0;
}
