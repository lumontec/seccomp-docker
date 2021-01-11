#include <sys/types.h>
#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

/* On versions of glibc before 2.27, we must invoke copy_file_range()
   using syscall(2) */

int main(int argc, char **argv) {
  int fd_in, fd_out;
  struct stat stat;
  loff_t len, ret;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd_in = open(argv[1], O_RDONLY);
  if (fd_in == -1) {
    perror("open (argv[1])");
    exit(EXIT_FAILURE);
  }

  if (fstat(fd_in, &stat) == -1) {
    perror("fstat");
    exit(EXIT_FAILURE);
  }

  len = stat.st_size;

  fd_out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
  if (fd_out == -1) {
    perror("open (argv[2])");
    exit(EXIT_FAILURE);
  }

  loff_t buffin = 0;
  loff_t buffout = 2;

  ret = syscall(__NR_copy_file_range, fd_in, &buffin, fd_out, &buffout, len, 0);

  if (ret == -1) {
    perror("copy_file_range");
    exit(EXIT_FAILURE);
  }

  close(fd_in);
  close(fd_out);
  exit(EXIT_SUCCESS);
}
