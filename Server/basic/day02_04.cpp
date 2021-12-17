/* day02 구조체 */
#include <stdio.h>
#include <string.h>

struct score{
    int kor;
    int eng;
    int math;
};

struct _name{
    char name[20];
};

struct _addr{
    char addr[20];
};

struct infor{
    struct _name name;
    struct _addr addr;
    int age;
};

struct Student{
    struct score s;
    struct infor i;
};

int main(){
    struct Student S;

    S.s.kor = 100;
    S.s.eng = 80;
    S.s.math = 70;

    strcpy(S.i.name.name, "EunYoung");
    strcpy(S.i.addr.addr, "naju");
    S.i.age = 28;
    
    printf("NAEM : %s\nADDR : %s\nAGE  : %d\n", S.i.name.name, S.i.addr.addr, S.i.age);

/*
    printf("NAEM : %s\n", S.i.name.name);
    printf("ADDR : %s\n", S.i.addr.addr);
    printf("AGE : %d\n", S.i.age);
*/
    printf("--------------------------\n");
    printf("KOR : %d\nENG : %d\nMATH : %d\n", S.s.kor, S.s.eng, S.s.math);

    return 0;
}