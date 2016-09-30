#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>

using namespace std;
/********************************************************/
int wild_card(char *text, char *pat)
{
  int i,j,l;
  char *p, *buff,*k;
  l=strlen(pat);
  buff=(char*)malloc(l+1);
  buff[0]='\0';
  i=0;k=text;
  while(pat[i])
    {
      j=0;text=k+strlen(buff);
      while(pat[i]!='\0' && pat[i]!='*') buff[j++]=pat[i++];
      buff[j]='\0';
      k=strstr(text,buff);
      if(k==NULL) return 0;
      if(pat[i]=='*') i++;
    }
  return 1;
}

int match(const char *P, const char *T)
{
  int i;
  char *word;
  if(!*P) if(!*T) return 1; else return 0;
  if(!*T) if(*P=='*' && !*(P+1)) return 1; else return 0;
  if(*P=='?') return match(P+1,T+1);
  if(*P=='*')
    {
      word=(char*)malloc(strlen(P)+1);
      for(i=1;P[i]&&P[i]!='*'&&P[i]!='?';i++) word[i-1]=P[i];
      if(i==1) return 1;
      word[i-1]='\0';
      T=strstr(T,word);  
      free(word);
      if(!T) return 0;
      else return match(P+i,T+i-1);      
    }
  else
    {
      if(*P==*T) return match(P+1,T+1);
      else return 0;
    }
}

void reverse_wordwise(char *s)
{
  int i,j,k;
  char t;
  i=j=0;
  while(s[i])
    {
      j=i;
      while(s[j]&&s[j]!=' ') j++;
      for(k=j-1;i<k;i++,k--) {t=s[i];s[i]=s[k];s[k]=t;}
      if(s[j]) break;
      i=j+1;
    }
  for(i=0,j=j-1;i<j;i++,j--){t=s[i];s[i]=s[j];s[j]=t;}
}

int longest_substring_with_k_chars(char *str, int k)
{
  int i,j,S,E,c,T[26]={0};
  if(!str || k<=0) return -1;
  for(i=0,c=0;str[i];i++)
    {
      T[str[i]-'a']++;
      if(T[str[i]-'a']==1)    
	{
	  c++;
	  if(c==k+1) break;
	}
    }
  if(c==k) return i; else if(c<k) return -1;
  S=0;E=i-1;j=0;
  while(str[i])
    {
      for(;j<i;j++)
	{
	  T[str[j]-'a']--;
	  if(T[str[j]-'a']==0) {j++;break;}
	}
      for(i++;str[i];i++)
	{
	  T[str[i]-'a']++;
	  if(T[str[i]-'a']==1) break;
	}
      if(i-j>E-S+1) {S=j,E=i-1;}
    }
  printf("(%d, %d):",S,E);
  return E-S+1;
}


void reverse_wordwise_withComma_dot(char *s)
{
  int i,j,k;
  char t;
  i=j=0;
  while(s[i])
    {
      j=i;
      while(s[j]&&s[j]!=' ') j++;
      for(k=j-1;i<k;i++,k--) {t=s[i];s[i]=s[k];s[k]=t;}
      if(s[j]) break;
      i=j+1;
    }
  for(i=0,j=j-1;i<j;i++,j--){t=s[i];s[i]=s[j];s[j]=t;}
}

int parenthesis_nesting_level(char *str)
{//i/p: (((x))(((y)))) o/p:4
  int i=0,stack_size=0,max=0;
  stack<char> s;
  if(!str || !str[0]) return 0;
  for(i=0;str[i];i++)
    {
      switch(str[i])
	{
	case '(':
	  s.push(str[i]);
	  stack_size++;
	  if(stack_size>max) max=stack_size;
	  break;
	case ')':
	  if(s.empty()) return -1;
	  s.pop();
	  stack_size--;
	  break;
	default:;
	}
    }    
  if(!s.empty()) return -1;
  return max;
}

int parenthesis_nesting_level_without_stack(char *str)
{//i/p: (((x))(((y)))) o/p:4
  int i=0,Size=0,max=0;
  if(!str || !str[0]) return 0;
  for(i=0;str[i];i++)
    {
      switch(str[i])
	{
	case '(':
	  Size++;
	  if(Size>max) max=Size;
	  break;
	case ')':
	  Size--;
	  if(Size<0) return -1;	  
	  break;
	default:;
	}
    }    
  if(Size==0)  return max;
  else return -1;
}

char* run_length_encoding(char *str)
{
  char *encoding=NULL,c='\0';
  int l=0,i=0,j=0,r=0,current=0,count=0;
  l=strlen(str);
  encoding=(char*)malloc((2*l+1)*sizeof(char));
  memset(encoding,0,(2*l+1)*sizeof(char));

  for(i=0,j=0,current=0,count=0;str[i];)
    {
      if(str[i]==str[current]) {count++;i++;}
      else 
	{
	  encoding[j++]=str[current];
	  l=j;
	  while(count)
	    {
	      encoding[j++]=count%10+'0';
	      count=count/10;
	    }	  
	  r=j-1;
	  while(l<r){c=encoding[l];encoding[l]=encoding[r];encoding[r]=c;l++;r--;}
	  current=i;count=0;
	}
    }
  	  encoding[j++]=str[current];
	  l=j;
	  while(count)
	    {
	      encoding[j++]=count%10+'0';
	      count=count/10;
	    }	  
	  r=j-1;
	  while(l<r){c=encoding[l];encoding[l]=encoding[r];encoding[r]=c;l++;r--;}

  return encoding;
}

void remove_2nd_string_from_first(char *first, char *second)
{
  int T[26]={0},i,j;
  if(*first && *second)
    {
      for(i=0;second[i];i++) T[second[i]-'a']=1;
      for(i=0,j=0;first[j];j++)
	{
	  if(!T[first[j]-'a']) 	  	  
	    first[i++]=first[j];	  
	}
      first[i]='\0';
    }
}

int smallest_window_in_str_containing_patternChars(char *str, char *pat)
{
  int T[26]={0},W[26]={0},count=0,i=0,j=0,k=0,start=0,end=0,flag=0,wCount=0;
  //xfill hash table for pat
  for(i=0;pat[i];i++) {T[pat[i]-'a']++;count++;}

  //find the first window which has all chars of pat
  wCount=0;
  for(i=0;str[i];i++)
    {
      if(T[str[i]-'a'])
	{
	  W[str[i]-'a']++;
	  if(W[str[i]-'a']<=T[str[i]-'a'])
	    {
	      wCount++;
	      if(wCount==1) start=i;
	      if(wCount==count) {end=i;break;}
	    }	  
	}
    }
  if(!str[i]) return -1;
  // leaving 1-by-1 chars from start of first window
  for(i=start,j=end;str[j];)
    {
      W[str[i]-'a']--;
    
      k=i+1;
      flag=0;
      while(k<=j && !T[str[k]-'a']) k++;
      if(W[str[i]-'a']>=T[str[i]-'a']) {
	i=k;
    	if(end-start > j-i) {end=j;start=i;}
    	continue;
      }
      
      if(k>j) flag=1;
      while(str[j] && str[j]!=str[i]) 
	{
	  if(T[str[j]-'a']) W[str[j]-'a']++;
	  j++;
	}
      if(flag) i=j;

      if(str[j]) {W[str[j]-'a']++;i=k;if(end-start > j-i) {end=j;start=i;}}
      else break;

    }
  //cout << start <<","<<end<<":";
  return (end-start);     
}
/********************************************************/

int main()
{
  char f[]="this is a test sting",s[]="ist";
  //cout <<f<<","<<s<<endl;

  cout<<smallest_window_in_str_containing_patternChars(f,s)<<endl;


  // remove_2nd_string_from_first(f,s);
  // cout <<f<<endl;
  //cout <<run_length_encoding(s)<<endl;
  // cout<<longest_substring_with_k_chars(s,3)<<endl;
  // reverse_wordwise(s);
  // cout <<s<<endl;
  // cout<< match("g*ks", "geeks")<<endl ; // Yes
  // cout<< match("ge?ks*", "geeksforgeeks")<<endl ; // Yes
  // cout<< match("g*k", "gee")<<endl ;  // No because 'k' is not in second
  // cout<< match("*pqrs", "pqrst")<<endl ; // No because 't' is not in first
  // cout<< match("abc*bcd", "abcdhghgbcd")<<endl ; // Yes
  // cout<< match("abc*c?d", "abcd")<<endl ; // No because second must have 2 instances of 'c'
  // cout<< match("*c*d", "abcd")<<endl ; // Yes
  // cout<< match("*?c*d", "abcd")<<endl ; // Yes
  return 0;
}
