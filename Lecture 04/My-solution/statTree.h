#ifndef _STATTREE_H
#define _STATTREE_H
#include "statNode.h"

typedef struct _tree_node *t_node;

struct _bst {
  t_node root;
};

typedef struct _bst *bst;

bst make_bst (void);

void delete_bst (bst t);

void bst_insert (bst t, t_node n);

int bst_depth (bst t);

void s_test (int n);

void r_test (int n);

#endif