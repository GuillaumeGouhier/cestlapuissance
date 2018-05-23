#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int random_column(void) {
  srand(time(NULL));
  int i = rand() % 8;
  return i;
}
