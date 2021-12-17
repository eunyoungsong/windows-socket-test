#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET CiTc;
    CiTc = socket(AF_INET, SOCK_STREAM, 0);
    if(CiTc == INVALID_SOCKET){
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    // 접속할 서버의 주소 구조체
    SOCKADDR_IN srvAddr;
    memset(&srvAddr, 0, sizeof(srvAddr));
    srvAddr.sin_addr.s_addr = inet_addr("192.168.0.35"); //서버에 대한 IP
    srvAddr.sin_port = htons(22222);
    srvAddr.sin_family = AF_INET;

    //connect(소켓, 서버에 대한 주소, 그 주소에 대한 사이즈);
    int errorCheck = connect(CiTc, (sockaddr*)(&srvAddr), sizeof(srvAddr));
    if(errorCheck == SOCKET_ERROR){
        printf("CONNECT ERROR!!\n");
        return -1;
    }
    
    // 서버에 데이터 전송
    char buf[100] = "HELLO SOCKET";
    int sendSize = 0;
    sendSize = send(CiTc, buf, sizeof(buf), 0);
    printf("%d byte 전송완료!\n", sendSize);

    closesocket(CiTc);
    WSACleanup();
    return 0;
}