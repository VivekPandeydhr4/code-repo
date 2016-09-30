#include "header.h"

/********************************************************
 http://www.careercup.com/question?id=5106757177180160

 Reverse characters of word in a sentence while words are 
 in same order. 

 Example:--

 @"the boy ran" => @"eht yob nar"
 *******************************************************/

char* rev_word_char(char *str)
{
  char *t1=NULL, *t2=NULL, *t3=NULL;

  t1 = t2 = str;

  while(*t1 != '\0')
    {
      while(*t2 != ' ' && *t2 != '\0')
	{
	  //t2 = t2+1;
	  if(*(t2+1) == ' ')
	    {
	      t3 = t2+2;
	      break;
	    }
	  else
	    t2 = t2+1;
	}
      if (*t2 == '\0') 
	{
	  t3=t2;
	  t2--;
	}
      while(t2 > t1)
	{
	  swap(t1, t2);
	  t1++;
	  t2--;
	}
      t1 = t2 = t3;
    }
  return str;
}

char* reverse_word(char *str)
{
  char *t1=NULL, *t2=NULL;

  t1 = t2 = str;

  while(*t2 != '\0')
    {
      t2++;
    }
  t2--;

  while(t1 < t2)
    {
      swap(t1, t2);
      t1++;
      t2--;
    }
  return str;
}
int main ()
{
  /*************************************************************/
   char str[] = "My name is Vivek Pandey";
   char str2[] = "vivek";
   printf(" String :=>\n");
   print(str);

   printf("\n Reversed String :=>\n");
   char* str1 = rev_word_char(str);
   //char* str3 = reverse_word(str2);
   print(str1);

   /*   char *a="asdc", *b="asde";
   printf("a=%c b=%c\n", a, b);
   swap(&a, &b);
     printf("a=%c b=%c\n", a, b);
   */
  /*************************************************************/

  return 0;
}
