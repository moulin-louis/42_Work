#include <stdio.h>

void toto(void) {
  printf("This is toto fn\n");
}

int main(void) {
  printf("Hello from test.c\n");
  toto();
  return 0;
}