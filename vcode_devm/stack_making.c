#include <stdio.h>
#include <stdlib.h>


#define max_stack 10


int checkmax(int stack_point){
    if(stack_point >= max_stack){

        printf("The stack is full");
        return 0;
    }
}

void push(int *stack_point,int value,int stack[]){

    stack[*stack_point] = value;

    *stack_point = (*stack_point)+1;

}


// void pop{


// }


int main(){


// int stack[10] = {1,2};

// int stack_point = 3;



// checkmax(stack_point);


// push(&stack_point,3,stack);


// for (int i = 0 ; i < stack_point; i ++){


//     printf("%d",stack[i]);
// }

for(int i = 0 ; i < 1000000; i++){

    printf("|");
    printf("/");
    printf("|");
    printf("\\");
    
}


}
