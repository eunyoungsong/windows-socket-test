/* TCP Server - 실습02 문제1. 동적할당 */
// 동적할당 데이터 초기화는 for문 또는 memeset 함수를 이용하여 초기화
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    // 소켓 생성
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0); // == socket(2, 1, 0);
    if(s == INVALID_SOCKET){
        printf("socket error!!\n");
        return -1;
    }

    // 주소 할당
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

    // 소켓 오픈 : 연결대기
    errorCheck = listen(s, SOMAXCONN);
    if(errorCheck == SOCKET_ERROR){
        printf("listen error!!\n");
        return -1;
    }

    // 클라이언트용 소켓 생성
    SOCKET cs;
    SOCKADDR_IN caddr;
    memset(&caddr, 0, sizeof(caddr));
    int clen = sizeof(caddr);

    printf("accep 실행 전\n");
    cs = accept(s, (sockaddr*)(&caddr), &clen);
    if(cs == INVALID_SOCKET){
        printf("accept error!!\n");
        return -1;
    }
    printf("accep 실행성공\n");
    printf("=====================================\n");

    // 실습02 문제1. 클라이언트가 보낼 데이터 크기만큼 저장공간 만들어 수신하기
    //char buf[1024] = {0,};
    int fsize;
    recv(cs, (char*)&fsize, 4, 0);
    printf("수신 사이즈 : %d\n", fsize);

    char * buf = (char*)malloc(fsize);

    int recvSize = 0;
    recvSize = recv(cs, buf, fsize, 0);
    printf("받은 수신 데이터 : %s\n", buf);
    printf("수신 데이터 크기 : %d\n", recvSize);
    printf("=====================================\n");

    // 데이터를 파일로 받기
    FILE * fp = fopen("C:\\dev\\socket_programing\\server\\TCP\\day09_01.txt", "w"); 
    if(fp == NULL){
        printf("fopen error!!\n");
        return -1;
    }
    //fwrite(buf, 1, sizeof(buf), fp);
    fwrite(buf, 1, fsize, fp);
    fclose(fp);

    printf("통신성공!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}