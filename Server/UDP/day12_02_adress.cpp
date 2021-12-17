/* UDP Server - ip/port 출력하기*/
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

int main(int argc, char *argv[]){

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

    int errorCheck = 0;
    errorCheck = bind(s, (sockaddr*)&addr, sizeof(addr));
    if(errorCheck == SOCKET_ERROR){
        printf("bind error!!\n");
        return -1;
    }

    SOCKADDR_IN Caddr;
    int Caddrlen = sizeof(Caddr);
    char buf[1024];
    errorCheck = recvfrom(s, buf, sizeof(buf), 0, (sockaddr*)&Caddr, &Caddrlen);
    if(errorCheck == SOCKET_ERROR){
        printf("recvfrom error!!\n ");
        return -1;
    }
    printf("수신 데이터 : %s\n", buf);
    printf("수신 IP : %s\n", inet_ntoa(Caddr.sin_addr));
    printf("수신 PORT : %d\n", ntohs(Caddr.sin_port));
    
    closesocket(s);
    WSACleanup();
    return 0;
}