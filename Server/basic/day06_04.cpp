/* LESSON06.윈도우 소켓 초기화, 생성, 종료 */
/* 17차시 socket 동작방식 및 함수 소개    */
#pragma comment(lib, "ws2_32") 
// WS2_32.DLL : 동적라이브러리(DLL-Dynamic Linking library) : 기능들을 모아둔 집합
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    /*  Windows Socket 생성 */
    WSADATA wsa; 
    WSAStartup(MAKEWORD(2,2), &wsa); 
    /*  - MAKEWORD(2,2) : winsock 버전 (2.2버전) 
        - &wsa   : WSADATA 변수의 주소
        - 성공 0, 실패 시 오류코드                    */
    
    printf("winsock start 테스트");

    /* Windows Socket 종료 */
    WSACleanup();
    /*  int WSAcleanup(void);
        - 운영체제에 사용 중지 요청
        - 소켓의 자원 반환
        - 성공 시 0, 실패시 SOCKET_ERROR      */
    
    return 0;
}
