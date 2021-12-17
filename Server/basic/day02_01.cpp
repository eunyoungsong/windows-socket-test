/* day02 구조체 */
#include <stdio.h>

struct A{
    int a;
    int b;
};

int main(){
    struct A a;
    a.a = 10; // . 구조체 접근연산자
    a.b = 20;
    printf("a.a = %d\na.b = %d\n", a.a, a.b);
    return 0;
} 