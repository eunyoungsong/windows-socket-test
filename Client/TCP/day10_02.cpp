/* TCP Client - 실습03 문제2. 이미지 파일 전송2 */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET cs;
    cs = socket(AF_INET, SOCK_STREAM, 0);
    if(cs == INVALID_SOCKET){
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    // 접속할 서버의 주소 구조체 만들어놓고
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22222);
    addr.sin_addr.s_addr = inet_addr("192.168.0.35"); //서버에 대한 IP
    
    // 서버에 접속 요청하기
    int errorCheck;
    errorCheck = connect(cs, (sockaddr*)(&addr), sizeof(addr)); //connect(소켓, 서버에 대한 주소, 그 주소에 대한 사이즈);
    if(errorCheck == SOCKET_ERROR){
        printf("CONNECT ERROR!!\n");
        return -1;
    }

    // 서버에 데이터 전송
    char buf[1024] = {0};
    printf("이미지 경로 입력 : ");
    scanf("%s", buf);    
    send(cs, buf, sizeof(buf), 0); // 서버에 이미지 경로 보내기

    // 서버에서 보낸 파일 사이즈 받기
    int fsize = 0;
    recv(cs, (char*)&fsize, 4, 0);
    printf("fsize : %d\n", fsize);

    // 동적할당 : 파일만큼의 공간 만들어주기
    char * fbuf = (char*)malloc(fsize);

    // 서버에서 보낸 이미지 파일 데이터 받기
    recv(cs, fbuf, fsize, 0);

    FILE * fp = NULL;
    fp = fopen("../src/testImage.jpg", "wb");
    if(fp == NULL){
        printf("fopen ERROR!!\n");
        return -1;
    }
    fwrite(fbuf, 1, fsize, fp);
    fclose(fp);
    free(fbuf); // 동적메모리 해제

    printf("통신성공!!");

    closesocket(cs);
    WSACleanup();
    return 0;
}
