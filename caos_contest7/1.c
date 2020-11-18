#include <sys/syscall.h>

long syscall(long number, ...);

//static const unsigned long long buf_size = 10;

void _start()
{

  while(1)
  {
   char Message[10] = "";

   int total_read = syscall(SYS_read, 0, Message, sizeof(Message));
   if (total_read == 0)
{ 
    break;
}
    syscall(SYS_write, 1, Message, total_read);
  }
  syscall(SYS_exit, 0);
}
