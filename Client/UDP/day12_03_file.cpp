/* UDP Client - 실습01-1. 파일전송 */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

int main(){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET cs;
    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if(cs == INVALID_SOCKET){
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    // 접속할 서버의 주소 구조체 만들어놓고
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    char buf[1024];
    printf("파일에 입력 할 데이터 : ");
    scanf("%s", buf);

    FILE * fp = fopen("../src/day12_03.txt", "w");
    if(fp == NULL){
        printf("fopen error!!\n");
        return -1;
    }
    fwrite(buf, 20, 1, fp);
    fclose(fp);

    fp = fopen("../src/day12_03.txt", "r");
    if(fp == NULL){
        printf("fopen error!!\n");
        return -1;
    }
    char str[1024] = {0};
    fread(buf, 1, sizeof(str), fp);
    fclose(fp);

    int error = 0;
    error = sendto(cs, buf, sizeof(buf), 0, (SOCKADDR*)&addr, sizeof(addr));
    if(error == SOCKET_ERROR){
        printf("sendto ERROR!!\n");
        return -1;
    }
    printf("전송완료!!\n");

    closesocket(cs);
    WSACleanup();
    return 0;
}