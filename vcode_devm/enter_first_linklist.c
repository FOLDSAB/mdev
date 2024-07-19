#include <stdio.h>
#include <stdlib.h>


typedef struct _linklist
{
    int a;
    struct _linklist* next;
}linklist;

int main(){

int num;
printf("please enter the no of nodes: ");
scanf("%d",&num);
linklist *head = NULL;

for(int i = 0; i< num; i++){

linklist *first = (struct _linklist*)malloc(sizeof(struct _linklist));


// first->a = i;
first->next = head;
head = first;

}

linklist *current = head;

for(int i = 0; i< num;i++){

printf("Please enter the value %d: ",i);
scanf("%d",&current->a);
current = current->next;

}
    current = head;

// linklist *currents = head;
for(int i = 0 ; i < num; i++){
    printf("The value no %d: %d\n",i,current->a);
    current= current->next;
}

int insert;
printf("what do you want to insert at the first node: ");
scanf("%d",&insert);

linklist *insertion =  (struct _linklist*)malloc(sizeof(struct _linklist));

current = head;
insertion->a = insert;
insertion->next = current;

int k =0;
while(insertion != NULL){

    printf("The value %d: %d\n",k,insertion->a);
    insertion = insertion->next;
    k++;
}

}