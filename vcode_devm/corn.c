
#include <stdio.h>
#include <stdlib.h>


int steps(int start){
int n = 0;
while(start!=1){
    if(start%2==0){
        start = start/2;
       
    }
    else if(start <= 0){
        return 3;
    }
    else{
        start = start*3;
      start = start+1;
    }
        n++;

    printf("%d\n",start);
}
return n;

}

int main(){

   int a = steps(-15);

   printf("total steps = %d\n",a);
}