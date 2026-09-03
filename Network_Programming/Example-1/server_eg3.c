#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>

int main()
{
struct addrinfo hints,*ptr2top_node,*t;
struct sockaddr_storage client_sockaddr_storage;
struct sockaddr_in *client_sockaddr_in;
int result,server_socket_descriptor,client_socket_descriptor;
char client_ip[16];
short unsigned int client_port;
socklen_t client_sockaddr_storage_size;
ssize_t bytes_sent,bytes_received;
size_t response_data_size;
size_t request_data_size;
char *request_data;
char response_data[1025];

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
printf("Unable to create socket\n");
close(server_socket_descriptor);
return 0;
}
result=listen(server_socket_descriptor,100);
if(result==-1)
{
printf("Unable to listen connection request\n");
printf("Error: %s\n",strerror(errno));
close(server_socket_descriptor);
return 0; 
}
while(1)
{
printf("Server ready to connection request on port 9696\n");
client_sockaddr_storage_size=sizeof(struct sockaddr_storage);
client_socket_descriptor=accept(server_socket_descriptor,(struct sockaddr *)&client_sockaddr_storage,&client_sockaddr_storage_size);
if(client_socket_descriptor==-1)
{
printf("Unable to accept connection request\n");
printf("Error: %s",strerror(errno));
continue;
}
if(client_sockaddr_storage_size<=sizeof(struct sockaddr_storage))
{
if(client_sockaddr_storage.ss_family==AF_INET)
{
client_sockaddr_in=(struct sockaddr_in *)&client_sockaddr_storage;
strcpy(client_ip,inet_ntoa(client_sockaddr_in->sin_addr));
client_port=ntohs(client_sockaddr_in->sin_port);
printf("Client IP/PORT: %s(%u)\n",client_ip,client_port);
}
}
else
{
printf("Unable to determine client ip/port\n");
printf("Error: %s\n",strerror(errno));
}
bytes_received=recv(client_socket_descriptor,request_data,request_data_size,0);
if(bytes_received==0)
{
if(errno==EINTR)
{
printf("Receiving interrupted\n");
}
else
{
printf("Unable to receiving request data\n");
printf("Error: %s\n",strerror(errno));
}
}
if(bytes_received>0)
{
request_data[bytes_received]='\0';
printf("Receiving data is as follows\n");
printf("%s\n",request_data);
}
strcpy(response_data,"THANK YOU!!! MAYANK JAAT");
response_data_size=strlen(response_data);
bytes_sent=send(client_socket_descriptor,response_data,response_data_size,0);
if(bytes_sent==0)
{
printf("Connection is closed by peer\n");
}
if(bytes_sent==-1)
{
if(errno==EINTR)
{
printf("sending interrupted\n");
}
else 
{
printf("Unable to sending data\n");
printf("Error: %s\n",strerror(errno));
}
}
if(bytes_sent<response_data_size)
{
printf("Unable to sending all data\n");
}
if(bytes_sent==response_data_size)
{
printf("data sending is as follows\n");
printf("%s\n",response_data);
}
close(client_socket_descriptor);
}

close(server_socket_descriptor);
return 0;
}
