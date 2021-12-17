/* TCP server 사용 예제 실습용 */
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>
    
int main(int argc, char *argv[]){

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET s;
    //SOCKET s1;  //bind error test
    s = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
    if(s == INVALID_SOCKET){ //-1
        printf("SOCKET ERROR!!\n");
        return -1;
    }
    
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET; // IPv4
    addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.35"); //bind error test
    addr.sin_port = htons(22222);

    int errorch = bind(s, (sockaddr*)&addr, sizeof(addr));
    // bind 기본값은 (socket, sockaddr*, int) 형
    // 우리는 sockaddr_in 형태으로 선언했기 때문에 (sockaddr*) 로 형변환 필요
    if(errorch == SOCKET_ERROR){ //-1
        printf("bind error!!\n");
        return -1;
    }
    
    errorch = listen(s, SOMAXCONN);
    if(errorch == SOCKET_ERROR){
        printf("listen error!!\n");
        return -1;
    }
    // listen 확인 방법 : cmd : netstat -an
    // scanf("%d", &errorch); // listen 확인을 위해 종료되지 않게

    // 클라이언트용 
    SOCKADDR_IN clt_addr;
    int len = sizeof(clt_addr);
    SOCKET clt_s;

    printf("accep 실행 전\n");
    clt_s = accept(s, (sockaddr*)&clt_addr, &len);
    if(clt_s == INVALID_SOCKET){
        printf("accep error!!");
        return -1;
    }
    printf("accep 실행 후\n");
    printf("성공\n");

    // 데이터 수신
    char buf[1024] = {0,};
    int size = recv(clt_s, buf, sizeof(buf), 0);
    printf("수신 데이터 : %s\n", buf);
    printf("수신 데이터 크기 : %d\n", size);
    
    closesocket(s);
    WSACleanup();
    return 0;
}