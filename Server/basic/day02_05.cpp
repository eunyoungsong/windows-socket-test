/* day02 유니온 : 공용체 */
#include <stdio.h>

struct B {
    union{
        struct{int a;}A;
        struct{char a,b,c,d;}B;
        struct{short a,b;}C;
        float a;
    }UN;
};

int main(){
    struct B te;
    te.UN.A.a = 100;
    printf("size : %d\n", sizeof(te));
    printf("%d\n", te.UN.A.a);
    return 0;
}