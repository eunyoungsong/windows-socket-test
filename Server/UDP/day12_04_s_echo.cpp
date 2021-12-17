/* UDP Server - 실습01-2. 에코서버 */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

int main(){
    
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s == INVALID_SOCKET){
        printf("socket error!!\n");
        return -1;
    }

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
    memset(&Caddr, 0, sizeof(Caddr));
    int Caddrlen = sizeof(Caddr);
    char buf[1024] = {0};

    // 데이터 받고
    errorCheck = recvfrom(s, buf, sizeof(buf), 0, (sockaddr*)&Caddr, &Caddrlen);
    if(errorCheck == SOCKET_ERROR){
        printf("recvfrom error!!\n ");
        return -1;
    }
    printf("수신 데이터 : %s\n", buf);

    // 응답 데이터 보내기
    char str[1024] = {0};
    printf("응답 데이터 입력 : ", str);
    scanf("%s", str);

    errorCheck = sendto(s, str, sizeof(str), 0, (sockaddr*)&Caddr, sizeof(Caddr));
    if(errorCheck == SOCKET_ERROR){
        printf("sendto error!!\n");
        return -1;
    }
    printf("====================통신성공\n");

    closesocket(s);
    WSACleanup();
    return 0;
}