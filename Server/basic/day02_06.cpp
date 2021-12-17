/* day02 유니온 */
#include <stdio.h>
#include <string.h>

struct B {
    union{
        struct{int a[5];}A;
        struct{char a[10], b[10];}B;
        struct{short a[5], b[5];}C;
        char addr[20]; // 자신의 아이피 주소 저장 "192.168.56.1"
    }UN;
    #define _addr UN.addr
};

struct A{
    int port; // 12345 저장
    struct B b;
};

int main(){
    struct A a;

    a.port = 12345;
    strcpy(a.b._addr, "192.168.56.1");
    //strcpy(a.b.UN.addr, "192.168.56.1");
    //a.b.UN.addr[20] = "192.168.56.1";

    printf("port : %d\naddr : %s\n", a.port, a.b._addr);

    return 0;
}