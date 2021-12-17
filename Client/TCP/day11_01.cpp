/* TCP Client - 실습04 문제1. UPDOWN 게임 : myCode */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

    int count = 1;
    while (count < 6)
    {
        /* 서버에 데이터 전송 */
        char num[10] = {0};
        printf("예상 숫자 입력 : ");
        scanf("%s", num);
        send(cs, num, sizeof(num), 0);
       
        /* 서버에서 보낸 데이터 받기 */
        char str[1024]={0};
        recv(cs, (char*)str, sizeof(str), 0);
        printf("%s\n", str);

        if(strcmp(str, "정답입니다!!") == 0){
            break;
        }

        if(count == 5){
            printf("\n게임실패!! 재시도하세요\n");
        }

        count++;
    }

    closesocket(cs);
    WSACleanup();
    return 0;
}
