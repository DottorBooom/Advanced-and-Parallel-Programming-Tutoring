#include <stdlib.h>
#include <stdio.h>

#include "unrolled_linked_list.h"


// CREAZIONE //
unrolled_linked_list ulst_make(void)
{
  // Creo una istanza della unrolled list
  unrolled_linked_list lst = (unrolled_linked_list) malloc(sizeof(struct _unrolled_linked_list));
  lst->head = NULL;
  return lst;
}


// CANCELLAZIONE
// Cancella tutta la unrolled list (itero su blocchi)
void ulst_delete(unrolled_linked_list lst)
{
  if (lst == NULL) { // se la lista è già NULL -> ok
    return;
  }

  unode current = lst->head; // Prendo il primo nodo della lista
  while (current != NULL) {  // Finché non alla fine della lista 
    unode prev = current;    // Salvo questo nodo
    current = current->next; // Prendo il successivo
    free(prev);              // Ora posso cancellarlo
  }
  free(lst); // alla fine del ciclo, posso liberare la memoria
}


// AGGIUNGI CHIAVE
// Aggiungi il valore nel primo spazio libero tra i blocchi (in ordine)
void ulst_add(unrolled_linked_list lst, int key)
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
  unode current = lst->head; // salvo la testa della coda

  if (current != NULL) // se la head è un nodo non vuoto
  {
  for (int i = 0; i < UNROLLED_SIZE; i++) // per ogni elemento dell'array della head
  {
    if (current->keys[i] == NULL) // se ho trovato un posto vuoto
    {
      current->keys[i] = key; // metto il valore
      current->valid[i] = true; // sarà valido
      return;
    } // fine if
  }
  } // altrimenti è il primo caso e va trattato come se non avesse primo nodo.

  // Se siamo qui, significa che non ho trovato spazio vuoto: devo creare un nuovo nodo
  // devo creare un nuovo nodo
  unode new = (unode) malloc(sizeof(struct _unrolled_node));

  // Aggiungo i valori
  // ARRAY del nodo
  new->keys[0] = key; //vettore di valori
  new->valid[0] = true; //vettore booleani

  new->next = lst->head;
  lst->head = new;

}




// RICERCA
// Ricerca scorrendo tra blocchi > array
bool ulst_search(unrolled_linked_list lst, int key)
{
  unode current = lst->head; // prendo la head della lista

  while (current != NULL) // fino alla fine
  {
    for (int i=0; i<UNROLLED_SIZE; i++) // per ogni elemento dell'array del nodo
    {
      if (current->keys[i] == key && current->valid[i]) // se c'è la chiave e il corrispondente flag è a true
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


void ulst_print(unrolled_linked_list lst)
{
  if (lst == NULL) {
    printf("NIL");
    return;
  }
  printf("(");
  unode current = lst->head;
  while (current != NULL) {
    printf("[");
    for (int i = 0; i < UNROLLED_SIZE; i++) {
      if (current->valid[i]) {
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
