#include <iostream>
#include <hash_map>
#include "header.h"
#include "hashmap.h"
using namespace std;

bool is_dup_within_Kth_distant(int arr[], int size, int k)
{
  hash_map <int, int> hmap;

  for(int i=0; i<size; i++)
    {
      hmap.insert(i, arr[i]);
    }

  for(int i=0; i<size; i++)
    {
      cout << "hmap [" << i << "]" << "=" hmap.get(i) << endl;
    }

  return false;
}

int main()
{
  int arr[] = {1, 2, 3, 4, 4};
  int size = sizeof(arr)/sizeof(int);
  printf("\n\t ***** Array ***** \n\n  ");
  print(arr, size);

  printf("\n");
  is_dup_within_Kth_distant();
  return 0;
}

