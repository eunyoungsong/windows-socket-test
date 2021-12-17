/* Thread : beginthreadex */
#include <stdio.h>
#include <windows.h>
#include <process.h>

unsigned __stdcall func1(void * arg){
    int i =0;
    for(i=0; i<100; i++){
        printf("i : %d\n", i);
    }
    return 0;
}
unsigned __stdcall func2(LPVOID arg){
    int j = 0;
    for(j=0; j<100; j++){
        printf("j : %d\n", j);
    }
    return 0;
}

int main(){

    printf("main() 시작\n");
    printf("Thread() 시작\n");

    unsigned long hThread1 = _beginthreadex(NULL, 0, func1, NULL, 0, NULL);
    unsigned long hThread2 = _beginthreadex(NULL, 0, func2, NULL, 0, NULL);

    while(1){
        printf("main()\n");
        Sleep(1000);
    }

    return 0;
}
