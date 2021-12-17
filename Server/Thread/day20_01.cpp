/* thread tcp 채팅 */
#pragma comment(lib, "ws2_32")
#include <stdio.h>
#include <winsock2.h>

struct userInfo{
    char userIP[20];
    char userPW[20];
    int num;
};

void auth(SOCKET CLTS);
SOCKET totSock[256];
int sockCnt = 0;
DWORD __stdcall func(LPVOID arg);
SOCKADDR_IN CLTaddr;

char* host_ip(){
    struct hostent * hp;
    char host[1024];
    char ip[100] = {0};
    gethostname(host, sizeof(host));
    hp = gethostbyname(host);
    printf("hp->h_addr_list[0] = %s\n", inet_ntoa(*(struct in_addr*)hp->h_addr_list[0]));
}