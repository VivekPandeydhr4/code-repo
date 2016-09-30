#include <stdio.h>
#include <stdlib.h>
void Min_Max(int *A, int s, int e, int *min, int *max);
int BinarySearch(int A[], int s, int e, int k);
void Merge_Sort(int A[],int s, int e);
void QuickSort(int A[], int s, int e);
int partition(int A[], int s, int e);
int inversions(int A[], int S, int E);
void min_Distance(int A[],int n, int a, int b);
void alternate_positive_negative(int A[],int n);
void contiguous_1_withSingle_0(int A[], int n);
int Find_Peak_in_Asc_Desc_array(int *A, int s , int e,int n);
int b_search_for_above(int *A, int n);
void wave_like_sorting(int A[], int n);
void Nut_Bolt(char *N, char *B, int s, int e);
void Contiguous_1_WithSingle_0(int A[], int n);
void Sort(int *A, int n, int *B, int m);
int main()
{
  char N[]="vikaspnldey",C[]="yedmnpsakiv";
  /* int i,min, max,A[]={8,7,6,3,2,1,4,5};// A[]={10,2,33,24,15,6,47,18,9}; */
  int i,A[]={8,3,2,8,5,4,9,3,1,2,3,7},B[]={8,3,1,2}; 
  for(i=0;i<12;i++)  
     printf("%d ",A[i]);  
  printf("\n"); 
  for(i=0;i<4;i++)  
     printf("%d ",B[i]);  
  printf("\n"); 
  Sort(A,12,B,4);
  for(i=0;i<12;i++)  
     printf("%d ",A[i]);  
  printf("\n"); 

  //Contiguous_1_WithSingle_0(B,10);
  /* printf("%s\n",N); */
  /* printf("%s\n",B); */
  /* Nut_Bolt(N,B,0,10); */
  /* printf("%s\n",N); */
  /* printf("%s\n",B); */
  /* wave_like_sorting(A,8); */

  /* for(i=0;i<8;i++)  */
  /*    printf("%d ",A[i]);  */
  /* printf("\n"); */


  //printf("%d\n",b_search_for_above(A,5));
  
  //alternate_positive_negative(A,13);
  // Min_Max(A,0,6,&min,&max);
  //printf("%d,%d\n",min,max);
  //min_Distance(A,13,1,3);

  /* printf("inversions:%d\n",inversions(A,0,8)); */
  /* for(i=0;i<13;i++)  */
  /*    printf("%d ",A[i]);  */
  /* printf("\n"); */
  return 0;
}
int search(int x, int *B, int m )
{
  int i;
  for(i=0;i<m;i++) if(B[i]==x) return i;
  return -1;
}
int Compare(int *A, int j, int p, int *B, int m)
{
  int x,y;
  x=search(A[j],B,m);
  y=search(A[p],B,m);
  if(x>-1 && y>-1) {if(x<y) return 1;else return 0;}
  else if(x>-1) return 1;
  else if(y>-1) return 0;
  else return A[j]<A[p];
}
int PPartition(int *A, int n , int *B, int m)
{
  int i, j,t;
  for(i=-1,j=0;j<n-1;j++)
    {
      if(Compare(A,j,n-1,B,m)){t=A[++i];A[i]=A[j];A[j]=t;}
    }
  t=A[++i];A[i]=A[j];A[j]=t;
  return i;
}
void Sort(int *A, int n, int *B, int m)
{
  int i;
  if(n>1)
    {
      i=PPartition(A,n,B,m);
      if(i!=0) Sort(A,i,B,m);
      if(i!=n-1) Sort(A+i+1,n-i-1,B,m);
    }
}
void Contiguous_1_WithSingle_0(int A[], int n)
{
  int i, j, pos, l, r, mpos;
  l=r=pos=mpos=-1;
  for(i=0,j=0;j<n;j++)
    {
      if(A[j]) continue;
      if(pos==-1){l=i;r=j;mpos=pos=j;}
      else
	{
	  if(r-l<j-i-1){l=i;r=j-1;mpos=pos; printf("%d-%d,",l,r);}
	  i=pos+1;pos=j;
	}
    }
  if(l==-1 || j-i-1 >r-l) {l=i;r=j-1;mpos=pos; printf("%d-%d,",l,r);}
  printf("\n(%d,%d):%d\n",l,r,mpos);
}


void swap_char(char *a, char *b)
{
  char t=*a;
  *a=*b;
  *b=t;
}
int swap(int *a, int *b)
{
  int t=*a;
  *a=*b;
  *b=t;
}

int Partition(char *A, int s, int e, char c)
{
  int i,j;
  if(s==e) return s;
  if(s<e)
    {
      i=s-1;
      j=s;
      while(j<e)
	{
	  if(A[j]<c) swap_char(A+(++i),A+(j++));
	  else if(A[j]>c) j++;
	  else swap_char(A+j,A+e);
	}
       swap_char(A+(++i),A+j);
       return i;
    }
}

void Nut_Bolt(char *N, char *B, int s, int e)
{
  int i,j;
  if(s<e)
    {
      i=Partition(B,s,e,N[e]);
      j=Partition(N,s,e,B[i]);
      if(i!=j) printf("Wrong input\n");
      else
	{
	  if(i!=s) Nut_Bolt(N,B,s,i-1);
	  if(i!=e) Nut_Bolt(N,B,i+1,e);	  
	}
    }
}


void wave_like_sorting(int A[], int n)
{
  int i,smallest;
  if(n==2){if(A[0]<A[1]) swap(A,A+1);}
  else if(n>2)
    {
      for(i=1;i<n;i+=2)
	{
	  smallest=i;
	  if(A[i-1]<A[smallest]) smallest=i-1;
	  if(i+1<n && A[i+1]<A[smallest]) smallest=i+1;
	  swap(A+i,A+smallest);
	}
    }
}



int Find_Peak_in_Asc_Desc_array(int *A, int s , int e, int n)
{
  int mid;
 
  if(s<=e)
    {
      mid=s+(e-s)/2;
      if((mid==0 && A[mid]>A[mid+1])||(mid==n-1 && A[mid]>A[mid-1])||( A[mid]>A[mid+1] &&A[mid]>A[mid-1])) return mid;
      else if(A[mid]>A[mid+1]  && A[mid]<A[mid-1]) return Find_Peak_in_Asc_Desc_array(A,s,mid-1,n);
      else return Find_Peak_in_Asc_Desc_array(A,mid+1,e,n);
    }
  return -1;
}
int Find_Peak_in_Asc_Desc_array1(int *A, int s , int e)
{
  int mid;
 
  if(s<=e)
    {
      mid=s+(e-s)/2;
      if( A[mid]>A[mid+1] && A[mid]>A[mid-1]) return mid;
      else if(A[mid]>A[mid+1]  && A[mid]<A[mid-1]) return Find_Peak_in_Asc_Desc_array1(A,s,mid-1);
      else return Find_Peak_in_Asc_Desc_array1(A,mid+1,e);
    }
  return -1;
}

int b_search_for_above(int *A, int n)
{
  if(A[0]>A[1]) return 0;
  if(A[n-1]>A[n-2]) return n-1;
  else return Find_Peak_in_Asc_Desc_array1(A,1,n-2);

}

void contiguous_1_withSingle_0(int A[], int n)
{
  int l,r,max_pos,i,j,pos,f;
  l=r=0;max_pos=-1;f=0;pos=-1;
  for(i=j=0;j<n;j++)
    {
      if(A[j]==0)
	{
	  f++;
	  if(f==1){pos=j;}
	  else {
	      if(j-i-1>r-l){max_pos=pos,l=i,r=j-1;}
	      i=pos+1;
	      pos=j;
	      f=1;
	    }
	}
    }
  if(j-i-1>r-l){max_pos=pos,l=i,r=j-1;}
  printf("(%d,%d):%d\n",l,r,max_pos);
}
/* void swap(int *a, int *b) */
/* { */
/*   int t=*a; */
/*   *a=*b; */
/*   *b=t; */
/* } */

void alternate_positive_negative(int A[], int n)
{
  int i,j;
  for(i=0,j=1;i<n;i+=2)
    {
      if(A[i]<0)
	{
	  while(j<n && A[j]<0) j+=2;
	  if(j>=n) break;
	  swap(A+i,A+j);
	}
    }
}
void min_Distance(int A[],int n, int a, int b)
{
  int i,j,k,d,l,r;
  l=r=-1;
  for(j=0;j<n;j++)
    {
      if(l>=0&&r>=0) break;
      if(A[j]==a) l=j;
      else if(A[j]==b) r=j;
      else {}
      i=j;
    }
  if(l>r) swap(&l,&r);
  d=r-l;
  while(j<n)
    {
      if(A[j]==a||A[j]==b)
	{
	  if(A[j]!=A[i])
	    {
	      if(j-i<d)
		{
		  l=i,r=j,d=j-i;
		}
	    }
	  i=j;
	}
      j++;
    }
  printf("%d : %d, %d\n",d,l,r);
}


int inversions(int A[], int S, int E)
{
  int count,mid, x, y ,i , j, k, *temp;
  if(S<E)
    {
      mid=S+(E-S)/2;
      x=inversions(A,S,mid);
      y=inversions(A,mid+1,E);
      temp=(int*)malloc((mid-S+1)*sizeof(int));
      for(i=S;i<=mid;i++) temp[i-S]=A[i];
      j=0;k=mid+1;count=0;
      for(i=S;i<=E;i++)
	{
	  if(j>mid-S){A[i]=A[k];k++;continue;}
	  if(k>E){A[i]=temp[j];j++;continue;}
	  if(temp[j]<=A[k]){A[i]=temp[j];j++;}
	  else{A[i]=A[k];k++;count+=(mid-j+1);}	  
	}
      free(temp);
      return (count+x+y);
    }
  return 0;
}
void Min_Max(int *A, int s, int e, int *min, int *max)
{
  int m,lmin,lmax,rmin,rmax;
  if(s==e){*min=A[s];*max=A[e];}
  else
    {
      m=(s+e)/2;
      
      Min_Max(A,s,m,&lmin,&lmax);
      Min_Max(A,m+1,e,&rmin,&rmax);

      *min=lmin<rmin?lmin:rmin;
      *max=lmax>rmax?lmax:rmax;
    }
}


int BinarySearch(int A[], int s, int e, int k)
{
  int mid;
  if(s<=e)
    {
      mid=(s+e)/2;
      if(A[mid]==k) return mid;
      if(k<A[mid])return BinarySearch(A,s,mid-1,k);
      else return BinarySearch(A,mid+1,e,k);
    }
  else return -1;
}

void Merge_Sort(int A[],int s, int e)
{
  int mid,l,r,i,j,k;
  int *B=malloc((1+(e-s)/2)*sizeof(int));
  int *C=malloc((1+(e-s)/2)*sizeof(int));
  if(s<e)
    {
      mid=(s+e)/2;

      Merge_Sort(A,s,mid);
      Merge_Sort(A,mid+1,e);

      for(i=s,j=0;i<=mid;i++) B[j++]=A[i];
      for(i=mid+1,k=0;i<=e;i++) C[k++]=A[i];

      l=0;r=0;
      
      for(i=s;i<=e;i++)
	{
	  if(l>=j) A[i]=C[r++];
	  else if(r>=k) A[i]=B[l++];
	  else if(B[l]<=C[r]) A[i]=B[l++];
	  else A[i]=C[r++];
	}
    }
}
void QuickSort(int A[], int s, int e)
{
  int i;
  if(s<e)
    {
      i=partition(A,s,e);
      if(i>s) QuickSort(A,s,i-1);
      if(i<e) QuickSort(A,i+1,e);
    }
}

int partition(int A[], int s, int e)
{
  int pivot,i,j,t;
  if(s<e);
  {
    pivot=A[e];
    for(i=s-1,j=s;j<e;j++)
      {
	if(A[j]<pivot)
	  {
	    t=A[++i];
	    A[i]=A[j];
	    A[j]=t;
	  }
      }
    A[e]=A[++i];
    A[i]=pivot;
    return i;
  }
}
