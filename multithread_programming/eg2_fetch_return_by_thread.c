#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
struct data_wrapper
{
int num1;
int num2;
};

struct result_wrapper
{
int sum;
int product;
};

void *do_something(void *ptr)
{
struct data_wrapper *t;
struct result_wrapper *v;
t=(struct data_wrapper *)ptr;
v=(struct result_wrapper *)malloc(sizeof(struct result_wrapper));
if(v!=NULL)
{
v->sum=t->num1+t->num2;
v->product=t->num1-t->num2;
return (void *)v;
}
else
{
return NULL;
}
}

int main()
{
struct result_wrapper *x;
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
pthread_join(thread_id,(void **)x);
printf("Sum : %d\n",x->sum);
printf("Product : %d\n",x->product);
free(x);
return 0;
}

