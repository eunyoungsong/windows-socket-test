/* Thread : beginthreadex C언어 스레드 함수 */
#include <stdio.h>
#include <windows.h>
#include <process.h>

/* 스레드 함수 형태 */
unsigned __stdcall func1(void * arg){
    int i =0;
    for(i=0; i<100; i++){
        printf("func1 -> %d\n", i);
    }
    return 0;
}
unsigned __stdcall func2(LPVOID arg){
    int j = 0;
    for(j=0; j<100; j++){
        printf("func2 ---> %d\n", j);
    }
    return 0;
}

int main(){

    printf("main() 시작\n");
    printf("Thread() 시작\n");

    /* 스레드 생성 함수 */
    unsigned long hThread1 = _beginthreadex(NULL, 0, func1, NULL, 0, NULL);
    unsigned long hThread2 = _beginthreadex(NULL, 0, func2, NULL, 0, NULL);
    /*unsigned long _beginthreadex :  C언어 스레드 생성 함수
        ( void * security     : 핸들상속과 보안 디스크립터 정보 전달 시 사용,
          unsigned stack_size : 프로세스 안에 스레드가 사용할 스택 공간 크기(기본1MB),
          unsigned (__Stdcall *start_address)(void *) : 스레드로 실행할 함수의 주소,
          void * argl ist      : 스레드로 실행 할 함수에 전달할 인자 주소,
          unsigned initflag   : 스레드가 만들어지고 나서 언제 시작할지 여부 설정,
          unsigned * thrdaddr : 스레드 ID 저장될 변수 주소                              );  */


    while(1){
        printf("main()\n");
        Sleep(1000);
    }

    return 0;
}