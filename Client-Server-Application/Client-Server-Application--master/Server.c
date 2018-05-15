#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 //
//void  Clientservice(char*[] command);
int main(int argc , char *argv[])
{
    int socket_desc , client_sock ,c , read_size,file;
    struct sockaddr_in server , client;
    char client_message[2000],buff,ch;
   int fd,fd1,c1=0,b;
  fpos_t pos;
fgetpos(stdout,&pos);
    pid_t childpid;    
    if(argc!=2) 
    {
	printf("run program like: program_name port_numebr");
    }
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( atoi(argv[1]) );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
while(1)
	{     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
       exit(1);
  

   printf("connection accepted from %s: %d \n ", inet_ntoa(client.sin_addr),ntohs(client.sin_port));

     if((childpid=fork())==0)
		{
			dup2(client_sock,socket_desc);
            		fflush(stdin);
		    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    			{
        //Send the message back to client
        puts(client_message);
        file = open("Result_N.txt", O_CREAT|O_WRONLY, S_IRWXU);
       int save_out1=dup(fileno(stdout));
        dup2(file,fileno(stdout));
        system(client_message);
        fflush(stdout);
       close(file);
  
        dup2(save_out1,fileno(stdout));
    close(save_out1);
printf("back");
printf("home");

fflush(stdout);
printf("%s",client_message);
fflush(stdout);
fflush(stdin);
fd=open("Result_N.txt",O_RDONLY);
if(fd==-1)
printf("file opening problem");
else
printf("file open");
lseek(fd,0L,SEEK_SET);
printf("ert");
  while((b=read(fd,&buff,1))==1)
      {
           c1++;
         
          printf("%c",buff);
        write(client_sock,buff,strlen(buff));
      }
        //write(client_sock , buff , strlen(buff));

    }
}

     
}  
close(fd);
}


