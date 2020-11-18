#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void print(int value) {
  char b;
  if (value < 0) {
    b = '-';
    write(1, &b, sizeof(b));
    value *= -1;
  }
  int d = 0;
  int temp = value;
  while (temp > 0) {
    temp /= 10;
    ++d;
  }
  char str[d];
  int i = d - 1;
  while (value > 0) {
    int s = value % 10;
    str[i] = '0' + s;
    value /= 10;
    i--;
  }
  write(1, str, d);
  b = ' ';
  write(1, &b, sizeof(b));
}

int main(int argc, char *argv[]) {
  int exit_code = 0;
  int in = open(argv[1], O_RDONLY);
  if (in == -1) {
    exit_code = 1;
    goto fin;
  }
  int in_b = 0;
  uint32_t in_four_byte;
  ssize_t in_read;
  while (1) {
    if((in_read = read(in, &in_b, sizeof(in_four_byte))) == 0){
      return 0;
    }
    print(in_b);
    read(in, &in_four_byte, sizeof(in_four_byte));
    if (in_four_byte == 0) {
      break;
    }
    lseek(in, in_four_byte, SEEK_SET);
  }
fin:
  close(in);
  return exit_code;
}
