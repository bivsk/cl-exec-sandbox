#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void fail(const char *message)
{
  fprintf(stderr, "cl-exec-sandbox-process-group: %s: %s\n", message,
          strerror(errno));
  _exit(125);
}

static void fail_message(const char *message)
{
  fprintf(stderr, "cl-exec-sandbox-process-group: %s\n", message);
  _exit(125);
}

int main(int argc, char **argv)
{
  if (argc < 3 || strcmp(argv[1], "--") != 0)
    fail_message("usage: cl-exec-sandbox-process-group -- PROGRAM [ARG ...]");
  if (setpgid(0, 0) != 0)
    fail("could not create process group");
  execv(argv[2], &argv[2]);
  fail("could not execute command");
  return 125;
}
