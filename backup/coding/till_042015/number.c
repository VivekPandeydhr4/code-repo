#include <stdio.h>
long long replace_0_wirh_5(long long  n);
/***************************************/
int binary_search(int n, int s, int e)
{
  int mid;
  if(s<=e)
    {
      mid=s+(e-s)/2;
      if(mid*mid==n) return mid;
      else if(mid*mid<n) return binary_search(n,mid+1,e);
      else return binary_search(n,s,mid-1);
    }
  return -1;
}
int square_root(int n)
{
  int i=1;
  while(i*i<n) i*=2;
  if(i*i==n) return i;
  return binary_search(n,i/2,i-1);
}
/***************************************/
int main()
{
  int i;
  for(i=1;i<=50;i++)
    printf("%d ",square_root(i*i));
  printf("\n");
  //printf("%lld \n",(long long)1304000000);
  //printf("%lld \n",replace_0_wirh_5(1304000000));
  return 0;
}

long long replace_0_wirh_5(long long  n)
{
  long long  d;
  d=1;
  while(n/d)
    {
      if((n/d)%10==0){n+=d*5;}
      d*=10;
    }
  return n;


}
