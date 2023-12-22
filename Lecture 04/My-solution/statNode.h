#ifndef _STATNODE_H
#define _STATNODE_H
#include "statTree.h"

struct _tree_node {
  int key;
  void *value;
  struct _tree_node *left;
  struct _tree_node *right;
  struct _tree_node *parent;
};

t_node make_t_node (void);

void delete_t_node (t_node tmp);

void delete_node_cascade (t_node t);

int node_depth (t_node n);

#endif