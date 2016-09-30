#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEST_PORT        5600
#define DEST_IP          "127.0.0.1"
#define MAXLEN           1024
#define Max_Len_PlName   32
/***********************************/
typedef struct mid_n_move
{//this contains the index in buff_file(with GS_R msg)where the move_string starts of a given match_ID 
    int MID;
    int index_in_buff_file;
    struct mid_n_move *next_MID_n_MOVE;
}MID_n_MOVE;


/***********************************/
char *buff_srv,*buff_file,**buff_print,*move;
char **mat;

char* itoa(int value);
MID_n_MOVE* print_match_list(char *buff_file);
void extract_games(char *);
void display_board(char **);
void init_matrix(char **,int);
char *getstr();
char *actual_move(char* string);
void update_match_board(char *buff_file,MID_n_MOVE *xyz,char *match_asPlayer);

int main()
{
  FILE *fd_wr, *fd_rd;
  struct sockaddr_in dest_addr;                                                       // will hold the destination addr
  char *temp_buff,*temp;
  int len, bytes_sent, recv_ret=-1, con_ret=1;
  int sockfd,i=0,k=0,m=0;                                                                         // listen on sock_fd, new connection on new_fd
  char *file_rd, *file_wr;
  char *Game_name,*Game_id,*winner_statement;
  char symbol, choice;
  char *clientname;
  
  file_rd =(char *)malloc(sizeof(char)*20);
  file_wr=(char *)malloc(sizeof(char)*20);
  buff_srv=(char *)malloc(sizeof(char)*200);
  buff_file=(char *)malloc(sizeof(char)*200);
  temp_buff=(char *)malloc(sizeof(char)*200);
  temp=(char *)malloc(sizeof(char)*200);
  move=(char *)malloc(sizeof(char)*200);
  clientname=(char *)malloc(sizeof(char)*MAXLEN);  
  winner_statement=(char *)malloc(sizeof(char)*MAXLEN);  
  Game_id=(char *)malloc(sizeof(char)*10);  

  buff_print = (char **)malloc(sizeof(char *)*200);
  for(i=0;i<200;i++)
    buff_print[i]=(char *)malloc(sizeof(char)*200);
  

  mat = (char **)malloc(sizeof(char *)*3);
  for(i=0;i<3;i++)
    mat[i]=(char *)malloc(sizeof(char)*3);
  
  sockfd = socket(PF_INET, SOCK_STREAM, 0);                                          // do some error checking!
  
  if (sockfd  < 0) 
    {
      perror("socket");
      exit(1);
    }
  
  dest_addr.sin_family = AF_INET;                                                    // host byte order
  dest_addr.sin_port = htons(DEST_PORT);                                             // short, network byte order
  dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
  memset(dest_addr.sin_zero, '\0', sizeof(dest_addr.sin_zero));
  
  con_ret=connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
  
  if(con_ret < 0)                               		                     /* to checking the connection. */
    {
      perror("connect");
      exit(1);
    }
//formalities with the player
/*   while(1){ */
/*   printf("\n\tPlay Game?(Y/N): "); */
/*   buff_file = getstr(); */
  
/*   if((strncmp(buff_file,"Y",1)==0)||(strncmp(buff_file,"y",1)==0)){ */
/*       printf("Client name:"); */
/*       clientname = getstr(); */
/*       break; */
/*   } */
/*   else  */
/*       printf("Wrong Choice:(Enter again)\n"); */
/*   } */

  printf("\n\tPlayer Name: ");
  clientname = getstr();
 
  i=0;k=0;
  buff_srv[i++]='G';
  buff_srv[i++]='L';
  buff_srv[i++]=' ';
  
  for(;clientname[k]!='\0';)
  {   
      buff_srv[i++]=clientname[k++];
  }
  buff_srv[i]='\0';
//  printf("%s\n",buff_srv);
  
  bytes_sent = send(sockfd, buff_srv, strlen(buff_srv)+1, 0);
//  printf("sent:%s\n",buff_srv);
  //printf("%d\n",bytes_sent);
  recv_ret=recv(sockfd, buff_file,MAXLEN, 0);
//  printf("rcvd:%s\n",buff_file);
  
  //printf("%s\n",buff_file);
  for( i=0,k=0;buff_file[k]!='\0';)
  {
      temp_buff[i++]=buff_file[k++];
  }
  temp_buff[i]='\0';
//  printf("temp_buff: %s\n",temp_buff);

  if(strncmp(temp_buff,"GL_R",4)==0)
    {
	printf("\n-------------------------------------------------------");
	printf("\n|  AVAILABLE GAMES====>> ");
	extract_games(buff_file);
	printf("\n-------------------------------------------------------\n");

    }
  int flag_game=0;

  printf("\tSELECT GAME: ");
  while(1){
      Game_name = getstr();
//check whether game entered to play exists or not.if not then enter again the correct name

      flag_game = check_game(Game_name,buff_file);
      if(flag_game == 1)
	  break;
      else
	  printf("Wrong Input.\n\tSELECT GAME: ");
  }
  i=0;k=0;
  buff_srv[i++]='G';
  buff_srv[i++]='S';
  buff_srv[i++]=' ';

  for(;Game_name[k]!='\0';)
  {   
      buff_srv[i++]=Game_name[k++];
  }
  buff_srv[i]='\0';
//  printf("%s\n",buff_srv);
  
  bytes_sent = send(sockfd, buff_srv, strlen(buff_srv), 0);                                
//  printf("sent:%s\n",buff_srv);
// receiving "GS_R (m1,p1) (m2,p2)","GS_R No Incomplete Match","GS_R No Such Game.so QUIT"
  memset(buff_file,0,MAXLEN);
  recv_ret=recv(sockfd, buff_file,MAXLEN,0);
//  printf("rcvd:%s\n",buff_file);

  for( i=0,k=0;buff_file[k]!=' ';)
  {
      temp_buff[i++]=buff_file[k++];
  }
  temp_buff[i]='\0';
//  printf("temp_buff: %s\n",temp_buff);


//handling GS_R messages 
  char *match_asPlayer=NULL,*buff_file1=NULL;
  MID_n_MOVE *mid_n_move=NULL;
  int updation_flag=0;
  init_matrix(mat,3);
  if(strncmp(temp_buff,"GS_R",4)==0)
  {
      if((buff_file[5]=='N')&&(buff_file[8]=='I'))
      {
	  char chr;
	  //  printf("%s\n",buff_file);
	  printf("-------------------------------------------\n");
	  printf("|  No Match exist.So choose a New Match\n");
	  printf("-------------------------------------------\n");
	  printf("\tNEW MATCH?(Y/N): ");
	  while(1)
	  {
	      scanf("%c",&chr);
	      getchar();
	      if((chr=='Y')||(chr=='y'))
	      {
		  bytes_sent = send(sockfd,"MS 0 1",7, 0);      
		  break;}
	      else if((chr=='N')||(chr=='n')){
		  bytes_sent = send(sockfd, "QUIT",5, 0);
		  break;}
	      else
		  printf("Invalid input .Re-enter ur choice: ");
	  }
	  display_board(mat);
	  //updation_flag=0;
      }
      else
      {            

	  printf("\n-----------(TYPE,MATCH_ID,PL_1,PL_2)--------------\n\n");
	  mid_n_move=print_match_list(buff_file);
	  printf("\n\n--------------------------------------------------\n");
	  printf("\n\n\tSELECT(Match_Id Pl_no): ");

	  buff_file1=(char*)malloc(strlen(buff_file)+1);
	  memset(buff_file1,0,strlen(buff_file)+1);
	  strcpy(buff_file1,buff_file);

	  match_asPlayer=getstr();
//	  printf("%s\n",match_asPlayer);
	  //updation_flag=1;
	  update_match_board(buff_file1,mid_n_move,match_asPlayer); 
	  display_board(mat);
//padding "MS " with the selected match_ID	  
	  i=0;k=0;
	  buff_srv[i++]='M';
	  buff_srv[i++]='S';
	  buff_srv[i++]=' ';

	  for(;match_asPlayer[k]!='\0';)	     
	      buff_srv[i++]=match_asPlayer[k++];	  
	  buff_srv[i]='\0';

// sending "MS match_ID"
	  bytes_sent = send(sockfd, buff_srv, strlen(buff_srv), 0); 
//	  printf("C>sent:%s\n",buff_srv);	  
      }
  }

//receiving "MS_R STARTED..." "MS_R WAIT..." "MS_R No Incomplete Match with this match_ID"     
  memset(buff_file,0,200);
  recv_ret=recv(sockfd, buff_file,MAXLEN, 0);                  
//  printf("rcvd:%s\n",buff_file);
  for(i=0,k=0;buff_file[i]!=' ';){
      temp_buff[k] = buff_file[i];
      i++;k++;}
  temp_buff[k]='\0'; //should be "MS_R"

  i++; //cosuming space

  if(strncmp(temp_buff,"MS_R",4)==0)
  {
      for(k=0;buff_file[i]!='\0';){
	  temp[k] = buff_file[i];
	i++;k++;}
  }
  temp[k]='\0';   //" message without MS_R"
//  printf("%s\n",temp) ;  

  if(strncmp(temp,"WAIT...",7)==0)
  {
      printf("\n\n\tWAIT...\n");
      send(sockfd,"OK",3,0);

      memset(buff_file,0,200);
      recv_ret=recv(sockfd, buff_file,MAXLEN,0);//receiving "MS_R STARTED..."
//      printf("%s\n",(char*)(buff_file+5));
      for(i=0,k=0;buff_file[i]!=' ';)    
	  temp_buff[k++] = buff_file[i++];      
      temp_buff[k]='\0';
      i++;  //consuming space
      if(strncmp(temp_buff,"MS_R",4)==0)
      {
	  memset(temp,0,200);
	  for(k=0;buff_file[i]!='\0';)	  	  
	      temp[k++] = buff_file[i++];	  
	  temp[k]='\0';  //"STARTED..."	  
      }
      int j=0;
      if(strncmp(temp,"STARTED...",10)==0)
      {
	  printf("\n\n\tSTARTED...\n");
	  send(sockfd,"OK",3,0);
      }  
  }    
  else if(strncmp(temp,"STARTED...",10)==0)
  {
      printf("\n\n\tSTARTED...\n");
      send(sockfd,"OK",3,0);
  }
//Till now each player has received the STARTED message and init board has displayed


//******************NOW play start**************
//ACCEPTS MOVE
  int row_col[2],loop_flag=0;
  while(1)
  {
      memset(buff_file,0,200);
//      printf("hanging on recv()\n");
      recv_ret=recv(sockfd, buff_file,MAXLEN,0);
//      printf("rcvd:%db,%s: \n",recv_ret,buff_file);
      if(strncmp(buff_file,"M_R Enter your move",19)==0)
      {
	  printf("\n\tMOVE(r c): ");
	  
	  loop_flag=0;
	  while(1)
	  {//////make it correct
	      memset(temp,0,200);
	      temp = getstr();
	      //printf("User enterd:%s\n",temp);
	      temp=actual_move(temp);
	      //printf("actual_move:%s\n",temp);
	      if(!temp)
	      {
		  printf("\n\tVALID MOVE(r c): ");
		  continue;
	      }
	      memset(buff_srv,0,200);
	      if((temp[0]>'0')&&(temp[0]<'4'))
	      {//TTT specific
		  buff_srv[0]='M';
		  buff_srv[1]=' ';
		  buff_srv[2]='\0';		  
		  strcat(buff_srv,temp);
		  loop_flag=1;		      		  
	      }
	      else if((temp[0]=='P')||(temp[0]=='R')||(temp[0]=='S')||(temp[0]=='Q'))  
	      {
		  buff_srv[0]=temp[0];
		  buff_srv[1]='\0';
		  loop_flag=1;
	      }
	      else  printf("Invalid request.\n\tVALID MOVE(r c): ");
	      if(loop_flag) break;
	  }
	  //printf("move to send:%s\n",buff_srv);
	  
//sending "M r c"
	  bytes_sent = send(sockfd, buff_srv, strlen(buff_srv)+1, 0); 
	  //printf("bytes sent:%d,%s\n",bytes_sent,buff_srv);  //TESTING
      }

      else if(strncmp(buff_file,"M_R Invalid move",16)==0)
      {
	  printf("Invalid move.\n\tVALID MOVE(r c): ");	  
	  loop_flag=0;
	  while(1)
	  {//////make it correct
	      memset(temp,0,200);
	      temp = getstr();
	      //printf("User enterd:%s\n",temp);
	      temp=actual_move(temp);
	      //printf("actual_move:%s\n",temp);
	      if(!temp)
	      {
		  printf("\n\tVALID MOVE(r c): ");
		  continue;
	      }
	      memset(buff_srv,0,200);
	      if((temp[0]>'0')&&(temp[0]<'4'))
	      {//TTT specific
		  buff_srv[0]='M';
		  buff_srv[1]=' ';
		  buff_srv[2]='\0';		  
		  strcat(buff_srv,temp);
		  loop_flag=1;		      		  
	      }
	      else if((temp[0]=='P')||(temp[0]=='R')||(temp[0]=='S')||(temp[0]=='Q'))  
	      {
		  buff_srv[0]=temp[0];
		  buff_srv[1]='\0';
		  loop_flag=1;
	      }
	      else  printf("Invalid request.\n\tVALID MOVE(r c): ");
	      if(loop_flag) break;
	  }
	  //printf("move to send:%s\n",buff_srv);	  
	  bytes_sent = send(sockfd, buff_srv, strlen(buff_srv)+1, 0);
      }
      else if(!strcmp(buff_file,"S_R saved.Enter your move"))
      {
	  printf("SAVED.\n\tMOVE(r c): ");
	  loop_flag=0;
	  while(1)
	  {
	      memset(temp,0,200);
	      temp = getstr();
	      //printf("User enterd:%s\n",temp);
	      temp=actual_move(temp);
	      //printf("actual_move:%s\n",temp);
	      if(!temp)
	      {
		  printf("VALID MOVE(row col): ");
		  continue;
	      }
	      memset(buff_srv,0,200);
	      if((temp[0]>'0')&&(temp[0]<'4'))
	      {//TTT specific
		  buff_srv[0]='M';
		  buff_srv[1]=' ';
		  buff_srv[2]='\0';		  
		  strcat(buff_srv,temp);
		  loop_flag=1;		      		  
	      }
	      else if((temp[0]=='P')||(temp[0]=='R')||(temp[0]=='S')||(temp[0]=='Q'))  
	      {
		  buff_srv[0]=temp[0];
		  buff_srv[1]='\0';
		  loop_flag=1;
	      }
	      else  printf("Invalid request.\n\tVALID MOVE(r c): ");
	      if(loop_flag) break;
	  }
	  //printf("move to send:%s\n",buff_srv);
	  
	  bytes_sent = send(sockfd, buff_srv, strlen(buff_srv)+1, 0); 
	  //printf("bytes sent:%d,%s\n",bytes_sent,buff_srv);  //TESTING
      }
      else if(!strcmp(buff_file,"P_R Paused.Enter R to resume"))
      {
	  printf("PAUSED.\n\tEnter R to RESUME: ");
	  loop_flag=0;
	  while(1)
	  {
	      memset(temp,0,200);
	      temp = getstr();
	      //printf("User enterd:%s\n",temp);
	      temp=actual_move(temp);
	      //printf("actual_move:%s\n",temp);

	      if(!temp)	printf("\n\tEnter R to RESUME: ");
	      else if(!strcmp(temp,"R")) loop_flag=1;
	      else printf("Invalid request.\n\tEnter R to RESUME: ");
	      if(loop_flag) break;
	  }
	  bytes_sent = send(sockfd,"R",2, 0);	  
      }
      else if(!strcmp(buff_file,"P_R Paused"))
      {
	  printf("PAUSED.So Wait...\n");
	  bytes_sent = send(sockfd,"OK",3, 0);
	  //printf("#@bytes sent:%d\n",bytes_sent);  //TESTING
      }
      else if(!strcmp(buff_file,"R_R Resumed.Enter your move"))
      {
	  printf("RESUMED...\n\tMOVE(r c): ");	  
	  loop_flag=0;
	  while(1)
	  {//////make it correct
	      memset(temp,0,200);
	      temp = getstr();
	      //printf("User enterd:%s\n",temp);
	      temp=actual_move(temp);
	      //printf("actual_move:%s\n",temp);
	      if(!temp)
	      {
		  printf("\n\tVALID MOVE(r c)");
		  continue;
	      }
	      memset(buff_srv,0,200);
	      if((temp[0]>'0')&&(temp[0]<'4'))
	      {//TTT specific
		  buff_srv[0]='M';
		  buff_srv[1]=' ';
		  buff_srv[2]='\0';		  
		  strcat(buff_srv,temp);
		  loop_flag=1;		      		  
	      }
	      else if((temp[0]=='P')||(temp[0]=='R')||(temp[0]=='S')||(temp[0]=='Q'))  
	      {
		  buff_srv[0]=temp[0];
		  buff_srv[1]='\0';
		  loop_flag=1;
	      }
	      else  printf("Invalid request.\n\tVALID MOVE(r c): ");
	      if(loop_flag) break;
	  }
	  //printf("move to send:%s\n",buff_srv);
	  
//sending "M r c"
	  bytes_sent = send(sockfd, buff_srv, strlen(buff_srv)+1, 0); 
	  //printf("bytes sent:%d,%s\n",bytes_sent,buff_srv);  //TESTING
      }
      else if(!strcmp(buff_file,"R_R Resumed"))
      {
	  printf("RESUMED...\n");
	  bytes_sent = send(sockfd,"OK",3, 0);
	  //printf("##bytes sent:%d\n",bytes_sent);  //TESTING
      }
      else if(!strcmp(buff_file,"Q_R Stopped"))
      {
	  printf("Match Stopped\n");
	  exit(1);
      }
      else if((strlen(buff_file)==7)&&(buff_file[0]=='M'))
      {//Update board
	  symbol=buff_file[2];
	  mat[buff_file[4]-49][buff_file[6]-49]=symbol;
/* 	  row_col[0]=buff_file[4]-48; */
/* 	  row_col[1]=buff_file[6]-48; */
	  //printf("rcv:%s & going to display board\n",buff_file);
	  display_board(mat);	
	  bytes_sent = send(sockfd, "OK", 3 , 0); 
      }
      else if((buff_file[0]=='W')||(buff_file[0]=='T'))
      {
	  symbol=buff_file[2];
	  mat[buff_file[4]-49][buff_file[6]-49]=symbol;
/* 	  row_col[0]=buff_file[4]-48; */
/* 	  row_col[1]=buff_file[6]-48; */
	  display_board(mat);	//Update board

	  for(m=0,i=8;buff_file[i]!='\0';)
	      winner_statement[m++]=buff_file[i++];
	  winner_statement[m]='\0';
	  break;
      }
  }
  printf("%s\n",winner_statement);
  close(sockfd);
  
}

void extract_games(char *buff_file)
{
  int i=0;
  while(buff_file[i]!=' ')
    i++;  
  i++;

  for(;buff_file[i]!='\0';i++)
  {
      if(buff_file[i]==' ') printf(" ");//printf("\n");
      else printf("%c",buff_file[i]);
  }
  //printf("\n"); 

}

int check_game(char *Game_name,char *buff_file)
{
    int i=0,k=0,flag=0;   
    while(buff_file[i]!=' ')
	i++;
    i++;
    while(buff_file[i]!='\0')
    {
	flag=1;
	k=0;
	if(buff_file[i++] == Game_name[k++])
	{
	    while((buff_file[i]!= ' ' )&&(buff_file[i]!= '\0' ))
	    {		
		if(buff_file[i] != Game_name[k])		
		    flag =0;			       		
		i++;
		k++;		
	    }   
	    if(flag==1)
	    {
		if(Game_name[k] == '\0')
		    return 1;
		else 
		{
		    if(buff_file[i]== '\0')
			return 0;		    
		}
	    }	    
	    i++;
	}	
    }    
}
MID_n_MOVE* print_match_list(char *buff_file)
{
    MID_n_MOVE *head=NULL,*t1=NULL;
    char *temp=malloc(Max_Len_PlName+1);
    int i=0,k=0;
    //printf("buff_file:%s\n",buff_file);
    
    i=6;
    while(1)
    {
	if(buff_file[i]=='I') printf("  INCOM\t");
	else if(buff_file[i]=='S') printf("  SAVED\t");
	i+=2;
	for(k=0;buff_file[i]!=' ';i++)//match_ID
	    temp[k++]=buff_file[i];
	temp[k]='\0';
	printf("\t%s",temp);
	i+=2;
	///////////////////////////////list work
	t1=(MID_n_MOVE*)malloc(sizeof(MID_n_MOVE));	    
	t1->MID=atoi(temp);	
        /////////////////////
	while(1)
	{
	    for(k=0;(buff_file[i]!=',')&&(buff_file[i]!=')');i++)//player's name
		temp[k++]=buff_file[i];
	    temp[k]='\0';
	    printf("\t\t%s",temp);
	    if(buff_file[i]==')') break;
	    i++;
	}

	///////////////////////list work
	t1->index_in_buff_file=i+3;
	t1->next_MID_n_MOVE=head;
	head=t1;
        //////////////////////

	for(;(buff_file[i]!='[')&&(buff_file[i]!='\0');i++);
	if(buff_file[i]=='\0') break;
	else i++;
	printf("\n");
/* 	for(;(buff_file[i]!='[')&&(buff_file[i]!='\0');i++) //printf("%c",buff_file[i]); */
/* 	if(buff_file[i]=='\0')  break; */
/* 	else    i+=3; */
    }
    return head;
}

/* void print_match_list(char *buff_file) */
/* { */
/*     char *temp=malloc(Max_Len_PlName+1); */
/*     int i=0,k=0; */
/*     printf("buff_file:%s\n",buff_file); */
/*     i=8; */
/*     while(1) */
/*     { */
/* 	for(k=0;buff_file[i]!=' ';i++)//match_ID */
/* 	    temp[k++]=buff_file[i]; */
/* 	temp[k]='\0'; */
/* 	printf("\n%s",temp); */
/* 	i+=2; */
    
/* 	while(1) */
/* 	{ */
/* 	    for(k=0;(buff_file[i]!=',')&&(buff_file[i]!=')');i++)//player's name */
/* 		temp[k++]=buff_file[i]; */
/* 	    temp[k]='\0'; */
/* 	    printf("\t\t%s",temp); */
/* 	    if(buff_file[i]==')') break; */
/* 	    i++; */
/* 	} */
/* 	printf("\n"); */
/* 	for(;(buff_file[i]!='[')&&(buff_file[i]!='\0');i++) printf("%c",buff_file[i]); */
/* 	if(buff_file[i]=='\0')  break; */
/* 	else    i+=3; */
/*     } */
/* } */
int check_game_id(char *Game_id,char *buff_file)
{
    
    int i=0,k=0,flag=0;   
    while(buff_file[i]!=' ')
	i++;
    i++;
    while(buff_file[i]!='\0')
    {
	flag=1;
	k=0;
	if(buff_file[i++] == '(') 
	{
	    while(buff_file[i] != ',')
	    {
		if(buff_file[i] != Game_id[k])
		    flag =0;
		i++;k++;
	    }
	    if(flag == 1)
	    {
		if(Game_id[k] == '\0')
		    return 1;
		else 
		    flag =0;
	    }
	    while(buff_file[i]!= ')')
		i++;
	}
	if(buff_file[i] == ' ')
	    i++;
    }
    return 0;
}
  
char* getstr()
{
    int i=0;
    char c='\0';
    char* res=malloc(MAXLEN);
    memset(res,0,MAXLEN);
    while((c=getchar())!='\n')
	res[i++]=c;
    res[i]='\0';
    return res;
}

void init_matrix(char **mat,int size)
{
    int i=0,j=0;
    for(i=0;i<size;i++)
	for(j=0;j<size;j++)
	    mat[i][j]=' ';
}
/*     printf("\n"); */
/*     for(i=0;i<3;i++) */
/*     { */
/* 	printf("\t\t"); */
/* 	printf(" %c | %c | %c ",mat[i][0],mat[i][1],mat[i][2]); */
/* 	if(i != 2) */
/* 	    printf("\n\t\t---|---|---\n"); */
/*     } */
/*     printf("\n"); */


void display_board(char ** mat)
{
  int i;
  //printf("disp_bord fun:(%d,%d),%c\n",move[0],move[1],symbol);
  //mat[move[0]-1][move[1]-1]=symbol;
  system("clear");
  printf("\n\n\n\n\n");
  for(i=0;i<3;i++)
    {
	printf("\t\t\t\t");
	printf(" %c | %c | %c ",mat[i][0],mat[i][1],mat[i][2]);
	if(i != 2)
	    printf("\n\t\t\t\t---|---|---\n");
    }
  printf("\n");
}
char *actual_move(char* string)
{
    int i=0,j=0;
    char* result=malloc(6);
    for(i=0;string[i]==' ';i++);
    j=0;
    result[j++]=string[i++];
    if((string[i-1]=='P')||(string[i-1]=='R')||(string[i-1]=='S')||(string[i-1]=='Q'))
    {
	result[j]='\0';
	return result;
    }
    else
    {
	result[j++]=' ';
	//printf("%dlength string::%s\n",strlen(string),string);
	while(string[i]!='\0')
	{
	    while(string[i]==' ') i++;
	    if(string[i]=='\0')
	    {
		//printf("1.bug\n");
		return NULL;
	    }
	    else
	    {
		result[j++]=string[i++];
		result[j]='\0';
		while(string[i]==' ') i++;
		if(string[i]=='\0')	    
		    return result;	    
		else 
		{		
		    //printf("3.bug(%c,%c)\n",string[i-1],string[i]);
		    return NULL;
		}
	    }
	}
	//printf("4.bug\n");
	return NULL;
    }
}

void update_match_board(char *buff_file,MID_n_MOVE *xyz,char *match_asPlayer)
{
    int i=0,k=0;
    char *t=NULL;
    MID_n_MOVE *temp=NULL;//assuming the length of any move is at max 24 bytes
    for(temp=xyz;temp;temp=temp->next_MID_n_MOVE)
    {
	t=itoa(temp->MID);
	if(!strncmp(match_asPlayer,t,strlen(t))) break;
    }
    //printf("xyz:%d,%d\n",xyz->MID,xyz->index_in_buff_file);
    if(!temp) printf("Invalid choice\n");
    else
    {
	i=temp->index_in_buff_file;
	//printf("temp:%d,%d\n",temp->MID,temp->index_in_buff_file);
	while(buff_file[i]!=')')
	{
	    mat[buff_file[i+4]-49][buff_file[i+6]-49]=buff_file[i+2];
	    if(buff_file[i+7]==')') break;
	    i+=8;
	    //printf("hi\n");
//	    for(;(buff_file[i]!=')')&&(buff_file[i]!=',');i++);

	}
    }	
}
char* itoa(int value)
{
    int x=1,num=0,i=0,j=0,k=0;
    char *str=NULL;
    if(value==0) return "0";
    if(value<0)
    {
	value*=-1;;
	k=1;
    }
    else k=0;
    for(i=0;value/x!=0;i++)
    {
	x=x*10;
    }
    str=(char*)malloc(i+2);  
    num=10;
    for(j=i-1;j>=0;j--)
    {
	str[j+k]=(value%num)+'0';
	value=value/10;      
    }
    str[i+k]='\0';
    if(k==1) str[0]='-';
    return str;
}
	
	
	


