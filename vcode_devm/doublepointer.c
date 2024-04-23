#include <stdio.h>
 
#define mac 80

#if mac < 200
#undef mac
#define mac 200

#elif mac < 1000
#undef mac 
#define mac 4000
#else 
#undef mac
#define mac 300
#endif





int main(){

    #ifdef mac
    #pragma message ("hello what is the pragma")
    #endif

    printf ("%d",mac);
}
