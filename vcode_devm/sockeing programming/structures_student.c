#include <stdio.h>
#include <stdlib.h>


typedef struct  student
{
    char name[30];
    int age;
    int marks;
}stdnt;



int average(stdnt *std){

float avg = (std[0].marks+std[1].marks)/2;



printf("The marks of the student 0 is %.2f",avg);

}
int main(){


stdnt st1[2];


char names[20];
for (int i = 0 ; i < 2 ; i ++){


    // printf("please Enter the name of Student%i: ",i); 
    // scanf(" %s",names);
    
    printf("please Enter the age of Student%i: ",i); 
    scanf("%d",&st1[i].age);
    
    printf("please Enter the marks of Student%i: ",i); 
    scanf("%d",&st1[i].marks);
    
}

// st1[0].marks = 3;
// st1[1].marks = 3;


average(st1);



}