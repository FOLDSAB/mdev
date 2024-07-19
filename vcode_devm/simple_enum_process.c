// Write a function that takes an array of integers and its size as parameters and returns the sum of all the elements in the array.
// Implement a function that takes an array of integers and its size as parameters and returns the maximum value in the array.


#include <stdio.h>
#include <stdlib.h>




int func(int arr[]){


int sum = 0;


for(int i =0 ; i <7; i++){



sum += arr[i];

}

printf("The sum is %d\n",sum);



}


int func_max(int arr[]){

    int max = arr[0];

    for(int i = 0 ; i<7; i++){

        if(max < arr[i]){

            max = arr[i];
        }

        
    }

    printf("The max is %d\n",max);
}


int func_vlue(int arr[]){

     arr[2]=5;
}

int func_char(char **arr){

    arr[0]="hell";
}
int main(){



int arr[] ={1,2,3,4,9,6,7};



char *carr[] ={"abcd","bcdef"};

func(arr);
func_max(arr);
func_vlue(arr);
func_char(carr);
printf("The arr[2] is :%d\n",arr[2]);

printf("%s",carr[0]);
    
}