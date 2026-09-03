#include<stdio.h>
#include<pthread.h>
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
return NULL;
}

int main()
{
int i;
int result;
struct data_wrapper s;
pthread_t thread_id;
s.num1=10;
s.num2=20;
result=pthread_create(&thread_id,NULL,sum,&s);
if(result!=0)
{
printf("Unable to create user thread\n");
return 0;
}
for(i=1;i<=5;i++)printf("%d\n",i);
pthread_join(thread_id,NULL);
return 0;
}

