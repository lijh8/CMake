#include "foo.h"
#include <sanitizer/lsan_interface.h>
#include <signal.h>
#include <stdio.h>

void handlerCont(int signum) {
  printf("SIGCONT %d\n", signum);
#ifndef NDEBUG
  __lsan_do_recoverable_leak_check();
#endif
}

int main() {
  signal(SIGCONT, handlerCont); // kill -CONT 123 # pid
  //...
  printf("main\n");
  foo();

  int a[3];
  int i = 0;

  // i = 3;      // ok, reported

  // i = 102400; // not reported?

  a[i] = 1;

  return 0;
}
