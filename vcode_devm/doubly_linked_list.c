#include <stdio.h>
#include <stdlib.h>


typedef struct _dllist
{
    int a;
    struct _dllist *next;
    struct _dllist *prev; 
}dllist;


int main(){
dllist *head = NULL;


// creating the last node at the first ;
for(int i = 0 ; i < 3; i++){

dllist *list = (struct _dllist *)malloc(sizeof(struct _dllist));


list->next = head;
if(i == 2){
    list->prev = NULL;
}
else{
list->prev = list;

}
head = list;



}

for(int i = 0 ; i < 3; i ++){
    printf("%p\n",head->next);
    printf("The prev is %p\n",head->prev);  
    head = head->next;
}


}  