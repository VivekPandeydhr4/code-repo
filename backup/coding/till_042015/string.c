#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int longest_palindrome(char *str, int *max);
void Perm(char *str, int k);
char max_occurring_char(char *str);
void f(char *s, char *perm, int i);
void permutation(char *s);
void comb(char *s, char *c, int b, int r);
void Combination(char *s, int r);
void combination(char *s, int r);
void com(char *s, int r);
void nCr(char *s, char *c, int b, int r);
int uniqueness(char*);
int minimum_Window_containing_S2(char *s, char *s2, int *i, int *j);
int wild_card(char *text, char *str);
void remove_duplicates(char *str);
void remove_2nd_from_1st(char *s1, char *s2);
void reverse(char *S, int l, int r);
int longest_palindrome_substring(char* , int *);
int longest_palindrome_substring_DP(char* , int *);
void sort_RGB(char *A);
void reverse_Words(char *s);
int main()
{
  int l,r,min,flag,i,max;
  char s[]="thopnis is a test skestpirng";
  char p[]="forgeekskeegfor";
  char str[]="RGGBRRRRGBBGRRBGGRB";
  //min=minimum_Window_containing_S2(s,p,&l,&r);
  //flag=wild_card(s,p);
  /* printf("%s\n",s); */
  /* printf("%s\n",p); */
  /* remove_2nd_from_1st(s,p); */
  printf("%s\n",s); 
  reverse_Words(s);
  printf("%s\n",s); 
  //i=longest_palindrome_substring_DP(p,&max);
  //printf("%d:%d\n",i,max); 
  //Combination(p,3);
  //reverse(str,0,strlen(str)-1);
  //printf("%s\n",str); 
  return 0;
}

void reverse_Words(char *s)
{
  char t;
  int i,j,k,n;
  if(s && *s)
    {
      n=strlen(s);
      i=0;
      while(i<n)
	{
	  j=i;
	  while(s[j]!=' '&& s[j]!='\n' && s[j]!='\0') j++;
	  for(k=j-1;i<k;i++,k--){t=s[i];s[i]=s[k];s[k]=t;}
	  i=j+1;
	}
      for(i=0,k=n-1;i<k;i++,k--){t=s[i];s[i]=s[k];s[k]=t;}
    }
}

void sort_RGB(char *A)
{
  char t;
  int i,j,k;
  if(A && *A)
    {
      for(i=-1,j=0,k=strlen(A);j<k;)
	{
	  if(A[j]=='R') {t=A[++i];A[i]=A[j];A[j++]=t;}
	  else if(A[j]=='B'){t=A[--k];A[k]=A[j];A[j]=t;}
	  else j++;
	}
    }
}


int longest_palindrome_substring_DP(char *str, int *m)
{//sunstring means continuous chars
  int max,pos,l,n,i,j,**M;
  if(!str || !str[0]){*m=0;return -1;}
  max=1;pos=0;l=0;
  n=strlen(str);
  M=(int**)malloc(n*sizeof(int*));
  for(i=0;i<n;i++) M[i]=(int*)malloc(n*sizeof(int));
  for(l=1;l<=n;l++)
    {     
      for(i=0;i<=n-l;i++)
	{
	  j=i+l-1;

	  if(i==j) M[i][j]=1;
	  else if(l==2 && M[i]==M[j]) {M[i][j]=1;max=l>max?l:max;pos=i;}
	  else if(M[i+1][j-1] && M[i]==M[j]){M[i][j]=1;max=l>max?l:max;pos=i;}
	  else M[i][j]=0;
	  printf("(%d,%d):%d ",i,j,M[i][j]);
	}
      printf("\n");
    }
  
  *m=max;
  return pos;
}
int longest_palindrome_substring(char *str, int *max)
{//sunstring means continuous chars
  int i,j,max_len,pos,n;
  if(!str || !str[0]) {*max=0;return -1;}
  max_len=1;pos=0;
  n=strlen(str);
  for(i=0;i<n-1;i++)
    {
      for(j=1;i-j>=0 && i+j<n; j++)
	if(str[i-j]!=str[i+j]) break;
      if(2*j-1> max_len){max_len=2*j-1;pos=i-j+1;}

      for(j=0;i-j>=0 && i+1+j<n; j++)
	if(str[i-j]!=str[i+1+j]) break;
      if(2*j>max_len){max_len=2*j;pos=i-j+1;}
    }
  *max=max_len;
  return pos;
}

void Comb(char *S, char *C, int r, int i, int j)
{
  if(strlen(S)-i>=r-j)
    {
      if(j==r){C[j]='\0'; printf("%s\n",C);}
      else
	{
	  C[j]=S[i];
	  Comb(S,C,r,i+1,j+1);
	  Comb(S,C,r,i+1,j);
	}
    }
}

void Combination(char *S,int r)
{//Easiest way to find combination
  char *C=malloc(r+1);
  memset(C,0,r+1);
  Comb(S,C,r,0,0);
}

void Perm(char *str, int k)
{
  char t;
  int i,l;
  if(str[k]=='\0') printf("%s\n",str);
  else
    {
      l=strlen(str);
      for(i=k;i<l;i++)
	{
	  t=str[k];str[k]=str[i];str[i]=t;
	  Perm(str,k+1);
	  t=str[k];str[k]=str[i];str[i]=t;
	}
    }
}
void reverse(char *S, int l, int r)
{
  char c;
  if(l<r)
    {
      c=S[l];S[l]=S[r];S[r]=c;
      reverse(S,l+1,r-1);
    }
}
void remove_2nd_from_1st(char *s1, char *s2)
{
  int i, j, T[26]={0};
  for(i=0;s2[i];i++) T[s2[i]-'a']++;
  for(i=0,j=0;s1[j];j++)
    {
      if(T[s1[j]-'a']==0) s1[i++]=s1[j];
    }
  s1[i]='\0';
}
void remove_duplicates(char *str)
{
  int T[26]={0},i,j;
  for(i=0,j=0;str[j];j++)
    {
      if(T[str[j]-'a']==0)
	{
	  str[i++]=str[j];
	}
      T[str[j]-'a']++;
    }
  str[i]='\0';

}
char max_occurring_char(char *str)
{
  int i,max,index,T[26]={0};
  if(str)
    {
      for(i=0;str[i];i++) T[str[i]-'a']++;
      max=0,index=-1;
      for(i=0;i<26;i++)
	{
	  if(T[i]>max)
	    {
	      max=T[i];index=i;
	    }
	}
      return (index+'a');
    }

}
int wild_card(char *text, char *str)
{
  int i,j,l;
  char *p, *buff,*k;
  l=strlen(str);
  buff=(char*)malloc(l+1);
  buff[0]='\0';
  i=0;k=text;
  while(str[i])
    {
      j=0;text=k+strlen(buff);
      while(str[i]!='\0' && str[i]!='*') buff[j++]=str[i++];
      buff[j]='\0';
      k=strstr(text,buff);
      if(k==NULL) return 0;
      if(str[i]=='*') i++;
    }
  return 1;
}

int minimum_Window_containing_S2(char *s, char *p, int *l, int *r)
{
  int i,j,k,len,count;
  int T[26],W[26];
  memset(T,0,26*sizeof(int));  
  memset(W,0,26*sizeof(int));  
  len=strlen(p);
  for(i=0;p[i];i++) T[p[i]-'a']++;
  for(count=0,i=0;s[i];i++)
    {
      if(T[s[i]-'a'])
	{
	  if(++W[s[i]-'a']<=T[s[i]-'a'])  count++;
	  if(count==1) *l=i;
	  else if(count==len) {*r=i;break;}
	}
    }

  if(count<len) {*l=*r=-1; return 0;}

  i=*l,j=*r;
  while(s[j])
    {      
      for(k=i+1;k<j && !T[s[k]-'a'];k++);     
      --W[s[i]-'a'];
      if(k==j || W[s[i]-'a']< T[s[i]-'a'])
	{
	  for(j++;s[j]&& s[j] !=s[i];j++)
	    {
	      if(T[s[j]-'a']) 	  W[s[j]-'a']++;
	    }
	  if(!s[j]) break;
	  W[s[i]-'a']++;
	}
      i=k;
      printf("%d,%d\n",i,j);
      if(*r-*l > j-i){*r=j,*l=i;}
    }
  return (*r-*l+1);
}

int uniqueness(char *str)
{
  int i,j;
  if(!str || !str[0]) return 1;
  int l=strlen(str);

  for(i=0;i<l-1;i++)    
    for(j=i+1;str[j];j++)
      if(str[j]==str[i]) return 0;
  return 1;			 
}


void com(char *s, int r)
{
  char *c=malloc(r+1);
  nCr(s,c,0,r);

}

void nCr(char *s, char *c, int b, int r)
{
  int l=strlen(s);
  char t;
  if(b==r){c[b]='\0';printf("%s\n",c);}
  else if(!s[0]){}
  else
    {
      t=s[l-1];
      c[b]=t;
      s[l-1]='\0';
      nCr(s,c,b+1,r);
      nCr(s,c,b,r);
      s[l-1]=t;
    }
}



void combination(char *s, int r)
{
  char *c=malloc(r+1);
  comb(s,c,0,r);
}

void comb(char *s, char *c, int b, int r)
{
  int i,n;
  n=strlen(s);
  if(b==r) {c[b]='\0';printf("%s\n",c);}
  else
    {
      for(i=0;i<=n-r+b;i++)
	{
	  c[b]=s[i];
	  comb(s+i+1,c,b+1,r);	  
	}
    }
}

void permutation(char *s)
{
  int l=strlen(s);
  char *perm=malloc(l+1);
  //  memset(perm,0,l+1);
  f(s,perm,0);
}
void f(char *s, char *perm, int i)
{
  int j,l=strlen(s);
  if(i==l) {perm[i]='\0'; printf("%s\n",perm);}
  else 
    {
      for(j=0;s[j];j++)
	{
	  if(s[j]=='\n') continue;
	  perm[i]=s[j];
	  s[j]='\n';
	  f(s,perm,i+1);
	  s[j]=perm[i];
	}
    }
}

int HIRE(char *s)
{
  unsigned int l,i,j;
  l=strlen(s);
  if(!l) return 1;
  if(s[0]!='h') return 0;
  for(i=0;i<l && s[i]=='h';i++);
  if(4*i>l) return 0;
  
  for(j=i;j<2*i;j++) if(s[j]!='i') return 0;
  for(;j<3*i;j++) if(s[j]!='r') return 0;
  for(;j<4*i;j++) if(s[j]!='e') return 0;
  
  return HIRE(s+4*i);
}
