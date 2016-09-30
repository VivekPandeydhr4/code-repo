#include <stdio.h>
#include <string.h>

int main()
{
  char ch[]="";
  char str='r';
  char len= strlen(ch);
   
  ch[len++] = str;
  ch[len] = '\0';
    //strcpy(ch, str);
  printf("%s\n", ch);
  return 0;
}
