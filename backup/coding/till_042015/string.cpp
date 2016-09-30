#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;


void smallest_window_in_s_containing_t_chars(char *S, char *t)
{
  int s,e,l,r,i,prev,len,count;
  int W[26],T[26];
  if(S && t && S[0] && t[0])
    {
      memset(W,0,sizeof(W));
      memset(T,0,sizeof(T));
      for(i=0;t[i];i++) {T[t[i]-'a']++;}//cout << t[i]<<endl;}
      len=strlen(t);
      l=r=-1;
      count=0;
      
      for(i=0;S[i];i++)
	{
	  if(S[i]==' ')continue;
	  if(T[S[i]-'a'])
	    {

	      W[S[i]-'a']++;
	      if(W[S[i]-'a']<=T[S[i]-'a']) 
		{
		  count++;
		  if(count==1) l=i;
		  if(count==len) {r=i;break;}
		}
	    }
	}  
      if(r==-1) printf("No such window1\n");
      else
	{
	  s=l;e=r;
	  while(S[r])
	    {
	      prev=l++;
	      W[S[prev]-'a']--;
	      while(S[l]&&T[S[l]-'a']==0) l++;
	      if(!S[l]) break;
	      if(W[S[prev]-'a']>=T[S[prev]-'a'])
		{
		  if(r-l<e-s){s=l,e=r;}
		}
	      else
		{
		  r++;
		  while(S[r]&&S[r]!=S[prev])
		    {
		      if(T[S[r]-'a']) W[S[r]-'a']++;
		      r++;
		    }
		  if(!S[r]) break;
		  W[S[r]-'a']++;
		  if(r-l<e-s){s=l,e=r;}
		}
	    }
	  printf("(%d,%d)\n",s,e);
	}
    }
  else  printf("No such window2\n");
}
/* Wildcard program : Given a text and a pattern woth wildcard. Check whether the text is recognized by the pattern*/

int WildCard(char*P, char *T)
{
  int i,j,k,b,l=strlen(P);
  char *f,* S=new char[l+1];
  memset(S,0,l+1);
  i=j=0;
  while(P[i] && T[j])
    {
      if(P[i]=='*') {i++; S[0]='\0'; k=0;}
      if(P[i]=='\0') break;
      for(;P[i]!='*';i++,k++) S[k]=P[i];
      S[k]=0;

      /*
      b=j;
      while(T[b])
	{
	  for(k=0,j=b; S[k] && T[j] && (S[k]==T[j]);k++,j++);
	  if(S[k]=='\0') break;
	  else if(T[j]=='\0') return 0;
	  else b++;
	}
	if(T[b]=='\0') return 0;*/
      f=strstr(T+j,S);
      if(!f) return 0;
      j=(f+strlen(S))-T;
    }
  if(P[i]=='\0') return 1;
  else return 0;
}
int main()
{
  char P[]="this is a test string";
  char T[]="tist";
  cout<<T<<endl;
  cout<<P<<endl;
  
  smallest_window_in_s_containing_t_chars(P,T);

  //cout <<P<<"\n"<<T<<"\nResult:"<< WildCard(P,T) <<endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
