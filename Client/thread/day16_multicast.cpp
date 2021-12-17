/* multicast_Send_Basic */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h>

int main()
{
    /* 윈속 생성 */
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    /* 소켓 생성 */
    SOCKET s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET)
    {
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    /* 통신할 주소 구조체 생성 */
    SOCKADDR_IN sendAddr;
    memset(&sendAddr, 0, sizeof(sendAddr));
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(22222);
    sendAddr.sin_addr.s_addr = inet_addr("233.3.3.3"); //멀티캐스트 예약주소

    /* 서버(receiver)에 데이터 송신 */
    int mulTTL = 128;
    setsockopt(s,IPPROTO_IP, IP_MULTICAST_TTL, (char*)&mulTTL, sizeof(mulTTL));

    char mulbuf[512] = {0};
    memset(mulbuf, 0, sizeof(mulbuf));

    printf("보낼 내용 입력 : ");
    scanf("%s", mulbuf);
    sendto(s, mulbuf, strlen(mulbuf), 0, (SOCKADDR*)&sendAddr, sizeof(sendAddr));

    printf("통신완료!!\n");

    /* 소켓 종료 */
    closesocket(s);
    /* 윈속 종료 */
    WSACleanup();
    return 0;
}