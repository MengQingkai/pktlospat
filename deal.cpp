#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#define SIZE 14400
#define N 1000
using namespace std;
char Str1[]=" TCP ";
char Str2[]="Seq=";
char Str3[]="Len=";
char Str4[]="[TCP Retransmission]";
char Str5[]="[TCP Previous segment not captured]";
char Str6[]="[TCP Out-Of-Order]";
char Str7[]="[TCP Fast Retransmission]";

struct Packet
{
  int type;
  int seq;
  int len;
  int flag;
}packet[N];

int char2num(char *p)
{
  int num=0,i;
  for(i=0;;i++)
  {
    if(p[i]>='0'&&p[i]<='9')
    {
      num=num*10+(p[i]-'0');
    }else break;
  }
  return num;
}

void print(int n)
{
  //printf("1\n");
  int i,flow=0;
  for(i=0;i<n;i++)
  {
    switch(packet[i].type)
    {
      case 0:packet[i].flag=0;if(packet[i].seq/SIZE==flow){printf("%d ",packet[i].flag);} else {printf("\n%d ",packet[i].flag); flow++;} break;
      case 1:packet[i].flag=1;if(packet[i].seq/SIZE==flow){printf("1 %d ",packet[i].flag);} else {printf("1 %d ",packet[i].flag); flow++;} break;
      case 2:packet[i].flag=1;if(packet[i].seq/SIZE==flow){printf("%d ",packet[i].flag);} else {printf("\n%d ",packet[i].flag); flow++;} break;
      case 3:packet[i].flag=0;if(packet[i].seq/SIZE==flow){printf("%d ",packet[i].flag);} else {printf("\n%d ",packet[i].flag); flow++;} break;
      case 4:packet[i].flag=1;if(packet[i].seq/SIZE==flow){printf("%d ",packet[i].flag);} else {printf("\n%d ",packet[i].flag); flow++;} break;
    }
  }
}

bool cmp(Packet A,Packet B)
{
  if(A.seq<B.seq)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int main()
{
  int i=0,num=0,length=0,n=0;
  char buf[500];
  FILE *fp=fopen("test_trans","r");
  while(fgets(buf,500,fp)!=NULL)//read one line
  {
     //printf("%s",buf);
     char *p=strstr(buf,Str1)+strlen(Str1);
     length=char2num(p);
     //printf("%d length:%d\n",i,num);
     //++i;
     if(length>100)//packet that have real data
     {

       if(strstr(buf,Str4)!=NULL){
         packet[n].type=0;// Re
       }else if(strstr(buf,Str5)!=NULL){
         packet[n].type=1;// need to add packet
       }else if(strstr(buf,Str6)!=NULL){
         packet[n].type=2;//order
       }else if(strstr(buf,Str7)!=NULL){
         packet[n].type=3;//Fast_re
       }else{
         packet[n].type=4;//normal
       }
       char *seq=strstr(buf,Str2)+strlen(Str2);
       packet[n].seq=char2num(seq);
       char *len=strstr(buf,Str3)+strlen(Str3);
       packet[n].len=char2num(len);
       n++;//packet + +
     }
  }

  sort(packet,packet+n-1,cmp);
//  for(i=0;i<n;i++)
//  {
//    printf("type:%d  seq:%d  len:%d\n",packet[i].type,packet[i].seq,packet[i].len);
//  }
  print(n);
  return 0;
}
