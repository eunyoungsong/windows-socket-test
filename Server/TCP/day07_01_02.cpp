/* 19차시 socket 통신에 필요한 함수 소개 */
/* TCP server 사용 예제_1 */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

    /*  bind 함수
        - 서버의 IP 주소와 포트 번호를 결정
        - 사용할 소켓 결정                  */
        
    
    /*  listen 함수
        - TCP 포트를 Listening 으로 설정
        - 클라이언트의 접속을 받을 준비 함수       */
    
    /*  acccept 함수
        - 클라이언트와 통신할 새로운 소켓을 생성 후 리턴
        - 접속할 클라이언트의 IP/Port 주소를 알 수 있음       */
    
    /*  recv 함수
        - 도착한 데이터를 수신하기 위해 수신버퍼에서 복사 함수 */
    
    /*  send 함수
        - 데이터를 전송하기 위해 송신버퍼에 복사 함수    */

    /*  connect 함수
        - 클라이언트 측의 함수
        - 접속 할 서버와 놀리적인 연결 설정      */
    
    /*  send 함수
        - 데이터를 전송하기 위해 송신버퍼에 복사 함수 */
    
int main(int argc, char *argv[]){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET SRVs; // 서버용 소켓 
    SRVs = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
    if(SRVs == INVALID_SOCKET){
        printf("SOCKET ERROR!!\n");
        return -1;
    }

     /* SOCKADDR_IN 구조체 : 소켓의 주소를 담는 기본 구조체 역할 */
    SOCKADDR_IN SRVAddr; // 주소 저장할 구조체
    memset(&SRVAddr, 0, sizeof(SRVAddr)); // 0 초기화
    int errorCheck;
    SRVAddr.sin_family = AF_INET; 
    SRVAddr.sin_port = htons(22222);
    SRVAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.35"); // 주소할당
    errorCheck = bind(SRVs, (sockaddr*)(&SRVAddr), sizeof(SRVAddr));
    /*  int bind(SECKET s, const struct sockaddr * name, int namelen);
        - SOCKET s                     : 접속을 허용할 소켓 지정
        - const struct sockaddr * name : IP/Port 주소를 담은 소켓 주소 구조체 
        - int namelen                  : 소켓 주소를 담은 구조체의 길이(바이트)
        - 리턴 값 : 성공 0, 실패 SOCKET_ERROR                                   */

    if(errorCheck == SOCKET_ERROR){
        printf("BIND ERROR!!\n");
        return -1;
    }

    // 소켓 오픈 (연결대기)
    errorCheck = listen(SRVs, SOMAXCONN);
    /*  int listen(SECKET s, int backlog)
        - SOCKET s     : bind 함수를 통해 IP/Port를 설정한 소켓
        - int backlong : 접속 가능한 클라이언트 개수,
                         최대값 SOMAXCONN (연결요청 대기 큐의 크기정보 전달)
        - 리턴 값 : 성공시 0, 실패시 SOCKET_ERROR                                   */
    if(errorCheck == SOCKET_ERROR){
        printf("LISTEN ERROR!!\n"); 
        return -1;
    }


    // 클라이언트 소켓
    SOCKET CiTs;
    // 클라이언트 주소 저장할 구조체
    SOCKADDR_IN CiTAddr; 
    memset(&CiTAddr, 0, sizeof(CiTAddr));
    int CiTLen = sizeof(CiTAddr);

    // 클라이언트 연결 허용 
    CiTs = accept(SRVs, (sockaddr*)(&CiTAddr), &CiTLen);
    /*  SOCKET accept(SOCKET s, struct sockaddr * addr, int * addreln);
        - SOCKET s               : TCP 포트를 listening 상태의 소켓
        - struct sockaddr * addr : 클라이언트의 IP/Port 정보를 저장할 주소 구조체
        - int * addrlen          : 주소를 담은 구조체의 길이(바이트)
        - 리턴 값 : 성공시 새로운 소켓, 실패시 INVALID_SOCKET                       */

    if(CiTs == INVALID_SOCKET){
        printf("ACCEPT ERROR!!\n");
        return -1;
    }

    // 클라이언트 데이터 수신
    char buf[100] = {0,};
    int recvSize = 0;
    memset(buf, 0, 100);
    recvSize = recv(CiTs, buf, sizeof(buf), 0);
    /*  int recv(SOCKET s, const char * buf, int len, int flags);
        - SOCKET s         : 통신 대상과 연결된 소켓
        - const char * buf : 받은 데이터를 저장할 버퍼 주소
        - int len          : 수신 버퍼에서 복사할 최대 데이터 크기
        - int flags        : recv 함수의 동작변경 옵션, 운영체제가 무시해서 사용 안됨=0
        - 리턴 값 : 성공시 보낸 데이터 바이트 수 , 실패시 SOCKET_ERROR                       */
    printf("수신 데이터 : %s\n", buf);
    printf("수신 데이터 크기 : %d\n", recvSize);
    
    closesocket(SRVs);

    WSACleanup();
    return 0;
}