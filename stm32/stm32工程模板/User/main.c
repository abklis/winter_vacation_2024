#include "stm32f10x.h"                  // Device header

int main()
{
	RCC ->APB2ENR = 0X00000010;
	GPIOC ->CRH = 0X00300000;
	GPIOC ->ODR = 0X00002000;
	while(1);
	return 0;
}
