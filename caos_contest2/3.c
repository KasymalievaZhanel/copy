#include <stdio.h>
#include <stdint.h>

int main(int args, char* argv[]) {
  for (int i = 1; i < args; ++i) {
    uint64_t lenth = 0;
    uint8_t flag = 0; 
    for(int k = 2; argv[i][k] != '\0'; ++k) {
        if (argv[i][k] != '0') {
           flag = 1;
           lenth += 4;
        }
        if (argv[i][k] == '0') {
            if(flag == 0) {
                continue;
            }
            else
               lenth += 4;
   }
    
