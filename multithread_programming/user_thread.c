#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
struct data_wrapper
{
int num1;
int num2;
};
void *sum(void *ptr)
{
int sum;
struct data_wrapper *p1;
p1=(struct data_wrapper *)ptr;
sum=p1->num1+p1->num2;
printf("Total is %d\n",sum);
free(ptr);
for(;sum<50;sum++)printf("%d ",sum);
return NULL;
}

void *sam(void *ptr)
{
struct data_wrapper *dw;
pthread_t thread_id;
int i,st;
dw=(struct data_wrapper *)malloc(sizeof(struct data_wrapper));
dw->num1=10;
dw->num2=20;
st=pthread_create(&thread_id,NULL,sum,dw);
for(i=101;i<120;i++)printf("%d ",i);
return NULL;
}

int main()
{
int i;
int result;
pthread_t thread_id;
result=pthread_create(&thread_id,NULL,sam,NULL);
if(result!=0)
{
printf("Unable to create user thread\n");
return 0;
}
for(i=1;i<20;i++)printf("%d ",i);
pthread_join(thread_id,NULL);
return 0;
}

