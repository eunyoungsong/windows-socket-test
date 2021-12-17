/* UDP Client - 실습02-2. 이미지파일 */
#pragma comment (lib, "ws2_32.lib")
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
        printf("SOCKET ERROR!!\n");
        return -1;
    }

    /* 접속할 주소 구조체 생성 */
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    /* 서버에 데이터 송신 */

    // 파일 오픈 후 사이즈 재기
    FILE * fp = NULL;
    fp = fopen("../src/testImage.jpg", "rb");
    fseek(fp, 0, SEEK_END);
    int datasize = 0;
    datasize = ftell(fp);
    fclose(fp);

    // 서버에 파일 사이즈 보내기
    int error = 0;
    error = sendto(s, (char*)&datasize, sizeof(datasize), 0, (SOCKADDR*)&addr, sizeof(addr));
    if(error == SOCKET_ERROR){
        printf("sendto error!!\n");
        return -1;
    }

    // 파일 사이즈만큼 동적할당
    char * sendbuf = (char*)malloc(datasize);
    memset(sendbuf, 0, datasize);

    // 할당된 메모리에 이미지파일 넣기
    fp = fopen("../src/testImage.jpg", "rb");
    fread(sendbuf, datasize, 1, fp);
    fclose(fp);

    char buf[1024] = {0}; // 1024 만큼씩 보내겠다
    int size = 0;
    int sendsize = 1024;

    while(1){
        // memcpy(복사받을 메모리포인터, 복사할 메모리포인터, 복사할 데이터의 길이);
        memcpy(buf, &sendbuf[size], sendsize);
        
        sendsize = sendto(s, buf, sendsize, 0, (SOCKADDR*)&addr, sizeof(addr));
        
        if(sendsize == 0){
        // 다 보내면 빠져나오기
           break;
        }
        
        // 데이터사이즈에서 보낸만큼 빼주기
        datasize -= sendsize;
        // sendbuf[size] 잘라주는 범위 설정
        size += sendsize;

        // 남은 데이터 다 보내기 위해 보내는 사이즈 바꿔주기
        if(datasize < sendsize){
            sendsize = datasize;
        }

        printf("sendsize : %d\n", sendsize);
    }
    
    printf("통신완료!!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}