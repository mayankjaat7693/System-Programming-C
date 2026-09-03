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
int b=101;
int i;
int result;
for(i=0;i<=4;i++)
{
result=pthread_create(&thread_id[i],NULL,do_something,(void *)&b);
if(result!=0)
{
printf("Unable to create user thread\n");
return 0;
}
b++;
}
for(i=0;i<=4;i++)pthread_join(thread_id[i],NULL);
return 0;
}
