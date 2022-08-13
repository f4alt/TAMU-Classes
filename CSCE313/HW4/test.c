#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
  /* <here you do your magic with dup2() to ensure that
      all output goes to stdout.> */
  dup2(1, 2);


  /* Once everything is set up, call the toy program. */
  execve("./toy", NULL, NULL);
}
