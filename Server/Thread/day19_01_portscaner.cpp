/* 포트스캐너 */
#pragma comment(lib, "ws2_32")
#include <stdio.h>
#include <winsock2.h>

SOCKET sock1, sock2;
SOCKADDR_IN port_info;

DWORD WINAPI portscan1(LPVOID arg){

    /* 파일 생성 */
    FILE * fp1 = NULL;
    char buf[20] = {0};
    int port = ((int*)arg)[0];

    /* 윈속 생성 */
    WSADATA wsa;
    //WSAStartup(MAKEWORD(2,2), &wsa);
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf("WSAStartup error!");
        return -1;
    }

    for(; port<=((int*)arg)[1]; port++){

        /* 소켓 생성 */
        sock1 = socket(AF_INET, SOCK_STREAM, 0);
        if(sock1 == INVALID_SOCKET){
            printf("socket ERROR!!\n");
            return -1;
        }

        /* 주소 구조체 포트 설정 */
        port_info.sin_port = htons(port);

        int error = connect(sock1, (struct sockaddr*)&port_info, sizeof(port_info));
        if(error == SOCKET_ERROR){
            sprintf(buf, "%d port close!!\n", port);
        }else {
            sprintf(buf, "%d port open!!\n", port);
        }

        fp1 = fopen("C:\\dev\\socket_programing\\server\\Thread\\port1.txt", "a");
        fwrite(buf, sizeof(buf), 1, fp1);
        fclose(fp1);
    }

    return 0;
}

DWORD WINAPI portscan2(LPVOID arg){

    /* 파일 생성 */
    FILE * fp2 = NULL;
    char buf[20] = {0};
    int port = ((int*)arg)[0];

    /* 윈속 생성 */
    WSADATA wsa;
    //WSAStartup(MAKEWORD(2,2), &wsa);
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf("WSAStartup error!");
        return -1;
    }

    for(; port<=((int*)arg)[1]; port++){

        /* 소켓 생성 */
        sock2 = socket(AF_INET, SOCK_STREAM, 0);
        if(sock2 == INVALID_SOCKET){
            printf("socket ERROR!!\n");
            return -1;
        }

        /* 주소 구조체 포트 설정 */
        port_info.sin_port = htons(port);

        int error = connect(sock2, (struct sockaddr*)&port_info, sizeof(port_info));
        if(error == SOCKET_ERROR){
            sprintf(buf, "%d port close!!\n", port);
        }else {
            sprintf(buf, "%d port open!!\n", port);
        }

        fp2 = fopen("C:\\dev\\socket_programing\\server\\Thread\\port2.txt", "a");
        fwrite(buf, sizeof(buf), 1, fp2);
        fclose(fp2);
    }
    
    return 0;
}


int main(int argc, char ** argv){

    memset(&port_info, 0, sizeof(port_info));
    port_info.sin_family = AF_INET;
    port_info.sin_addr.s_addr = inet_addr("192.168.0.35");

    int portsu = atoi(argv[2]) - atoi(argv[1]) + 1;
    int port1[2], port2[2];
    int len = portsu/2;

    port1[0] = atoi(argv[1]);
    port1[1] = atoi(argv[1])+len;
    port2[0] = port1[1]+1;
    port2[1] = atoi(argv[2]);

    HANDLE handles[2];
    handles[0] = CreateThread(NULL, 0, portscan1, (LPVOID)port1, 0, NULL);
    handles[1] = CreateThread(NULL, 0, portscan2, (LPVOID)port2, 0, NULL);

    printf("스캔중.....\n");

    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    closesocket(sock1);
    closesocket(sock2);
    WSACleanup();
    return 0;
    
}