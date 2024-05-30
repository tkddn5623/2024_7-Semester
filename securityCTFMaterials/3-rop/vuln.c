#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SZ 64
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define RST "\x1B[0m"

int secret = 0x3a83cf38;

void win(int condition) {

  if (condition == secret)
    puts(GRN "You" RST);
  else
    puts(RED "You Lose" RST);

  if (condition == secret)
    puts(GRN "Win" RST);
  else
    puts(RED "You Lose" RST);
}

void vuln() {
  unsigned long esp;
  char buf[BUF_SZ];

  printf("Please enter your command >>> ");
  fflush(stdout);
  read(STDIN_FILENO, buf, 128);
}

int main() {
  printf("Welcome to *1990*'s server.\n");
  vuln();
}
