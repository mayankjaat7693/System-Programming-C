#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<errno.h>

int main()
{
struct addrinfo hints,*ptr2top,*t;
int result,server_socket_descriptor;
memset(&hints,0,sizeof(hints));
hints.ai_family=AF_INET; // (IPv4)
hints.ai_socktype=SOCK_STREAM; //(TCP)
hints.ai_flags=AI_PASSIVE;  // Listen for any available IP in machine 
result=getaddrinfo(NULL,"9696",&hints,&ptr2top);
if(result!=0){
printf("Error %s\n",gai_strerror(errno));
return 0;
}
for(t=ptr2top;t!=NULL;t=t->ai_next)
{
server_socket_descriptor=socket(t->ai_family,t->ai_socktype,t->ai_protocol);
if(server_socket_descriptor==-1)continue;
result=bind(server_socket_descriptor,t->ai_addr,t->ai_addrlen);
if(result==-1)
{
close(server_socket_descriptor);
}
else 
{
break;
}
}
freeaddrinfo(ptr2top);
if(t==NULL)
{
printf("unavailable to create a socket\n");
return 0;
}
result=listen(server_socket_descriptor,100);
return 0;
}
