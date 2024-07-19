#include <stdio.h>
#include <stdlib.h>

typedef struct something
{
    int a;
}some;


int func(some *s1){

    printf("%d",s1[0].a);

    s1[0].a = 5;
}


int func2 (some *s2){

printf(("%d"),*s2);

}
int main(){

some s1[10];

some s2;

some* ps2 = &s2;

ps2->a = 3;

s1[0].a = 3;

func(s1);
func2(ps2);

printf("%d",*s1);



}