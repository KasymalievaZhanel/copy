#include <stdio.h>

#define max 1

int a[11] = { 10, 14, 1};
int b[10];


int main() { 
   int i;

   printf("List before sorting\n");
   
   for(i = 0; i <= max; i++)
      printf("%d ", a[i]);

   int k = mergesort(0, max, a, b);

   printf("\nList after sorting\n %d", k);
   
   
/*   for(i = 0; i <= max; i++)
      printf("%d ", a[i]);
}*/
return 0;
}
