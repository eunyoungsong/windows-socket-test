/* TCP Server - 실습03 문제2. 이미지 파일 전송2  */
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

    char buf[1024] = {0};
    int recvSize = 0;
    recvSize = recv(cs, buf, sizeof(buf), 0); // buf에 클라이언트가 보낸 이미지 경로가 들어옴
    printf("수신 데이터 buf : %s\n", buf);

    // 받은 이미지 경로로 파일 오픈하기
    FILE * fp = NULL;
    fp = fopen(buf, "rb"); // buf에 경로가 들어와 있기 때문에
    if(fp == NULL){
        printf("fopen ERROR!!\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    int fsize = 0;
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    send(cs, (char*)&fsize, sizeof(fsize), 0); // 파일사이즈를 클라이언트에게 보내기
    printf("fsize: %d\n", fsize); // 확인

    char * fbuf = (char*)malloc(fsize); // 파일만큼의 공간만들어주기 : 동적할당
    fread(fbuf, 1, fsize, fp);
    send(cs, fbuf, fsize, 0);
    fclose(fp);
    free(fbuf); // malloc함수 메모리 해제

    printf("통신성공!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}
