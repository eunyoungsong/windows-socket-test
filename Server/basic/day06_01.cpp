/* ex1) 바이트 정렬 함수(호스트->네트워크) */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    short x1 = 0x1234; // 0x = 16진수이다
    long y1 = 0x12345678;

    //printf("[호스트 바이트 -> 네트워크 바이트]\n");
    printf("[host bite -> network bite]\n");
    // Little Endian 방식 때문에 해당 값 뒤집어주기
    printf("0x%x -> 0x%x\n", x1, htons(x1)); 
    printf("0x%x -> 0x%x\n", y1, htonl(y1)); 
    
    return 0;
}

