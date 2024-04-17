#include <stdio.h>
#include <stdlib.h>

typedef struct structure {
    int a;
    int b;
    char c[];
} ssstruck;

int prfunction(int *a, int *b){
    
    printf("called function prfunction");
    *a = 888;
    *b = 888;

    printf("%d,%d\n",a,b);

}
int main() {
    printf("hello world\n");

    ssstruck struc;
    ssstruck *pstruc = &struc;
    ssstruck *ppsturc = malloc(sizeof(ssstruck)); // Allocate memory for ppsturc

    if (ppsturc == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit with failure status
    }

    ppsturc->a = 3;
    pstruc->a = 4;

// printf("%d",ppsturc->a);
    int c = 3;
    int *d = &c;

    printf("%d\n", c); 
    printf("%d",*d);
    free(ppsturc); 

    prfunction(d,d);

    printf(" after calling %d",*d);
    // printf("%d")
    return 0;
}
