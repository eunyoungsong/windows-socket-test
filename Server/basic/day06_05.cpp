/* LESSON07.소켓함수 및 TCP서버-클라이언트 */
/* 18차시 socket 통신에 필요한 함수 소개 : socket 함수   */
/* SOCKET 함수 사용 예제 */

#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa); // socket 사용을 위해 반드시 필요!! 없으면 에러.

     /* 소켓 생성 */
    SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    /*  SOCKET socket(int af, int type, int protocol)
        - af       : 주소체계 지정 (IPv4 : AF_INET, IPv6 : AF_INET6)
        - tpye     : 소켓 타입 지정(TCP : SOCK_STREAM, UDP : SOCK_DGRAM)
        - protocol : 사용할 프로토콜 지정(IPPROTP_TCP)
        - 리턴 값 : 파일과 동일하게 소켓의 핸들 값(번호), 실패시 INVALID_SOCKET    */


    if(tcp_sock == INVALID_SOCKET) // -1 : 에러
    {
        printf("%d : 소켓 에러 socket error!!", tcp_sock);
        return 0;
    }
    printf("소켓 성공 socket success!!\n소켓 핸들 값 : %d", tcp_sock);
    closesocket(tcp_sock);

    WSACleanup();
    return 0;
}