#include <stdio.h>
#include"calc.h"
int main() {
    int a = 5;
    int b = 3;
    int sum = add(a, b);
    int difference = subtract(a, b);
    int product = multiply(a, b);
    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", difference);
    printf("Product: %d\n", product);
    return 0;
}