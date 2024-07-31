void IO_getline(char* dest, int max) {
	for (*dest = 0, fgets(dest, max, stdin); *dest >= ' '; dest++);; *dest = 0;
}
int IO_read_int() {
	int a, b, c;
	while ((c = getchar()) && c < '-');
	for (b = c < '0' ? 0 : c & 0xf; (a = getchar()) >= '0'; b = b * 10 + (a & 0xf));
	return c == '-' ? -b : b;
}
void IO_write_int(int n) {
	int m = 1000000000;
	while (m > 1 && !(n / m)) { m /= 10; }
	do { putchar('0' | n / m); n %= m; } while (m /= 10);
	putchar('\n');
}

char buf_stdin[1 << 17];
char buf_stdout[1 << 17];
setvbuf(stdin, buf_stdin, _IOFBF, sizeof(buf_stdin));
setvbuf(stdout, buf_stdout, _IOFBF, sizeof(buf_stdout));

int string_tokenizer(char* tokens[], char* str) {
	int ch, i = 0;
	do {
		while ((ch = *str) == ' ') *str++ = '\0';
		if (ch) tokens[i++] = str++;
		while ((ch = *str) != ' ' && ch) str++;
	} while (ch);
	return i;
}
int string_compare(const char* a, const char* b) {
	while (*a && *a == *b) a++, b++;
	return *a - *b;
}
void string_copy(char* a, const char* b) {
	while (*a = *b++);
}
int string_length(const char* a) {
	const char* b = a;
	while (*b) b++;
	return b - a;
}
int string_parse_int(const char* str) {
	int a, b, c;
	while ((c = *str++) && c < '-');
	for (b = c < '0' ? 0 : c & 0xf; (a = *str++) >= '0'; b = b * 10 + (a & 0xf));
	return c == '-' ? -b : b;
}

/*
// Tokenizer <string.h> version

#define MAXTOK (999)
	char* tokens[MAXTOK];
	int tokens_size;
	tokens[(tokens_size = 0)] = strtok(buf, " ");
	while (++tokens_size < MAXTOK && (tokens[tokens_size] = strtok(NULL, " ")));

*/

/*
* 2024.2.5 Mon
* <string.h> imitation
* Reference of {compare, copy}: bloodstrawberry.tistory.com
*/