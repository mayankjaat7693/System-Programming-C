#include<stdio.h>
#include<pthread.h>
void *sam(void*ptr)
{
int i;
for(i=1000;i<1100;i++)
{
printf("%d ",i);
}
return NULL;
}

int main()
{
int result;
pthread_t thread_id;
int x;
result=pthread_create(&thread_id,NULL,sam,NULL);
if(result==0)
{
printf("Create user thread\n");
}
else
{
printf("Unable to create user thread\n");
return 0;
}
for(x=1;x<30;x++)printf("%d ",x);
pthread_join(thread_id,NULL);
return 0;
}

