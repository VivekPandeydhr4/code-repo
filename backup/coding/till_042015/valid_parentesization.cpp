#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stack>

using namespace std;

int isValid_parenthisation(char* Exp);
int main()
{
  int i,f=1;
  stack<char> s;
  char Exp[1000];
  scanf("%s",Exp);
  for(i=0;Exp[i];i++)
    {
      switch(Exp[i])
	{
	case '(':
	case '{':
	case '[': s.push(Exp[i]); break;
	case')':
	  if(s.top()=='(')s.pop();
	  else f=0;
	  break;	    
	case'}':
	  if(s.top()=='{') s.pop();
	  else f=0;
	  break;	    
	case']':
	  if(s.top()=='[')s.pop();
	  else f=0;
	  break;	    
	}
      if(f==0) {printf("Invalid\n"); break;}
    }
  if(s.empty()) printf("Valid\n");;
  


  //printf("%d\n", isValid_parenthisation("{[[(())]({[]}())}"));

  return 0;
}

int isValid_parenthisation(char* Exp)
{
  int i;
  stack<char> s;
  for(i=0;Exp[i];i++)
    {
      switch(Exp[i])
	{
	case '(':
	case '{':
	case '[': s.push(Exp[i]); break;
	case')':
	  if(s.top()=='(')
	    {s.pop();break;}
	  else return 0;

	case'}':
	  if(s.top()=='{')
	    {s.pop();break;}
	  else return 0;

	case']':
	  if(s.top()=='[')
	    {s.pop();break;}
	  else return 0;
	}
    }
  if(s.empty()) return 1;
  else return 0;
}
