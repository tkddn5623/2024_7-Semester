#include <stdio.h>

char buf_stdin[1 << 17];
char buf_stdout[1 << 17];

void write_int(int n) {
	int m = 1000000000;
	while (m > 1 && !(n / m)) { m /= 10; }
	do { putchar('0' | n / m); n %= m; } while (m /= 10);
	putchar('\n');
}
int read_int() {
	int a, b;
	while ((a = getchar()) && a < '0');
	for (b = a & 0xf; (a = getchar()) >= '0'; b = b * 10 + (a & 0xf));
	return b;
}
int main() {
	setvbuf(stdin, buf_stdin, _IOFBF, sizeof(buf_stdin));
	setvbuf(stdout, buf_stdout, _IOFBF, sizeof(buf_stdout));
	int N = read_int();
	for (int i = 0; i < N; i++) {
		int a = read_int(), b = read_int();
		write_int(a + b);
	}
	return 0;
}