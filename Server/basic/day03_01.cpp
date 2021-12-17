/* day03 포인터&구조체 */
#include <stdio.h>
#include <malloc.h>

int main(){

    int num;
    printf("How many letters is your name? : ");
    scanf("%d", &num);
     
    char * name = (char *)malloc(num);
    //void * v = malloc(num); // heap 에 num 만큼의 공간 할당
    //char * p (char * )v;
    //char nmae[num];
    printf("What's your name? : ");
    scanf("%s", &name);
    printf("name : %s", name);

    free(name); // 공간 지워주기
    printf("name : %s", name);
    
    return 0;
}