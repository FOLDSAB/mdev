#include <stdio.h>
#include <stdlib.h>

int main(){

int arr[]={1,2,3,4,5,6,7,8,9,0};


int n = -1;
int  temp[10];
for (int i = 2; i <= ((sizeof(arr)/4)); i++){
    n++;

    temp[n] = arr[i];
    printf("The n is %d\n",n);
    
}



for (int j = 0 ; j <= 1; j++){


temp[n] = arr[j];
printf("the aj is: %d\n",arr[j]);
printf("The n is %d\n",n);
n++;

}

for (int k = 0; k < 10; k++){
    printf("%d\n",temp[k]);
}


}