//
// Created by guangsujiqiang on 3/17/20.
//
inline int MAX(int a, int b)
{
	return a > b ? a : b;
}

int a[] = { 9, 3, 5, 2, 1, 0, 8, 7, 6, 4 };

int max(int n)
{
	return n == 0 ? a[0] : MAX(a[n], max(n-1));
}

int main(void)
{
	max(9);
	return 0;
}
