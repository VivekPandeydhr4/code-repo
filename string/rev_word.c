
#include "header.h"

char *rev_word(char *str)
{
  
  int i=0, word_count=0;

  for (i=0; *(str+i) != '\0'; i++)
    {
      if (*(str+i) == ' ')
	{
	  while (*(str+i) == ' ')
	    i++;
	  
	  if (*(str+i) != '\0')
	    word_count++;
	}
    } 

  char **ch = (char **) malloc(word_count * sizeof(char*));

  char *t1, *t;
  t = str;

  for (i=0; i <= word_count; i++)
    {
      *(ch+i) = t;
      
      while ( (*t != '\0') && (*t != ' ')) t++;

      // while ((*(t+1) != '\0') && (*(t+1) != ' ')) t++;

      t1 = t;
      t++;
      *t1 = '\0';      
    }
  /*
  for (i=word_count; i>=0; i--)
    {
      //print(*(ch+i));
      printf("%s", *(ch+i));
      printf(" ");
    }
  */
  str = NULL;

  for (i=word_count; i>=0; i--)
    {
      if (i == word_count)
	{
	  str = *(ch+word_count);
	}
      else
	strcat(str+strlen(str), *(ch+i));

      //      if (i != 0)
      strcat(str+strlen(str), " ");      
    }
  *(str+strlen(str)-1) = '\0';
  //  strcat(str+strlen(str), "\0");      
  
  free(ch);
  return str;
}

void rev_word_1(char *str)
{
  char *tmp, *tmp1, *tmp3;

  int flag = 0;

  for (tmp=str, tmp1=str; *tmp1 != '\0'; tmp1++) 
    {
      if ((!flag) && ((*(tmp1+1) == ' ') || (strlen(tmp1+1) == 0)))
	{
	  if (*(tmp1+1) == ' ')
	    {
	      tmp3 = tmp1+2;
	      while (tmp < tmp1)
		{
		  swap(tmp, tmp1);
		  tmp++;
		  tmp1--;
		}
	    }
	  else //if (*(tmp1+1) == '\0')
	    {
	      tmp3 = NULL;
	      while (tmp < tmp1)
		{
		  swap(tmp, tmp1);
		  tmp++;
		  tmp1--;
		}
	      flag = 1;
	    }
	  
	  if(tmp3)
	    {
	      tmp = tmp1 = tmp3;
	    }
	}
    }
  
  tmp1--;
  tmp = str;

  printf("\n %s \n", str);
  while (tmp <= tmp1)
    {
      swap(tmp, tmp1);
      tmp++;
      tmp1--;
    }
}

int main()
{
  char str[] = "My name is vivek kumar pandey";

  printf("String is = %s\n", str);
  rev_word_1(str);
  printf("String with Reversed word = %s\n", str);
  printf("\n");
  return 0;
}
