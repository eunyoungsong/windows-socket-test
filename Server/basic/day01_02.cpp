#include <stdio.h>

int add_func(int num1, int num2){
    int result = num1 + num2;
    return result;
}

int sub_func(int num1, int num2){
    int result = num1 - num2;
    return result;
}

int mul_func(int num1, int num2){
    int result = num1 * num2;
    return result;
}

float div_func(int num1, int num2){
    float result = (float)num1 / (float)num2;
    return result;
}

int main(){
   int su1 = 0;
   int su2 = 0;
   printf("first num : ");
   scanf("%d", &su1);
   printf("second num : ");
   scanf("%d", &su2);
   printf("%d + %d = %d\n", su1, su2, add_func(su1, su2));
   printf("%d - %d = %d\n", su1, su2, sub_func(su1, su2));
   printf("%d * %d = %d\n", su1, su2, mul_func(su1, su2));
   printf("%d / %d = %f\n", su1, su2, div_func(su1, su2));
} 