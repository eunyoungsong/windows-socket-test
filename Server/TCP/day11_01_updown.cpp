/* TCP Server - 실습04 문제1. UpDown 게임 : myCode */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    /* 랜덤 숫자 뽑기 */
    srand((unsigned int)time(NULL));
    int num = rand();
    //printf("난수 : %d\t나머지 : %d\n", num, (int)num%100);
    num = (int)(num%100);
    printf("랜덤숫자 : %d\n", num);

    // 클라이언트용 소켓 생성
    SOCKET cs;
    SOCKADDR_IN caddr;
    memset(&caddr, 0, sizeof(caddr));
    int clen = sizeof(caddr);
    
    printf("accept 실행 전\n");
    cs = accept(s, (sockaddr*)(&caddr), &clen);
    if(cs == INVALID_SOCKET){
        printf("accept error!!\n");
        return -1;
    }
    printf("accept 실행성공\n");
    printf("=====================================\n");

    /* 클라이언트에서 숫자 받기 */
    char recNum[10] = {0};
    int count = 1;

    while(count < 6){
        recv(cs, recNum, sizeof(recNum), 0);
        //printf("클라이언트가 보낸 숫자 : %s\n", recNum);
        int recNum2 = 0;
        recNum2 = atoi(recNum);
        printf("클라이언트가 보낸 숫자 : %d\n", recNum2);

        /* 랜덤 숫자와 받은 숫자 비교하기 : 일치한다면 게임종료 */
        char str[1024] = {0};
        if(num == recNum2){
            //printf("정답입니다!!\n");
            strcpy(str, "정답입니다!!");
            send(cs, (char*)str, sizeof(str), 0);
            break;
        }
        /* 불일치 한다면 : Up Down 알려주기 */
        else if(num > recNum2){
            //printf("up\n");
            strcpy(str, "up");
            send(cs, (char*)str, sizeof(str), 0);
        }
        else if(num < recNum2){
            //printf("down\n");
            strcpy(str, "down");
            send(cs, (char*)str, sizeof(str), 0);
        }
        count++;
    }
    
    printf("=====================================\n");
    printf("통신성공!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}