/* UDP Server - 실습02-2. 이미지파일 */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
#define SERVER_IP "192.168.0.35"
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

    /* 데이터 수신 */

    /* 클라이언트 주소 구조체 생성 */
    SOCKADDR_IN Caddr;
    memset(&Caddr, 0, sizeof(Caddr));
    int Caddrlen = sizeof(Caddr);

    // 이미지 파일 사이즈 받기
    int dataSize = 0;

    errorCheck =  recvfrom(s, (char*)&dataSize, sizeof(dataSize), 0, (sockaddr*)&Caddr, &Caddrlen);
    if(errorCheck == SOCKET_ERROR){
        printf("recvfrom error!!\n ");
        return -1;
    }
    printf("받은 데이터 : %d\n", dataSize);
    
    // 받은 사이즈만큼 동적 할당
    char * recvbuf = (char*)malloc(dataSize);
    memset(recvbuf, 0, sizeof(recvbuf));

    // 이미지 파일을 받을 메모리버퍼
    char buf[1024] = {0}; 
    int totalszie = 0;
    int recvsize = 0;

    // 클라이언트가 보낸 데이트 받기
    while(1){
        recvsize = recvfrom(s, buf, sizeof(buf), 0, (SOCKADDR*)&Caddr, &Caddrlen);
        if(recvsize == 0){
            break;
        }
        // memcpy(복사받을 메모리포인터, 복사할 메모리포인터, 복사할 데이터의 길이);
        memcpy(&recvbuf[totalszie], buf, recvsize);
        totalszie += recvsize;
    }

    FILE * fp = NULL;
    fp = fopen("C:\\dev\\socket_programing\\server\\UDP\\test.jpg", "wb");
    fwrite(recvbuf, dataSize, 1, fp);
    fclose(fp);
    
    printf("통신완료!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}