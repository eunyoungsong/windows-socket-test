/* UDP Server */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

int main(int argc, char *argv[]){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    // 서버 소켓 생성
    SOCKET udpS;
    udpS= socket(AF_INET, SOCK_DGRAM, 0); // UDP : SOCK_DGRAM
    if(udpS == INVALID_SOCKET){
        printf("socket error!!\n");
        return -1;
    }

    // 서버 주소 구조체
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 소켓에 주소 연결
    int error = 0;
    error = bind(udpS, (SOCKADDR*)(&addr), sizeof(addr));
    if(error = SOCKET_ERROR){
        printf("bind error!!\n");
        return -1;
    }

    // 클라이언트 주소 저장할 구조체 
    SOCKADDR_IN CTAddr;
    int CTAddrLen = sizeof(CTAddr);
    char buf[1024];
    error = recvfrom(udpS, buf, sizeof(buf), 0, (SOCKADDR*)(&CTAddr), &CTAddrLen);
    /*  int recvfrom(SOCKET s, const char * buf, int len, int flag,
                     const struct sockaddr * from, int * fromlen)
        - SOCKET s                   : 접속을 허용할 소켓 지정
        - const struct sockaddr * from : 송신자 주소 구조체
        - int fromlen                  : 주소 구조체의 길이를 담은 변수의 주소 
        - 리턴 값 : 성공 시 수신 바이트, 실패시 SOCKET_ERROR                      */
    if(error = SOCKET_ERROR){
        printf("recvfrom error!!\n");
        return -1;
    }
    printf("수신 데이터 : %s\n", buf);

    closesocket(udpS);
    WSACleanup();
    return 0;

}