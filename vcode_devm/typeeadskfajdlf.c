#include <stdio.h>




void a(){
    printf("The function a is called");
}

void b( void (*ptr)()){

    printf("The function b is called\n");

    (*ptr)();

}

int main(){

void(*ptr)() = &a;

b(ptr);

}