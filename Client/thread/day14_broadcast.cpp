/* broadcast_Send_Basic */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
//#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

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

    /* 브로드캐스트 활성 */
    BOOL opt = TRUE ;
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt));
    /*int setsockopt( s: 옵션 적용할 소켓,
                      int level : 소켓의 어떤 부분을 변경할 것인지 주체설정,
                      int optname : 설정할 옵션 이름 (SO_BROADCAST : 브로드캐스트로 옵션 설정),
                      const char * optval : 설정할 옵션 값을 담고 있는 변수 주소,
                      int optlen : optval의 크기 ) */


    /* 통신할 주소 구조체 생성 */
    SOCKADDR_IN sendAddr;
    memset(&sendAddr, 0, sizeof(sendAddr));
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(SERVER_PORT);
    sendAddr.sin_addr.s_addr = inet_addr("192.168.222.255"); // 브로드캐스트 255 : 같은 대역대의 모든PC에 데이터 전송

    /* 서버(receiver)에 데이터 송신 */
    char sendbuf[1024] = {0};
    memset(sendbuf, 0, sizeof(sendbuf));

    strcpy(sendbuf, "Broadcasting!!");
    int sendlen = strlen(sendbuf);

    sendto(s, sendbuf, sendlen, 0, (SOCKADDR*)&sendAddr, sizeof(sendAddr));

    printf("통신완료!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}