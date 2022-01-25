#include <stdio.h>

long long int poly(long long int n,long long int a[n], long long int x0, long long i) {
	if (i == 1) {
		return a[i - 1] * x0 + a[i];
	} 
	else {
		return poly(n, a, x0, i - 1) * x0 + a[i];
	}
}

int main(int argc, char **argv)
{
	long long int n, x0;
	scanf("%lld%lld", &n, &x0);
	long long int a[n + 1];
	long long int b[n];
	for (long long int i = 0; i < n + 1; i++) {
		scanf("%lld", &a[i]);
	}
	for (long long int i = 0; i < n; i++) {
		b[i] = a[i] * (n - i);
	}
	printf("%lld %lld\n", poly(n + 1, a, x0, n), 
	poly(n, b, x0, n - 1));
	return 0;
}
