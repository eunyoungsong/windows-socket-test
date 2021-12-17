/* TCP Server - 실습01 문제1,2,3 */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
    
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

    // 클라이언트용 소켓 생성
    SOCKET cs;
    SOCKADDR_IN caddr;
    memset(&caddr, 0, sizeof(caddr));
    int clen = sizeof(caddr);
    
    // 클라이언트용 소켓으로 클라이언트 요청 수락 : 연결허용
    cs = accept(s, (sockaddr*)(&caddr), &clen);
    if(cs == INVALID_SOCKET){
        printf("accept error!!\n");
        return -1;
    }

    // 클라이언트에서 보낸 데이터 수신
    char buf[1024] = {0,};
    int recvSize = 0;
    memset(buf, 0, 1024);
    recvSize = recv(cs, buf, sizeof(buf), 0);
    printf("=====================================\n");
    printf("받은 수신 데이터 : %s\n", buf);
    printf("수신 데이터 크기 : %d\n", recvSize);
    printf("=====================================\n");

    // 문제1. 클라이언트의 IP/PORT 주소 출력하기
    //printf("수신 데이터의 IP 주소   : %d\n", caddr.sin_addr);
    printf("수신 데이터의 IP 주소   : %s\n", inet_ntoa(caddr.sin_addr));
    printf("수신 데이터의 PORT 주소 : %d\n", ntohs(caddr.sin_port));
    printf("=====================================\n");
    
    // 문제2. 에코 : 클라이언트에 데이터 전송
    char str[1024];
    printf("응답 데이터 입력 : ");
    scanf("%s", str);
    send(cs, str, sizeof(str), 0);

    printf("=====================================\n");
    printf("통신성공!!\n");

    closesocket(s);
    WSACleanup();

    return 0;
}
