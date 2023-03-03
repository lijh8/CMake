#include <stdio.h>
#include <signal.h>
#include <sanitizer/lsan_interface.h>
#include "foo.h"

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
  int a[1024];
  int n = 102400;
  a[n] = 1;

}
