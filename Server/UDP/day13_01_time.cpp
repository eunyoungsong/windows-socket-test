/* UDP Server - 실습02-1. 현재시간 */
#pragma comment(lib, "ws2_32")
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
        printf("socket error!!\n");
        return -1;
    }

    /* 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);

    /* 주소결합 */
    int errorCheck = 0;
    errorCheck = bind(s, (sockaddr*)&addr, sizeof(addr));
    if(errorCheck == SOCKET_ERROR){
        printf("bind error!!\n");
        return -1;
    }

    /* 데이터 수신 */
    SOCKADDR_IN Caddr;
    int Caddrlen = sizeof(Caddr);
    memset(&Caddr, 0, sizeof(Caddr));

    char msg[256] = {0};
    memset(&msg, 0, sizeof(msg));

    errorCheck = recvfrom(s, msg, sizeof(msg), 0, (sockaddr*)&Caddr, &Caddrlen); // 클라이언트 정보 수집
    if(errorCheck == SOCKET_ERROR){
        printf("recvfrom error!!\n ");
        return -1;
    }
    
    /* 클라이언트에 데이터 보내기 */
    time_t tm;
    time(&tm);
    struct tm * lt = localtime(&tm);
    char time[512];
    memset(time, 0, sizeof(time));
    
    sprintf(time, "%d년 %d월 %d일 %d시 %d분",
            lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min);

    errorCheck = sendto(s, time, sizeof(time), 0, (sockaddr*)&Caddr, Caddrlen);
    if(errorCheck == SOCKET_ERROR){
        printf("sendto error!!\n");
        return -1;
    }

    printf("통신완료\n");

    closesocket(s);
    WSACleanup();
    return 0;
}