#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "statNode.h"
#include "statTree.h"

t_node make_t_node (void)
{
  t_node tmp = (t_node) malloc(sizeof(struct _tree_node));
  if (tmp == NULL) {
    errno = ENOMEM;
    perror("make_t_node - creazione nodo fallita");
  } else {
    tmp->value = tmp->left = tmp->right = tmp->parent = NULL;
    tmp->key = 0;
  }
  return tmp;
}

void delete_t_node (t_node tmp)
{
  if (tmp == NULL)
    return;
  if (tmp->value != NULL)
    free(tmp->value);
  free(tmp);
}


void delete_node_cascade (t_node t)
{
  if (t == NULL)
    return;
  delete_node_cascade(t->left);
  delete_node_cascade(t->right);
  if (t->value != NULL)
    free(t->value);
  free(t);
}

int node_depth (t_node n)
{
  if (n == NULL)
    return 0;
  int l = node_depth(n->left);
  int r = node_depth(n->right);
  if (l > r)
    return l + 1;
  return r + 1;
}