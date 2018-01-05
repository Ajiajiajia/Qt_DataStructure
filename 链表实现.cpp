#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#define OK 1;
#define ERROR 0;
using namespace std;

typedef int elemtype;
typedef struct LNode
{
elemtype password,num;
struct LNode *next;
} LNode,*Linklist;

void Creat_List(Linklist &L,int n)
{
LNode *p,*q;
L=(Linklist)malloc (sizeof(LNode));
L->num=1;
L->password=1;
p=L;
for (int i=2; i<=n; i++)
{
q=(Linklist)malloc(sizeof(LNode));
q->num=i;
q->password=i;
q->next=NULL;
p->next=q;
p=p->next;
}
p->next=L;//将整个链表首尾相接 
}


void YSF(Linklist &L,int n)
{
int  m,i,j,k;
LNode *p,*q,*r;
cout<<"请输入第一个出队列人员手中的数:";
cin>>m;
cout<<endl;
p=L;
if(m==1)
{
r=p;
while(r->next!=p)
{
r=r->next;
}
cout<<p->num<<" ";
k=p->password;
q=p;
r->next=r->next->next;
p=p->next;
free(q);
}
else
{
for(j=1; j<m-1; j++)
{
p=p->next;
}
q=p->next;
cout<<q->num<<" ";
k=q->password;
p->next=q->next;
p=p->next;
free(q);
}
for(i=2; i<=n-1; i++)
{
if(k==1)
{
r=p;
while(r->next!=p)
{
r=r->next;
}
cout<<p->num<<" ";
k=m;
q=p;
p=p->next;
r->next=r->next->next;
free(q);
}
else
{
for(j=1; j<k-1; j++)
{
p=p->next;
}
q=p->next;
cout<<q->num<<" ";
k=m;
p->next=q->next;
free(q);
p=p->next;
}
}
cout<<p->num;
}

int main ()
{

int i,j,k,m,n,o;
Linklist list;
cout<<"请输入人数：";
cin>>n;
Creat_List(list,n);
cout<<endl;
YSF(list,n);

return 0;
}
