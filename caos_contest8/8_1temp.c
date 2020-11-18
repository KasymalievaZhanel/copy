#include <windows.h>


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

LARGE_INTEGER intToLargeInt(int integ) {
   LARGE_INTEGER li;
   li.QuadPart = integ;
   return li;
}

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


int main(int argc, char *argv[]) {
  int exit_code = 0;
  HANDLE in = CreateFileA(argv[1], GENERIC_READ, 0, NULL,
                          OPEN_EXISTING, 0, NULL);
  if (in == INVALID_HANDLE_VALUE) {
    exit_code = 7;
    goto finally;
  }
  int in_value = 0;
  uint32_t in_pointer_to_next;
  BOOL in_read;
  LPDWORD lpNumberOfBytesRead;
  while (1) {
    if((in_read = ReadFile(in, &in_value, sizeof(int), lpNumberOfBytesRead,
         NULL)) == TRUE && *lpNumberOfBytesRead == 0){
      return 0;
    }
    print(in_value);
    ReadFile(in, &in_pointer_to_next, sizeof(uint32_t), lpNumberOfBytesRead,
             NULL);
    if (in_pointer_to_next == 0) {
      break;
    }
    uint32_t integ = in_pointer_to_next;
    SetFilePointerEx(in, intToLargeInt(integ), NULL, 0);
  }
  finally:
    CloseHandle(in);
    return exit_code;
}
