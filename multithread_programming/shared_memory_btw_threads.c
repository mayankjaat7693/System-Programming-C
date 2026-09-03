#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
struct data_wrapper
{
int number;
int *ptr;
};


void* do_something(void *p)
{
struct data_wrapper *t;
t=(struct data_wrapper *)p;
*(t->ptr)=t->number;
printf("kept : %d\n",*(t->ptr));
sleep(2);
printf("keeping whatever was kept: %d\n",*(t->ptr));
}


int main()
{
struct data_wrapper dw1,dw2,dw3;
pthread_t t1,t2,t3;
int st;
int common_place;
dw1.ptr=&common_place;
dw1.number=101;

dw2.ptr=&common_place;
dw2.number=102;

dw3.ptr=&common_place;
dw3.number=103;

st=pthread_create(&t1,NULL,do_something,&dw1);
if(st!=0)
{
printf("Unable to create user thread\n");
exit(-1);
}
st=pthread_create(&t2,NULL,do_something,&dw2);
if(st!=0)
{
printf("Unable to create user thread\n");
exit(-1);
}
st=pthread_create(&t3,NULL,do_something,&dw3);
if(st!=0)
{
printf("Unable to create user thread\n");
exit(-1);
}
pthread_join(t1,NULL);
pthread_join(t2,NULL);
pthread_join(t3,NULL);
return 0;
}
