#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "statNode.h"
#include "statTree.h"

bst make_bst (void)
{
  bst tmp = (bst) malloc(sizeof(struct _bst));
  if (tmp == NULL) {
    errno = ENOMEM;
    perror("make_bst - creazione albero fallita.");
  } else {
    tmp->root = NULL;
  }
  return tmp;
}

void delete_bst (bst t)
{
  if (t != NULL)
    delete_node_cascade(t->root);
  free(t);
}

void bst_insert (bst t, t_node n)
{
  if (t != NULL && n != NULL) {
    if (t->root == NULL)
      t->root = n;
    else {
      t_node cfr = t->root;
      while (1) {
	if (n->key > cfr->key) {
	  if (cfr->right == NULL) {
	    cfr->right = n;
	    n->parent = cfr;
	    break;
	  } else
	    cfr = cfr->right;
	} else {
	  if (cfr->left == NULL) {
	    cfr->left = n;
	    n->parent = cfr;
	    break;
	  } else
	    cfr = cfr->left;
	}
      }
    }
  }
}

int bst_depth (bst t) {
  if (t != NULL)
    return node_depth(t->root);
  return 0;
}