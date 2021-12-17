/* UDP Client */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

//#define SERVER_IP "192.168.0.35"
//#define SERVER_PORT 22222

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
    addr.sin_port = htons(22222);
    addr.sin_addr.s_addr = inet_addr("192.168.0.35");

    char buf[512];
    printf("송신 데이터 입력 : ");
    scanf("%s", buf);

    int error = 0;
    error = sendto(cs, buf, sizeof(buf), 0, (SOCKADDR*)&addr, sizeof(addr));
    /*  sendto(SOCKET s, const char * buf, int len, int flag,
                const struct sockaddr * to, int tolen);
        - const struct sockaddr * to : 수신자 주소 구조체
        - int tolen                  : 주소 구조체의 길이                   */
    if(error == SOCKET_ERROR){
        printf("sendto ERROR!!\n");
        return -1;
    }

    /*
    int size = 0;
    size = sendto(cs, buf, sizeof(buf), 0, (SOCKADDR*)&addr, sizeof(addr));
    printf("송신 데이터 크기 : %d\n", size);
    */

    printf("전송완료!!\n");

    closesocket(cs);
    WSACleanup();
    return 0;
}