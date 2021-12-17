/* UDP Client - 실습02-1. 현재시간 */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

// time 라이브러리 추가
#include <time.h>

int main(){

    /* 윈속 생성 */
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    /* 소켓 생성 */
    SOCKET s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s == INVALID_SOCKET){
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    /* 접속할 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    /* 서버에 데이터 송신 */
    char msg[256] = "시간보내기!!";
    int error = 0;
    error = sendto(s, msg, sizeof(msg), 0, (SOCKADDR*)&addr, sizeof(addr));
    if(error == SOCKET_ERROR){
        printf("sendto ERROR!!\n");
        return -1;
    }

    char time[512];
    memset(time, 0, sizeof(time));

    SOCKADDR_IN recvAddr;
    int recvLen = sizeof(recvAddr);
    memset((char*)&recvAddr, 0, recvLen);

    recvfrom(s, time, sizeof(time), 0, (SOCKADDR*)&recvAddr, &recvLen);

    printf("%s\n", time);
    printf("통신완료\n");

    closesocket(s);
    WSACleanup();
    return 0;
}