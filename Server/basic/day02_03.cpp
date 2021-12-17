/* day02 구조체 */
#include <stdio.h>
#include <string.h>

struct A{
    int a;
    char a_str[20];
};

struct B{
    struct A a;
    int b;
    char b_str[20];
};

int main(){
    struct B b;

    //b.a.a_str = "Hello"; 에러 strcpy 또는 sprintf 로 넣어주어 함.
    strcpy(b.a.a_str, "Hello");
    strcpy(b.b_str, "world");
    printf("%s %s\n", b.a.a_str, b.b_str);

    sprintf(b.b_str, "test");
    printf("%s\n", b.b_str);

    b.a.a = 10;
    b.b = 20;
    printf("%d %d", b.a.a, b.b);
    
    return 0;
}