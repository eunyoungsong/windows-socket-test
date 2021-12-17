/* 동기화와 임계영역 예제 */
#include <stdio.h>
#include <Windows.h>
#include <process.h>

int A[100];
CRITICAL_SECTION cs; //임계영역 사용할 구조체 전역변수

unsigned __stdcall func1(void * arg){
    EnterCriticalSection(&cs); //공유자원 접근시작
    printf("func1\n");
    for(int i=0; i<100; i++){
        A[i] = 3;
        printf("%d", A[i]);
        Sleep(10);
    }
    LeaveCriticalSection(&cs); //공유자원 접근종료
    return 0;
}

unsigned __stdcall func2(void * arg){
    EnterCriticalSection(&cs); //공유자원 접근시작
    printf("func2\n");
    for(int j=99; j>=0; j--){
        A[j] = 4;
        printf("%d", A[j]);
        Sleep(10);
    }
    LeaveCriticalSection(&cs); //공유자원 접근종료
    return 0;
}

int main(){

    InitializeCriticalSection(&cs); //임계영역 생성
    printf("main() strat!\n");
    HANDLE hThread1, hThread2;
    hThread1 = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
    hThread2 = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    DeleteCriticalSection(&cs); //임계영역 종료
    printf("\n");
    return 0;
}