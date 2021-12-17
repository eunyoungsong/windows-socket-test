/* UDP Client - 실습01-3. 계산기 */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

struct calc {
    int num1;
    char op;
    int num2;
};    

int main(){

    /* 윈속 생성 */
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    /* 소켓 생성 */
    SOCKET s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s == INVALID_SOCKET){
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    /* 접속할 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    /* 서버에 데이터 송신 */
    struct calc ca;
    printf("계산식 : ");
    scanf("%d %c %d", &ca.num1, &ca.op, &ca.num2);

    int error = 0;
    error = sendto(s, (char*)&ca, sizeof(ca), 0, (SOCKADDR*)&addr, sizeof(addr));
    if(error == SOCKET_ERROR){
        printf("sendto ERROR!!\n");
        return -1;
    }

    /* 서버에서 계산결과 데이터 수신 */
    int result = 0;
    error = recvfrom(s, (char*)&result, sizeof(result), 0, 0, 0);
    if(error == SOCKET_ERROR){
        printf("recvfrom ERROR!!\n");
        return -1;
    }

    printf("계산결과 : %d %c %d = %d\n", ca.num1, ca.op, ca.num2, result);
    printf("통신완료\n");

    closesocket(s);
    WSACleanup();
    return 0;
}