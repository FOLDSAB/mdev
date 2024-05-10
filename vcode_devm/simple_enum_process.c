#include <stdio.h>
#include <stdlib.h>


int main(){


    char *arr[] ={"aaa","bbb","ccc","ddd"};

    char **parr = arr;


    printf("%s",parr[0]);


    char ***pparr = &parr;

    
}