#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"
#include "unrolled_linked_list.h"
#include "unrolled_linked_list_bit.h"

#define TEST_LIST_SIZE 10000000

void test_linked_list(void)
{
  linked_list lst = lst_make();
  for (int i = 0; i < 20; i++) {
    lst_add(lst, rand()%100);
    lst_print(lst);
    printf("\n");
  }
  lst_delete(lst);
}

void test_unrolled_linked_list(void)
{
  unrolled_linked_list lst = ulst_make();
  for (int i = 0; i < 20; i++) {
    ulst_add(lst, rand()%100);
    ulst_print(lst);
    printf("\n");
  }
  ulst_delete(lst);
}

void test_unrolled_linked_list_bit(void)
{
  unrolled_linked_list_bit lst = ulst_make_bit();
  for (int i = 0; i < 20; i++) {
    ulst_add_bit(lst, rand()%100);
    ulst_print_bit(lst);
    printf("\n");
  }
  ulst_delete_bit(lst);
}


void perf_linked_list(int size, int repetitions)
{
  linked_list lst = lst_make();
  for (int i = 0; i < size; i++) {
    lst_add(lst, rand());
  }
  clock_t start = clock();
  for (int i = 0; i < repetitions; i++) {
    lst_search(lst, rand());
  }
  clock_t end = clock();
  float ms = (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("Searching in a linked list of %d elements %d times: %f ms\n", size, repetitions, ms);
  lst_delete(lst);
}


void perf_unrolled_linked_list(int size, int repetitions)
{
  unrolled_linked_list lst = ulst_make();
  for (int i = 0; i < size; i++) {
    ulst_add(lst, rand());
  }
  clock_t start = clock();
  for (int i = 0; i < repetitions; i++) {
    ulst_search(lst, rand());
  }
  clock_t end = clock();
  float ms = (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("Searching in an unrolled linked list of %d elements %d times: %f ms\n", size, repetitions, ms);
  ulst_delete(lst);
}

void perf_unrolled_linked_list_bit(int size, int repetitions)
{
  unrolled_linked_list_bit lst = ulst_make_bit();
  for (int i = 0; i < size; i++) {
    ulst_add_bit(lst, rand());
  }
  clock_t start = clock();
  for (int i = 0; i < repetitions; i++) {
    ulst_search_bit(lst, rand());
  }
  clock_t end = clock();
  float ms = (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("Searching in an unrolled bit linked list of %d elements %d times: %f ms\n", size, repetitions, ms);
  ulst_delete_bit(lst);
}


int main(int argc, char * argv[])
{
  srand(time(NULL));
  test_linked_list();
  test_unrolled_linked_list();
  test_unrolled_linked_list_bit();
  perf_linked_list(TEST_LIST_SIZE, 10);
  perf_unrolled_linked_list(TEST_LIST_SIZE, 10);
  perf_unrolled_linked_list_bit(TEST_LIST_SIZE, 10);
  return 0;
}
