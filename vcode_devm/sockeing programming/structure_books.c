#include <stdio.h>
#include <stdlib.h>


typedef struct  books
{
    char title[40];
    char author[20];
    float price;
}book;

int cheapfinder(book *self){

    float small = self[0].price;

    for(int i = 0 ; i < 3; i ++){

        if(small > self[i].price){
            
            small = self[i].price;
        }
    }

    return small;
}

int main(){


book self[3];


for (int i = 0 ; i < 3 ; i++){

    printf("please enter the Title of the book: ");
    scanf(" %s",&self[i].title);

    // printf("The name of the book is %s\n",self[i].title);

    printf("Please enter the author of the book: ");
    scanf(" %s",&self[i].author);


    printf("Please enter the price of the book: ");
    scanf("%f",&self[i].price);
}


float cheapest = cheapfinder(self);


for(int i = 0 ; i < 3; i++){

    if(cheapest == self[i].price){
        printf("The name of the cheapest book is %s\n",self[i].title);
        printf("author: %s\n",self[i].title);
        printf("price:  %.2f",self[i].price);
    }
}




}