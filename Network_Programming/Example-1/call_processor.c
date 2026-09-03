#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define st_type unsigned int 
#define ST_INDIAN 1
#define ST_AMERICAN 2
#define ST_OTHER 3
typedef struct student
{
st_type student_type;
char data[];
}student;

typedef struct indian_student 
{
st_type student_type;
char aadhaar_number[17];
}indian_student;

typedef struct american_student
{
st_type student_type;
char social_security_identification_number[10];
}american_student;

typedef struct other_student
{
st_type student_type;
char national_identification_number[101];
char country_name[51];
}other_student;

student *queue[5];
int front;

void populated_queue()
{
indian_student *i_student;
american_student *a_student;
other_student *o_student;

i_student=(indian_student *)malloc(sizeof(indian_student));
i_student->student_type=ST_INDIAN;
strcpy(i_student->aadhaar_number,"3372815017913893");
queue[0]=(student *)i_student;

o_student=(other_student *)malloc(sizeof(other_student));
o_student->student_type=ST_OTHER;
strcpy(o_student->national_identification_number,"12345678987655432213");
strcpy(o_student->country_name,"SOUTH AFRICA");
queue[1]=(student*)o_student;

i_student=(indian_student *)malloc(sizeof(indian_student));
i_student->student_type=ST_INDIAN;
strcpy(i_student->aadhaar_number,"1234123412341234");
queue[2]=(student*)i_student;

a_student=(american_student *)malloc(sizeof(american_student));
a_student->student_type=ST_AMERICAN;
strcpy(a_student->social_security_identification_number,"987654321");
queue[3]=(student*)a_student;

o_student=(other_student *)malloc(sizeof(other_student));
o_student->student_type=ST_OTHER;
strcpy(o_student->national_identification_number,"1234987643216789019283");
queue[4]=(student*)o_student;

front=0;
}

void released_queue()
{
int i;
for(i=0;i<=4;i++)free(queue[i]);
}

void get_next_caller_information(student *s,int *ptr2block_with_reservation_size)
{
student *student_from_queue;
int size_of_record_to_reserve;
int size_of_reservation_done_by_user;
student_from_queue=queue[front];
size_of_reservation_done_by_user=*ptr2block_with_reservation_size;
if(student_from_queue->student_type==ST_INDIAN)
{
size_of_record_to_reserve=sizeof(indian_student);
}
if(student_from_queue->student_type==ST_AMERICAN)
{
size_of_record_to_reserve=sizeof(american_student);
}
if(student_from_queue->student_type==ST_OTHER)
{
size_of_record_to_reserve=sizeof(other_student);
}
if(size_of_record_to_reserve==size_of_reservation_done_by_user)
{
memcpy(s,student_from_queue,size_of_record_to_reserve);
*ptr2block_with_reservation_size=size_of_record_to_reserve;
}
if(size_of_record_to_reserve<size_of_reservation_done_by_user)
{
memcpy(s,student_from_queue,size_of_record_to_reserve);
*ptr2block_with_reservation_size=size_of_record_to_reserve;
}
if(size_of_record_to_reserve>size_of_reservation_done_by_user)
{
memcpy(s,student_from_queue,size_of_reservation_done_by_user);
*ptr2block_with_reservation_size=size_of_record_to_reserve;
}
front++;
}

int main()
{
other_student record;
indian_student *indian;
american_student *american;
int orignal_size;
int update_size;
int i;
st_type student_type;

populated_queue();
for(i=1;i<=5;i++)
{
orignal_size=sizeof(record);
update_size=orignal_size;
get_next_caller_information((student *)&record,&update_size);
printf("coller number %d\n",i);
if(update_size<=orignal_size)
{
student_type=record.student_type;
if(student_type==ST_INDIAN)
{
indian=(indian_student*)&record;
printf("Indian Student Calling...\n");
printf("Aadhaar Number: %s\n",indian->aadhaar_number);
}
if(student_type==ST_AMERICAN)
{
american=(american_student*)&record;
printf("American Student Calling...\n");
printf("Social Security Identification Number: %s\n",american->social_security_identification_number);
}
if(student_type==ST_OTHER)
{
printf("Either Not Indian or American student calling...\n");
printf("Country Name: %s\n",record.country_name);
printf("National Idetification Number: %s\n",record.national_identification_number);
}
}
if(update_size>orignal_size) 
{
printf("information is incomplete\n");
}
printf("----------------------------------------\n");
}
released_queue();
return 0;
}





