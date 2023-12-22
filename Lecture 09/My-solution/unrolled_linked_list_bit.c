#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "unrolled_linked_list_bit.h"


// CREAZIONE //
unrolled_linked_list_bit ulst_make_bit(void)
{
  // Creo una istanza della unrolled list
  unrolled_linked_list_bit lst = (unrolled_linked_list_bit) malloc(sizeof(struct _unrolled_linked_list_bit));
  lst->head = NULL;
  return lst;
}


// CANCELLAZIONE
// Cancella tutta la unrolled list (itero su blocchi)
void ulst_delete_bit(unrolled_linked_list_bit lst)
{
  if (lst == NULL) { // se la lista è già NULL -> ok
    return;
  }

  unode_bit current = lst->head; // Prendo il primo nodo della lista
  while (current != NULL) {  // Finché non alla fine della lista 
    unode_bit prev = current;    // Salvo questo nodo
    current = current->next; // Prendo il successivo
    free(prev);              // Ora posso cancellarlo
  }
  free(lst); // alla fine del ciclo, posso liberare la memoria
}


// AGGIUNGI CHIAVE
// Aggiungi il valore nel primo spazio libero tra i blocchi (in ordine)
void ulst_add_bit(unrolled_linked_list_bit lst, uint32_t key)
{
  // Dovremo distinguere tra due casi, ricordando che stiamo considerando che i nodi più vecchi siano tutti pieni
  // * Se c'è uno spazio vuoto nell'array del nodo in testa
  //   - Devo ciclare su tale array andando in cerca dello spazio vuoto
  // * Se NON c'è uno spazio vuoto nell'array del nodo in testa
  //   - Dovremo creare un nuovo nodo head

  if (lst == NULL) {
    return;
  } // caso NULL

  // Controllo spazio in HEAD
  unode_bit current = lst->head; // salvo la testa della coda

  if (current != NULL) // se la head è un nodo non vuoto
  {
  for (int i = 0; i < UNROLLED_SIZE; i++) // per ogni elemento dell'array della head
  {
    uint32_t number = current -> keys[i] >> 1;

    if (number == NULL) // se ho trovato un posto vuoto
    {
      current->keys[i] = (key << 1) | 1; // metto il valore
      return;
    } // fine if
  }
  } // altrimenti è il primo caso e va trattato come se non avesse primo nodo.

  // Se siamo qui, significa che non ho trovato spazio vuoto: devo creare un nuovo nodo
  // devo creare un nuovo nodo
  unode_bit new = (unode_bit) malloc(sizeof(struct _unrolled_node_bit));

  // Aggiungo i valori
  // ARRAY del nodo
  new->keys[0] = (key << 1) | 1; //vettore di valori

  new->next = lst->head;
  lst->head = new;

}




// RICERCA
// Ricerca scorrendo tra blocchi > array
bool ulst_search_bit(unrolled_linked_list_bit lst, uint32_t key)
{
  unode_bit current = lst->head; // prendo la head della lista

  while (current != NULL) // fino alla fine
  {
    for (int i=0; i<UNROLLED_SIZE; i++) // per ogni elemento dell'array del nodo
    {
      if (current->keys[i] == key && current->keys[i]&1) // se c'è la chiave e il corrispondente flag è a true
      {
        return 1; // abbiamo trovato il valore
      }
    }

    // Se non lo troviamo usciamo dal for e cambiamo nodo.
    current = current->next;
  }

  // Se non è presente, esco dal while e ritorno 0.
  return 0;
}


void ulst_print_bit(unrolled_linked_list_bit lst)
{
  if (lst == NULL) {
    printf("NIL");
    return;
  }
  printf("(");
  unode_bit current = lst->head;
  while (current != NULL) {
    printf("[");
    for (int i = 0; i < UNROLLED_SIZE; i++) {
      // ... GESTIONE ... //
      bool valid = current->keys[i] & 1;
      // ...................... //
      if (valid) {
	printf("%d", current->keys[i]);
      } else {
	printf(".");
      }
      if (i < UNROLLED_SIZE - 1) {
	printf(" ");
      }
    }
    printf("]");
    if (current->next != NULL) {
      printf(" ");
    }
    current = current->next;
  }
  printf(")");
}
