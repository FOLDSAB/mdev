#include <stdio.h>
#include <stdlib.h>



typedef struct _linklist
{
    int a;
    struct _linklist *next;
}linklist;

int main(){

int num;
printf("please Enter the number of nodes: ");
scanf("%d",&num);
linklist *head = NULL;
linklist *abcd = NULL;

int count = 0;
for(int i = 0 ; i<num ; i++){

linklist *first = (struct _linklist *)malloc(sizeof(struct _linklist));


// printf("Please Enter the value %d: ",i);
// scanf(" %d",&first->a);

first->next = head;
head = first;
}

linklist *current = head;

for (int i = 0; i < num; i++)
{
    printf("please enter the value %d: ",i);
    scanf("%d",&current->a);
    current = current->next;
}

linklist *now = head;
for(int i=0 ; i < num ;i++){
    printf("The vlaue is %d: %d\n",i,now->a);
    now = now->next;
    count++;
}

printf("The count is %d",count);






}