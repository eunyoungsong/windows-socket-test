/* UDP Server - 실습01-3. 계산기 */
#pragma comment(lib, "ws2_32")
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
        printf("socket error!!\n");
        return -1;
    }

    /* 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);

    /* 주소결합 */
    int errorCheck = 0;
    errorCheck = bind(s, (sockaddr*)&addr, sizeof(addr));
    if(errorCheck == SOCKET_ERROR){
        printf("bind error!!\n");
        return -1;
    }

    /* 계산식 데이터 수신 */
    struct calc ca;
    ca.num1 = 0;
    ca.num2 = 0;
    ca.op = 0;
   //char buf[1024] = {0};
    SOCKADDR_IN Caddr;
    memset(&Caddr, 0, sizeof(Caddr));
    int Caddrlen = sizeof(Caddr);
    int result = 0;

    errorCheck =  recvfrom(s, (char*)&ca, sizeof(ca), 0, (sockaddr*)&Caddr, &Caddrlen);
    if(errorCheck == SOCKET_ERROR){
        printf("recvfrom error!!\n ");
        return -1;
    }
    printf("받은 데이터 : %d %c %d\n", ca.num1, ca.op, ca.num2);

    /* 연산 */
    if(ca.op == '+'){
        result = ca.num1 + ca.num2;
    }else if(ca.op == '-'){
        result = ca.num1 - ca.num2;
    }else if(ca.op == '*'){
        result = ca.num1 * ca.num2;
    }else if(ca.op == '/'){
        result = ca.num1 / ca.num2;
    }
    printf("연산 결과 : %d\n", result);

    /* 클라이언트에 결과 보내기 */
    errorCheck = sendto(s, (char*)&result, sizeof(result), 0, (sockaddr*)&Caddr, Caddrlen);
    if(errorCheck == SOCKET_ERROR){
        printf("sendto error!!\n");
        return -1;
    }
    printf("통신완료\n");

    closesocket(s);
    WSACleanup();
    return 0;
}