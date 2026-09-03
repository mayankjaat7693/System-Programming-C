// Usage ./client_eg1.out    ip_of_server_machine   port_of_server_socket   Massage.....
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<errno.h>

int main(int c,char *v[])
{
int client_socket_descriptor,result;
struct addrinfo hints,*ptr2top_node,*t;
char *ip_of_server_machine;
char *port_of_server_socket;

if(c!=4)
{
printf("Usage: ./client.out  IP_address_of_server   Port_number_server_socket   \"massage\"\n");
return 0;
}

ip_of_server_machine=v[1];
port_of_server_socket=v[2];
memset(&hints,0,sizeof(hints));
hints.ai_family=AF_INET;
hints.ai_socktype=SOCK_STREAM;
result=getaddrinfo(ip_of_server_machine,port_of_server_socket,&hints,&ptr2top_node);
if(result!=0)
{
printf("Error: %s\n",gai_strerror(errno));
return 0;
}
for(t=ptr2top_node;t!=NULL;t=t->ai_next)
{
client_socket_descriptor=socket(t->ai_family,t->ai_socktype,t->ai_protocol);
if(client_socket_descriptor==-1)continue;
result=connect(client_socket_descriptor,t->ai_addr,t->ai_addrlen);
if(result==-1)
{
close(client_socket_descriptor);
continue;
}
break;
}
if(t==NULL)
{
printf("Unable to connect to %s(%s)\n",ip_of_server_machine,port_of_server_socket);
return 0;
}
freeaddrinfo(ptr2top_node);
printf("Client Connection with server establish\n");
close(client_socket_descriptor);
return 0;
}
