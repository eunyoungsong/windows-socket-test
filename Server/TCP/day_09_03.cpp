/* TCP Server - ???02 ????2. ????? ???? ???? */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    // ???? ????
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0); // == socket(2, 1, 0);
    if(s == INVALID_SOCKET){
        printf("socket error!!\n");
        return -1;
    }

    // ??? ???
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    int errorCheck = 0;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22222);
    addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.35");
    errorCheck = bind(s, (sockaddr*)(&addr), sizeof(addr));
    if(errorCheck == SOCKET_ERROR){
        printf("bind error!!\n");
        return -1;
    }

    // ???? ???? : ??????
    errorCheck = listen(s, SOMAXCONN);
    if(errorCheck == SOCKET_ERROR){
        printf("listen error!!\n");
        return -1;
    }

    // ????????? ???? ????
    SOCKET cs;
    SOCKADDR_IN caddr;
    memset(&caddr, 0, sizeof(caddr));
    int clen = sizeof(caddr);

    printf("accep ???? ??\n");
    cs = accept(s, (sockaddr*)(&caddr), &clen);
    if(cs == INVALID_SOCKET){
        printf("accept error!!\n");
        return -1;
    }
    printf("accep ??????\n");
     printf("=====================================\n");

    // ???02 ????1. ????????? ???? ?????? ???? ??????? ????? ???????
    //char buf[1024] = {0,};
    int fsize;
    recv(cs, (char*)&fsize, 4, 0);
    printf("???? ?????? : %d\n", fsize);

    char * buf = (char*)malloc(fsize);

    int recvSize = 0;
    recvSize = recv(cs, buf, fsize, 0);
    printf("???? ???? ?????? : %s\n", buf);
    printf("???? ?????? ??? : %d\n", recvSize);
    printf("=====================================\n");

    // ??????? ????? ???
    FILE * fp = fopen("C:\\dev\\socket_programing\\server\\TCP\\testImage.jpg", "wb"); 
    if(fp == NULL){
        printf("fopen error!!\n");
        return -1;
    }
    //fwrite(buf, 1, sizeof(buf), fp);
    fwrite(buf, 1, fsize, fp);
    fclose(fp);

    printf("??????!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}