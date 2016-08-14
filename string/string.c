#include "header.h"

#define MAX_CHAR 26

void max_occur(char *str)
{
  int len = strlen(str);
  
  int count[MAX_CHAR] = {0};
  int i=0;
  
  for (i=0; i<len; i++)
    {
      count[str[i]-'a']++;
    }

  for (i=0; i<MAX_CHAR; i++)
    {
      printf("%2c ", i+'a');
    }
  printf("\n");
  for (i=0; i<MAX_CHAR; i++)
    {
      printf("%2d ", count[i]);
    }
}

char* rev_word(char* str)
{
  int len = strlen(str);
  
  int i, j, k;


  i=0;
  while(i<len/2)
    {
      swap(str+i, str+len-i-1);
      i++;
    }

  i=0; j=0; k=0;
  while(k<len)
    {
      while(*(str+j+1) != ' ' &&
	    *(str+j+1) != '\0')
	{
	  j++;
	}
      if(*(str+j+1) == ' ')
	{
	  k = j+2;
	}
      else if (*(str+j+1) == '\0') k=len;
      while(i<=j)
	{
	  swap(str+i, str+j);
	  i++; j--;
	}
      i = k;
      j = k;
    }

  return str;
}

char max_char_count(char *str)
{
  int arr['z'-'a'+1] = {0};
  int i=0, len=strlen(str), mIndx=0;

  for(i=0; i<len; i++)
    arr[*(str+i)-'a']++;

  for(i=0; i<('z'-'a'+1); i++)
    if(arr[mIndx]<arr[i])
      mIndx = i;

  return ('a'+mIndx);
}

int main()
{
  char str[] = "Pandvey Kvumar Vivek";

  printf("Max Occured Char = %c\n", max_char_count(str));
  /*
  printf("Given String = %s\n", str);
  printf("Reversed String = %s", rev_word(str));
  */

  printf("\n");
  return 0;
}
