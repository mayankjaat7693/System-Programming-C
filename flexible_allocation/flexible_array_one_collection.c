#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>

typedef struct int_array
{
int sz;
int x[];
}INT_ARRAY;

int main()
{
INT_ARRAY *p2p;
int requirement;
int i;
printf("Enter how many requiment you have: ");
scanf("%d",&requirement);
__fpurge(stdin);
if(requirement<=0)
{
printf("Invalid requirement\n");
return 0;
}
p2p=(INT_ARRAY*)malloc(sizeof(INT_ARRAY)*requirement);
if(!p2p){
printf("Low Memory\n");
return 0;
}
p2p->sz=requirement;
for(i=0;i<p2p->sz;i++)
{
printf("Enter number: ");
scanf("%d",&(p2p->x[i]));
__fpurge(stdin);
}
printf("Collect data\n");
for(i=0;i<p2p->sz;i++)
{
printf("%d   ",p2p->x[i]);
}
printf("\n");
printf("cleaning up everything\n");
free(p2p);
return 0;
}
