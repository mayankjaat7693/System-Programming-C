#include<stdlib.h>
#include<stdio.h>
#include<stdio_ext.h>
typedef struct int_array
{
int sz;
int x[];
}INT_ARRAY;

int main()
{
INT_ARRAY **p2p;
int requirement;
int collection_size;
int i,j;
printf("Enter how many collection to maintain: ");
scanf("%d",&requirement);
__fpurge(stdin);
if(requirement<=0){
printf("Invalid requirement\n");
return 0;
}
p2p=(INT_ARRAY **)malloc(sizeof(INT_ARRAY *)*requirement);
if(!p2p){
printf("Low Memory\n");
return 0;
}
for(i=0;i<requirement;i++)p2p[i]=NULL;
for(i=0;i<requirement;i++){
printf("Enter size of collection number %d\n",i+1);
scanf("%d",&collection_size);
__fpurge(stdin);
if(collection_size<=0)
{
printf("invalid collection size %d",i+1);
break;
} 
p2p[i]=(INT_ARRAY *)malloc(sizeof(INT_ARRAY)+(sizeof(int)*collection_size));
if(!p2p[i]){
printf("Low Memory\n");
break;
}
p2p[i]->sz=collection_size;
}
if(i<requirement)
{
for(j=0;j<i;j++)free(p2p[j]);
free(p2p);
}
printf("feed data for %d number of colletion\n",requirement);
for(i=0;i<requirement;i++)
{
printf("feed data for collection number %d\n",i+1);
for(j=0;j<p2p[i]->sz;j++)
{
printf("Enter a number: ");
scanf("%d",&(p2p[i]->x[j]));
__fpurge(stdin);
}
}

printf("data for collection number");
for(i=0;i<requirement;i++)
{
printf("collection number %d\n",i+1);
for(j=0;j<p2p[i]->sz;j++)
{
printf("%d   ",p2p[i]->x[j]);
}
printf("\n");
}
printf("cleaning up everything\n");
for(i=0;i<requirement;i++)free(p2p[i]);
free(p2p);
return 0;
}
