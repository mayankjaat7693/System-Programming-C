#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
int main()
{
int **ptr2ptr;
int *ptr2sizes;
int i,j;
int how_many_collections;
printf("Enter how many collection you maintain: ");
scanf("%d",&how_many_collections);
__fpurge(stdin);
if(how_many_collections<=0)
{
printf("Invalid requirement\n");
return 0;
}
ptr2ptr=(int **)malloc(sizeof(int *)*how_many_collections);
if(!ptr2ptr){
printf("Low Memory\n");
return 0;
}
ptr2sizes=(int *)malloc(sizeof(int)*how_many_collections);
if(!ptr2sizes){
printf("Low Memory\n");
return 0;
}
for(i=0;i<how_many_collections;i++)ptr2ptr[i]=NULL;
for(i=0;i<how_many_collections;i++){
printf("Enter size of collection number %d\n",i+1);
scanf("%d",&ptr2sizes[i]);
__fpurge(stdin);
ptr2ptr[i]=(int *)malloc(sizeof(int)*(ptr2sizes[i]));
if(!ptr2ptr[i]){
printf("Low Memory\n");
break;
}
}
if(i<how_many_collections){
for(j=0;j<i;i++)free(ptr2ptr[j]);
free(ptr2ptr);
free(ptr2sizes);
return 0;
}
printf("feed data for %d collection numbers\n",how_many_collections);
for(i=0;i<how_many_collections;i++)
{
printf("data feed for collection number %d\n",i+1);
for(j=0;j<ptr2sizes[i];j++)
{
printf("Enter a number : ");
scanf("%d",&(ptr2ptr[i][j]));
__fpurge(stdin);
}
}

printf("feeded data print\n");
for(i=0;i<how_many_collections;i++)
{
printf("collection number %d\n",i+1);
for(j=0;j<ptr2sizes[i];j++)
{
printf("%d   ",ptr2ptr[i][j]);
}
printf("\n");
}
printf("cleaning up everything\n");
for(i=0;i<how_many_collections;i++)free(ptr2ptr[i]);
free(ptr2ptr);
free(ptr2sizes);
return 0;
}
