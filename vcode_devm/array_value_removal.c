#include <stdio.h>


int main(){

    int arr[]={0,1,2,3,4,5,99,6,7,8,9,0};

    int temp[11];


    int index = 7;

    int n = -1;

    for(int i = 0 ; i < (index-1) ; i++ ){
        n++;
        temp[n] = arr[i];
    }
    for(int j = (index);j <= 11;j++){
        n++;
        temp[n] = arr[j];
        printf("the aj is %d",arr[j]);

    }

    for(int k = 0; k < 11; k++ ){
        printf("%d ",temp[k]);
    }


    
}