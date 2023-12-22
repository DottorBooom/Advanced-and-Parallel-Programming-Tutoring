#include "merge.h"

void merge(int * v1, int n1, int * v2, int n2, int * results)
{
  for(int i = 0, j = 0; i < n1 || j < n2;){
    if((v1[i] < v2[j] && i != n1) || j == n2){
      results[i+j] = v1[i];
      i++;
    }else{
      results[i+j] = v2[j];
      j++;
    }
  }
}

void merge_branchless(int * v1, int n1, int * v2, int n2, int * results)
{

  int i,j;
  for(i = 0, j = 0; i < n1 && j < n2;){
    results[i+j] = (v1[i] < v2[j]) * v1[i];
    i += (v1[i] < v2[j]);
    results[i+j] += (v2[j] <= v1[i]) * v2[j];
    j += (v2[j] <= v1[i]);
  }

  while (i < j)
  {
    results[i+j] = v1[i];
    i++;
  }
  
    while (j < i)
  {
    results[i+j] = v2[j];
    j++;
  }

}