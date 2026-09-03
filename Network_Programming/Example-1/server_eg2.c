#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

int main()
{
struct addrinfo hints,*ptr2top_node,*t;
struct sockaddr_in *client_sockaddr_in;
struct sockaddr_storage client_sockaddr_storage;
int client_sockaddr_size,result;
int client_socket_descriptor,server_socket_descriptor;

memset(&hints,0,sizeof(hints));
hints.ai_family=AF_INET;
hints.ai_socktype=SOCK_STREAM;
hints.ai_flags=AI_PASSIVE;
result=getaddrinfo(NULL,"9696",&hints,&ptr2top_node);
if(result!=0)
{
printf("Error: %s\n",gai_strerror(errno));
return 0;
}
for(t=ptr2top_node;t!=NULL;t=t->ai_next)
{
server_socket_descriptor=socket(t->ai_family,t->ai_socktype,t->ai_protocol);
if(server_socket_descriptor==-1)continue;
result=bind(server_socket_descriptor,t->ai_addr,t->ai_addrlen);
if(result==-1)
{
close(server_socket_descriptor);
continue;
}
break;
}
freeaddrinfo(ptr2top_node);
if(t==NULL)
{
printf("Unable to Create Socket\n");
return 0;
}
result=listen(server_socket_descriptor,100);
if(result==-1)
{
printf("Unable to listen connection request\n");
return 0;
}
while(1)
{
client_sockaddr_size=sizeof(struct sockaddr_storage);
printf("Server is ready to accept connection on port 9696\n");
client_socket_descriptor=accept(server_socket_descriptor,(struct sockaddr *)&client_sockaddr_storage,&client_sockaddr_size);
if(client_socket_descriptor==-1)
{
printf("Unable to accept connection request\n");
printf("Error: %s\n",strerror(errno));
continue;
}
printf("Connection request arrived and accepted\n");
if(client_sockaddr_size<=sizeof(struct sockaddr_storage))
{
if(client_sockaddr_storage.ss_family==AF_INET)
{
client_sockaddr_in=(struct sockaddr_in *)&client_sockaddr_storage;
}
}
else 
{
printf("Unable to determine client IP/PORT\n");
}
close(client_socket_descriptor);
}
close(client_socket_descriptor);
return 0;
}
