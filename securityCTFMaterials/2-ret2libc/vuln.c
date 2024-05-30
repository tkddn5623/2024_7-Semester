#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SZ 64

void vuln() {
  unsigned long esp;
  char buf[BUF_SZ];

  // Inline assembly to read esp
  /* asm("mov %%esp, %0" : "=r"(esp)); */

  /* printf("vuln's addr = 0x%08lx\n", &vuln); */
  printf("Please enter your command >>> ");
  fflush(stdout);
  read(STDIN_FILENO, buf, 128);
}

int main() {
  printf("Welcome to *1990*'s server.\n");
  vuln();
}
