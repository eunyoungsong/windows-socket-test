/* day01 함수실습 */
#include <stdio.h>

char change(char ch2){
    // small latter check
    if('a' <= ch2 && ch2 <= 'z'){
        return ch2-32; 
    }else{
        return ch2;
    }
}

int main(){
    char ch;
    printf("Alphabet : ");
    scanf("%c", &ch);
    char result = change(ch);
    printf("result : %c\n", result);
} 
