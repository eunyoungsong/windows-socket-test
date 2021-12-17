/* UDP Client - 실습01-2. 에코클라이언트 */
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

    /* 접속할 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    /* 데이터 송신 */
    char buf[1024]= {0};
    printf("송신 데이터 : ");
    scanf("%s", buf);

    int error = 0;
    error = sendto(cs, buf, sizeof(buf), 0, (SOCKADDR*)&addr, sizeof(addr));
    if(error == SOCKET_ERROR){
        printf("sendto ERROR!!\n");
        return -1;
    }

    // 에코 받기
    SOCKADDR_IN recvaddr;
    memset(&recvaddr, 0, sizeof(recvaddr));
    int addrlen = sizeof(recvaddr);
    char str[1024] = {0};
    error = recvfrom(cs, str, sizeof(str), 0, (sockaddr*)&recvaddr, &addrlen);
    //error = recvfrom(cs, str, sizeof(str), 0, 0, 0); // 상대방에 대한 정보가 필요 없으면 0 값 처리
    if(error == SOCKET_ERROR){
        printf("recvfrom ERROR!!\n");
        return -1;
    }
    printf("수신 데이터: %s\n", str);
    printf("=====================전송완료\n");

    closesocket(cs);
    WSACleanup();
    return 0;
}