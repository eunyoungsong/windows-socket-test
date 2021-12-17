/* day02 구조체 */
#include <stdio.h>

struct A{
    int a;
    int b;
};

struct B{
    struct A a;
    int b;
};

struct C{
    struct A a;
    struct B b; 
    int c;
};

int main(){
    struct C c;
    c.a.a = 40;
    c.a.b = 30;
    c.b.b = 20;
    c.c = 10;
    c.b.a.a = 10;
    c.b.a.b = 20;
    printf("%d, %d, %d, %d, %d, %d", c.a.a, c.a.b, c.b.b, c.c, c.b.a.a, c.b.a.b);
    return 0;
}