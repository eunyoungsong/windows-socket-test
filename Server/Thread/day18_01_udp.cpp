/* UDP 채팅프로그램 */
#pragma comment(lib, "ws2_32")
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>

HANDLE hThread[2];
SOCKET UDPs;
SOCKADDR_IN SRVAddr;

unsigned __stdcall func1(void * arg);
unsigned __stdcall func2(void * arg);

int main(){
    
    /* 윈속 생성 */
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    /* 소켓 생성 */
    UDPs = socket(AF_INET, SOCK_DGRAM, 0);
    if(UDPs == INVALID_SOCKET){
        printf("socket ERROR!!\n");
        return -1;
    }

    /* 서버 주소 구조체 */
    SRVAddr.sin_family = AF_INET;
    SRVAddr.sin_port = htons(22222);
    SRVAddr.sin_addr.s_addr = inet_addr("192.168.0.35"); //자기주소 0.0.0.0 127.0.0.1~254 localhost

    /* 주소 결합 */
    int error = 0;
    error = bind(UDPs, (sockaddr*)&SRVAddr, sizeof(SRVAddr));
    if(error == SOCKET_ERROR){
        printf("bind ERROR!!\n");
        return -1;
    }

    // 스레드 두개 돌리기
    hThread[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL); //send용 스레드
    hThread[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL); //recv용 스레드

    // 메인 일시중지
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

    /* 소켓 종료 */
    closesocket(UDPs);
    /* 윈속 종료 */
    WSACleanup();
    return 0;
}

/* send 역할 */
unsigned __stdcall func1(void * arg){

    /* 멀티캐스트 TTL */
    int ttl = 128;
    setsockopt(UDPs, IPPROTO_IP, IP_MULTICAST_TTL, (char*)ttl, sizeof(ttl));

    /* 통신할 대상의 주소 구조체 */
    SOCKADDR_IN sendAddr;
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(22222);
    sendAddr.sin_addr.s_addr = inet_addr("233.3.3.3"); //멀티캐스트 주소

    char sendBuf[512];
    memset(sendBuf, 0, sizeof(sendBuf));
    int error = 0;

    while(1){
        printf("[입력] >");
        gets(sendBuf);

        /* 데이터전송 */
        error = sendto(UDPs, sendBuf, sizeof(sendBuf), 0, (sockaddr*)&sendAddr, sizeof(sendAddr));
        if(error == SOCKET_ERROR){
            printf("sendto ERROR!!\n");
            return -1;
        }

        if(strcmp(sendBuf, "exit") == 0){
            sprintf(sendBuf, "%s님이 채팅방 나감", inet_ntoa(SRVAddr.sin_addr));
            sendto(UDPs, sendBuf, sizeof(sendBuf), 0, (sockaddr*)&sendAddr, sizeof(sendAddr));

            closesocket(UDPs);
            printf("프로그램 종료\n");
            break;
        }
    }

    return 0;
}

/* recv 역할 */
unsigned __stdcall func2(void * arg){

    /* 멀티캐스트 주소 */
    struct ip_mreq mt;
    mt.imr_interface.s_addr = inet_addr("192.168.0.35");
    mt.imr_multiaddr.s_addr = inet_addr("233.3.3.3"); 

    /* 멀티캐스트 그룹 가입 */
    setsockopt(UDPs, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mt, sizeof(mt));

    /* 통신할 대상의 주소 구조체 */
    SOCKADDR_IN recvAddr;
    int recvLen = sizeof(recvAddr);

    /* 데이터 수신 */
    char recvBuf[512];
    memset(recvBuf, 0, sizeof(recvBuf));
    int error = 0;

    while (1){
        error = recvfrom(UDPs, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&recvAddr, &recvLen);
        if(error == SOCKET_ERROR){
            printf("recvfrom ERROR!!\n");
            return -1;
        }
        printf("[UDP %s:%d]\n", inet_ntoa(recvAddr.sin_addr), ntohs(recvAddr.sin_port));
        printf("[출력] > %s\n", recvBuf);
    }

    return 0;
}