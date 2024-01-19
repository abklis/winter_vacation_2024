#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void move(char l,char r)
{
	printf("%c->%c ", l, r);
}
void hanoi(int n , char a,char b,char c)
{
	if (n == 1)
		move(a, c);
	else
	{
		hanoi(n - 1, a, c, b);
		move(a, c);
		hanoi(n - 1, b, a, c);
	}
}
int main()
{
	int n = 3;
	char A = 'A', B = 'B', C = 'C';
	printf("n = %d: ", n);
	hanoi(n, A, B, C);
	return 0;
}