#include <stdio.h>

void test(float *a){
    printf("\ntest_okok\n");
}

int main(){

    char str[10] = "hello";
    char ch = 'A';
    int a = 97;
    printf((char*)&a);
    float b = (char)a;
    test((float*)&a);
    return 0;

} 