#ifndef _UNROLLED_LINKED_LIST_BIT_H
#define _UNROLLED_LINKED_LIST_BIT_H

#include <stdbool.h>
#include <stdint.h>

#define UNROLLED_SIZE 16

struct _unrolled_node_bit {
  uint32_t keys[UNROLLED_SIZE];
  struct _unrolled_node_bit * next;
};

typedef struct _unrolled_node_bit * unode_bit;

struct _unrolled_linked_list_bit {
  unode_bit head;
};

typedef struct _unrolled_linked_list_bit * unrolled_linked_list_bit;

unrolled_linked_list_bit ulst_make_bit(void);

/* Elimina la lista e tutto il suo contenuto */
void ulst_delete_bit(unrolled_linked_list_bit lst);

/* Aggiunge alla testa della lista un nuovo nodo con la chiave indicata */
void ulst_add_bit(unrolled_linked_list_bit lst, uint32_t key);

/* Ritorna vero se e solo se il valore cercato è presente nella lista */
bool ulst_search_bit(unrolled_linked_list_bit lst, uint32_t key);

/* Stampa il contenuto della lista */
void ulst_print_bit(unrolled_linked_list_bit lst);

#endif