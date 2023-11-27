#include<stdio.h>
#include "hello.h"
#include "my_math.h"


int main(){
    hello();
    printf("4 + 5 = %d\n",sum(4,5));

    return 0;
}