#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
char *ip_server_machine,*port_server_socket;
ssize_t bytes_sent,bytes_received;
size_t request_data_size,response_data_size;
int result,client_socket_descriptor;
struct addrinfo hints,*ptr2top_node,*t;
struct sockaddr_storage client_sockaddr_storage;
struct sockaddr_in *client_sockaddr_in;
struct sockaddr *client_sockaddr;
socklen_t client_sockaddr_storage_size;
char *request_data;
char response_data[1025];
char client_ip[16];
short unsigned int client_port;

if(argc!=4)
{
printf("Usage: ./client.out  IP_of_server_machine  Port_of_server_socket  Massage");
return 0;
}

memset(&hints,0,sizeof(hints));
hints.ai_family=AF_INET;
hints.ai_socktype=SOCK_STREAM;
ip_server_machine=argv[1];
port_server_socket=argv[2];

result=getaddrinfo(ip_server_machine,port_server_socket,&hints,&ptr2top_node);
if(result!=0)
{
printf("Error: %s\n",gai_strerror(errno));
return 0;
}
for(t=ptr2top_node;t!=NULL;t=t->ai_next)
{
client_socket_descriptor=socket(t->ai_family,t->ai_socktype,t->ai_protocol);
if(client_socket_descriptor==-1)
{
printf("Error: %s\n",strerror(errno));
continue;
}
result=connect(client_socket_descriptor,t->ai_addr,t->ai_addrlen);
if(result==-1)
{
printf("server connection descript\n");
continue; 
}
break;
}
freeaddrinfo(ptr2top_node);
if(t==NULL)
{
printf("Unable to connection with server\n");
close(client_socket_descriptor);
return 0;
}
printf("Client connection with server establish\n");
client_sockaddr_storage_size=sizeof(struct sockaddr_storage);
result=getsockname(client_socket_descriptor,(struct sockaddr *)&client_sockaddr_storage,&client_sockaddr_storage_size);
if(result==0)
{
if(client_sockaddr_storage_size<=sizeof(struct sockaddr_storage)){
client_sockaddr_in=(struct sockaddr_in *)&client_sockaddr_storage;
strcpy(client_ip,inet_ntoa(client_sockaddr_in->sin_addr));
client_port=ntohs(client_sockaddr_in->sin_port);
printf("Client IP/PORT: %s(%u)\n",client_ip,client_port);
}
}

strcpy(request_data,argv[3]);
request_data_size=strlen(request_data);
bytes_sent=send(client_socket_descriptor,request_data,request_data_size,0);
if(bytes_sent==0)
{
printf("Connection closed by peer\n");
}
if(bytes_sent==-1)
{
if(errno==EINTR)
{
printf("Sending interrupted\n");
}
else
{
printf("data is not sending\n");
printf("Error: %s\n",strerror(errno));
}
}
if(bytes_sent<request_data_size)
{
printf("all data not sending\n");
}
if(bytes_sent==request_data_size)
{
printf("data sending is as follow\n");
printf("%s\n",request_data);
}

bytes_received=recv(client_socket_descriptor,response_data,response_data_size,0);
if(bytes_received==-1)
{
if(errno==EINTR)
{
printf("Receiving interrupted\n");
}
else
{
printf("Unable to reciving data\n");
printf("Error: %s\n",strerror(errno));
}
}
if(bytes_received==0)
{
printf("Connection closed by peer\n");
}
if(bytes_received>0)
{
response_data[bytes_received]='\0';
printf("Receiving data is as following\n");
printf("%s\n",response_data);
}

close(client_socket_descriptor);
return 0;
}
