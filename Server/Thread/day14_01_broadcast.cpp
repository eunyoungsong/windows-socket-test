/* broadcast_recv_basic */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
//#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

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

    /* 서버 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.S_un.S_addr = inet_addr("192.168.222.255"); // 브로드캐스트 255

    /* 주소결합 */
    int errorCheck = 0;
    errorCheck = bind(s, (sockaddr*)&addr, sizeof(addr));
    if(errorCheck == SOCKET_ERROR){
        printf("bind error!!\n");
        return -1;
    }

    /* 클라이언트 주소 구조체 생성 */
    SOCKADDR_IN Caddr;
    memset(&Caddr, 0, sizeof(Caddr));
    int Caddrlen = sizeof(Caddr);

    char recvbuf[1024] = {0};
    recvfrom(s,recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&Caddr, &Caddrlen);
    printf("수신 데이터 : %s\n", recvbuf);
    
    printf("통신완료!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}