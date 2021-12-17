/* ex3) ip주소 변환 함수 */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    char * ipv4 = "192.168.1.1";
    printf("변환 전: %s\n", ipv4); // 문자형
    printf("변환 후: %d\n", inet_addr(ipv4)); // IP주소 정수형으로 변환

    IN_ADDR ipv4_su;
    ipv4_su.s_addr = inet_addr(ipv4);
    //ipv4_su.S_un.S_addr = inet_addr(ipv4);

    //  inet_ntoa(IN_ADDR자료형) : 다시 문자열로 재변환
    printf("재변환 : %s\n", inet_ntoa(ipv4_su)); 
    
    return 0;
}

