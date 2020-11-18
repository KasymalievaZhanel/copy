#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

void print(int value) {
  char b;
  if (value < 0) {
    b = '-';
    write(1, &b, sizeof(b));
    value *= -1;
  }
  int number_of_indexes = 0;
  int temp = value;
  while (temp > 0) {
    temp /= 10;
    ++number_of_indexes;
  }
  char str[number_of_indexes];
  int i = number_of_indexes - 1;
  while (value > 0) {
    int s = value % 10;
    str[i] = '0' + s;
    value /= 10;
    i--;
  }
  write(1, str, number_of_indexes);
  b = ' ';
  write(1, &b, sizeof(b));
}


int
 main (int argc, char **argv) {
   int exit_code = 0;
   int in = open(argv[1], O_RDONLY);
   if (in == -1) {
     exit_code = 1;
     goto finally;
   }
   struct Item data;
   ssize_t in_read;
   while (1) {
     if((in_read = read(in, &data, sizeof(data))) == 0){
        return 0;
     }
     print(data.value);
     if (data.next_pointer == 0) {
        break;
     }
     lseek(in, data.next_pointer, SEEK_SET);
   }
   finally:
     close(in);
     return exit_code;
 }
