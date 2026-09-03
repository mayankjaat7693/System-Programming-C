#include<stdio.h>
#include<pthread.h>
struct data_wrapper
{
int num1;
int num2;
int sum;
};

void *do_something(void *ptr)
{
struct data_wrapper *t;
t=(struct data_wrapper *)ptr;
t->sum=t->num1+t->num2;
return NULL;
}

int main()
{
pthread_t thread_id;
struct data_wrapper k;
int st;
k.num1=10;
k.num2=20;
st=pthread_create(&thread_id,NULL,do_something,(void *)&k);
if(st!=0)
{
printf("Unable to create user thread\n");
return 0;
}
pthread_join(thread_id,NULL);
printf("Sum : %d\n",k.sum);
return 0;
}

