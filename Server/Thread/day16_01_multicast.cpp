/* multicast_recv_basic */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h> // 옵션 헤더
//#define SERVER_IP "192.168.0.35"
#define SERVER_PORT 22222

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

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    /* 서버 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.35");

    /* 주소결합 */
    int errorCheck = 0;
    errorCheck = bind(s, (sockaddr*)&addr, sizeof(addr));
    if(errorCheck == SOCKET_ERROR){
        printf("bind error!!\n");
        return -1;
    }

    /* 멀티캐스트 주소 */
    struct ip_mreq mreq;
    mreq.imr_interface.s_addr = inet_addr("192.168.0.35"); //자기주소
    mreq.imr_multiaddr.s_addr = inet_addr("233.3.3.3"); //멀티캐스트 예약주소

    /* 멀티캐스트 그룹 가입 */
    setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
    /*int setsockopt ( s : 옵션 적용할 소켓,
                     int level : 소켓의 어떤 부분을 변경할 것인지 주체 설정,
                     int optname : 설정할 옵션 이름,
                     const char * optval : 설정할 옵션 값을 담고 있는 변수 주소,
                     int optlen : optval의 크기  )                                  */
    
    char mulbuf[512] = {0};

    recvfrom(s, mulbuf, sizeof(mulbuf), 0, NULL, NULL);
    printf("수신 데이터 : %s\n", mulbuf);

    /* 멀티캐스트 그룹 탈퇴 */
    setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
    
    printf("통신완료!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}