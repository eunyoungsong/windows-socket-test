/* TCP Client - 실습01 문제4 : 파일전송 */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

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
    char buf[1024] = {0,};

    // 문제4. 파일로 데이터 전송하기
    FILE * fp = fopen("C:\\Users\\eunyoung\\dev\\socket_client\\src\\day09_01.txt", "r");
    if(fp == NULL){
        printf("fopen error!!\n");
        return -1;
    }
    fread(buf, 1, 1024, fp);
    fclose(fp);

    int sendSize = 0;
    sendSize = send(cs, buf, sizeof(buf), 0);
    printf("송신 데이터 크기 : %d\n", sendSize);
    
    closesocket(cs);
    WSACleanup();
    return 0;
}
