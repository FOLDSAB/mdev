#include <stdio.h>
#include <stdlib.h>

typedef struct _stdnt
{
    int age;
}stdnt;


int findage(stdnt *student[]){

    student[0]->age = 3;

}

int main(){


stdnt *students[23];
    for(int i = 0 ; i < 23;i++){
        students[i] = (stdnt *)malloc(sizeof(students[0]));
    }

findage(students);
printf("%d",students[0]->age);




}


// #include <stdio.h>
// #include <stdlib.h>

// typedef struct _stdnt {
//     int age;
// } stdnt;

// void findage(stdnt *students[]) {
//     students[0]->age = 3;
// }

// int main() {
//     stdnt *students[23];


//     findage(students);
//     printf("%d", students[0]->age);
//     return 0;
// }
