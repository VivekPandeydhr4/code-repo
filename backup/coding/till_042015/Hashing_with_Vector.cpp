#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int isDuplicates_in_K_Distance(int *A, int n, int k);
/*************************************************************/
                   /* Hashing API*/
#define SIZE 7
#define KEY(n) n%SIZE

// For insert(n) use   "  Hash[KEY(n)].push_back(n) " at the appropriate vector in the table

int search(vector<int>& v, int n)
{
  vector<int>::iterator it;
  for(it=v.begin();it!=v.end();it++) if(*it==n) return 1;    
  return 0;   
}
void Delete(vector<int>& v, int n)
{
  vector<int>::iterator it;
  for(it=v.begin();it!=v.end();it++)
    {
      if(*it==n) {v.erase(it); break;}
    }
}

/********************************************************************/

                      /*Hashing use example*/
int main()
{
  int A[]={1,1,3,5,9,6,7,2,8.1};
  cout<<isDuplicates_in_K_Distance(A,10,4)<<endl;
  return 0;
}


int isDuplicates_in_K_Distance(int *A, int n, int k)
{
  int i;
  vector<int> Hash[SIZE];

  for(i=0;i<k;i++)
    {
      if(search(Hash[KEY(A[i])],A[i])) return 1;
      Hash[KEY(A[i])].push_back(A[i]);    //insert(A(i)) example
    }

  for(;i<n;i++)
    {
      Delete(Hash[A[i-k]%SIZE],A[i-k]);
      if(search(Hash[KEY(A[i])],A[i])) return 1;
      Hash[KEY(A[i])].push_back(A[i]);   //insert(A(i)) example
    }

  return 0;
}
