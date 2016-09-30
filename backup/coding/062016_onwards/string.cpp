#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
//*******************************************************************

int isSpace(char c)
{
  if(c==' ' || c=='\n' || c=='\t') return 1;
  else return 0;
}

//*******************************************************************
void column_name_in_a_excel_sheet_for_a_columnNumber(int n)
{
  int d=0;
  if(n)
    {
      d=n%26;
      if(d==0)
	{
	  column_name_in_a_excel_sheet_for_a_columnNumber(n/26 -1);
	  cout<<'Z';
	}
      else
	{
	  column_name_in_a_excel_sheet_for_a_columnNumber(n/26);
	  cout<<(char)('A'+d-1);
	}
    }
}
int count_words(char *s)
{
  int i,count;
  if(!*s) return 0;
  for(i=1,count=0;s[i];i++)
    {
      if(isSpace(s[i]) && !isSpace(s[i-1])) count++;
    }
  if(!isSpace(s[i-1])) count++;
  return count;
}

int longest_palindrome(char *s)
{
  int i,j,len,d,pal_i=0,pal_j=0;
  if(!*s) return 0;
  for(i=1;s[i];i++)
    {
      len=1;
      for(d=1;i-d>=0 && s[i+d];d++)
	{
	  if(s[i-d]==s[i+d]) len+=2;
	  else break;
	}
      if(pal_j-pal_i+1<len)
	{
	  pal_i= i-len/2;
	  pal_j=i+len/2;
	}
    }
  for(i=0;s[i+1];i++)
    {
      j=i+1;
      len=0;
      for(d=0;i-d>=0 && s[j+d];d++)
	{
	  if(s[i-d]==s[j+d]) len+=2;
	  else break;
	}
      if(pal_j-pal_i+1<len)
	{
	  pal_i= i-len/2+1;
	  pal_j= j+len/2-1;
	}
    }
  for(i=pal_i;i<=pal_j;i++) cout<< s[i];
  cout<<endl;
  return pal_j-pal_i+1;
}
//***************************************************************************

int smallest_substring_of_1st_containining_second(char *F, char *S)
{//Check
  int i,j,k,l,r,FT[128]={0},ST[128]={0},cnt=0;
  for(i=0;S[i];i++) {ST[S[i]]++;if(ST[S[i]]==1) cnt++;}
  for(i=-1,j=0;F[j];j++)
    {
      if(ST[F[j]])
	{
	  FT[F[j]]++;
	  if(i==-1) i=j;
	  if(FT[F[j]]==ST[F[j]])
	    {
	      cnt--;
	      if(!cnt) break;
	    }
	}
    }
  l=i;r=j;
  while(F[j])
    {
      while(i<=j)
	{
	  if(ST[F[i]])
	    {
	      FT[F[i]]--;
	      if(FT[F[i]]<ST[F[i]]) {break;}
	    }
	  i++;
	}
      k=i;
      i++;
      while(i<j)
	{	  
	  if(ST[F[i]]) break;
	  i++;
	}
      j++;
      while(F[j])
	{
	  if(ST[F[j]]){
	    FT[F[j]]++;if(F[j]==F[k])break;
	  }
	  j++;
	}
      if(j-i<r-l){r=j,l=i;}
    }
}
void swap(char *a, char *b)
{
  char c;
  c=*a;*a=*b;*b=c;
}
//***************************************************************************
//                          PERMUTATIONS

void fun1(char *S, char *P, int b)
{
  int i;
  if(!S[0]){P[b]='\0';cout<<P<<endl;}
  else
    {
      for(i=0;S[i];i++)
	{
	  if((i==0)||(S[i]!=S[i-1]))
	    {
	      swap(S,S+i);P[b]=S[0];
	      fun1(S+1,P,b+1);
	      swap(S,S+i);
	    }
	}
    }
}
void permutation(char *S)
{//ERRONEOUS
  int n=strlen(S);
  sort(S,S+n);
  if(n>0)
    {
      char *P=new char[n+1];
      fun1(S,P,0);
    }
}

//***************************************************************************
int fact(int n)
{
  if(n==0) return 1;
  else return n*fact(n-1);
}
int lexicographic_rank(char *S)
{
  int n=strlen(S),i,j,less,greater,rank;
  char temp[n+1];
  memset(temp,0,n+1);
  strcpy(temp,S);
  rank=0;
  for(i=0;S[i];i++)
    {
      less=greater=0;
      for(j=0;temp[j];j++)
	{
	  if(temp[j]!='#')
	    {
	      if(temp[j]<S[i]) less++;
	      else if(temp[j]>S[i]) greater++;
	      else temp[j]='#';
	      
	    }
	}
      rank+=less*fact(less+greater);            
    }
  rank++;
  return rank;
}

int isInterleaving_C_of_AB(char *A, char *B, char *C)
{
}
//***************************************************************************
int main()
{
  char S[]="bca";
  char A[]="ace", B[]="bdf", C[]="acbdfe";

  cout<<A<<' '<<B<<' '<<C<<endl;
  cout<<isInterleaving_C_of_AB(A,B,C);
  //permutation(S);
  //cout<<lexicographic_rank(S);
  //cout<<longest_palindrome(S);
  //cout<<count_words(S) <<endl;
  //column_name_in_a_excel_sheet_for_a_columnNumber(56);
  cout<<endl;return 0;
}


















