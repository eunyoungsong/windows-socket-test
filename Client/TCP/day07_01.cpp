/* TCP Client 사용 예제 실습용 */
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == INVALID_SOCKET){
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    // 접속할 서버의 주소 구조체
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr("192.168.0.35"); //서버에 대한 IP
    addr.sin_port = htons(22222);
    addr.sin_family = AF_INET;

    //서버에 접속 요청
    int errorCheck;
    errorCheck = connect(s, (sockaddr*)(&addr), sizeof(addr)); // connect(소켓, 서버에 대한 주소, 그 주소에 대한 사이즈);
    if(errorCheck == SOCKET_ERROR){
        printf("CONNECT ERROR!!\n");
        return -1;
    }
    
    char buf[1024] = {0,};
    printf("송신 데이터 입력 : ");
    scanf("%s", buf);

    int sendSize = 0;
    sendSize = send(s, buf, sizeof(buf), 0);
    printf("송신 데이터 크기 : %d\n", sendSize);

    closesocket(s);
    WSACleanup();
    return 0;
}