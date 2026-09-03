#include<stdio.h>
#include<pthread.h>
void *do_something(void *ptr)
{
int *t;
t=(int *)ptr;
printf("NUM: %d\n",*t);
return NULL;
}

int main()
{
pthread_t thread_id[5];
int b[5];
int i;
int result;
int number=101;
for(i=0;i<=4;i++)
{
b[i]=number;
result=pthread_create(&thread_id[i],NULL,do_something,(void *)&b[i]);
if(result!=0)
{
printf("Unable to create user thread\n");
return 0;
}
number++;
}
for(i=0;i<=4;i++)pthread_join(thread_id[i],NULL);
return 0;
}
