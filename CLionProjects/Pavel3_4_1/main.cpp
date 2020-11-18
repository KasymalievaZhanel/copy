
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

//Слияние
int* Merge(int *mas1, int *mas2, int s1, int s2, int SizeResult=0)
{
  SizeResult = (SizeResult == 0? s1 + s2: SizeResult);
  int *mas = new int[ SizeResult ];
  int n = 0;
  while (s1 && s2 && n < SizeResult)
  {
    if (*mas1 < *mas2)
    {
      mas[n] = *mas1;
      ++mas1;
      --s1;
    }
    else if(*mas1 >= *mas2)
    {
      mas[n] = *mas2;
      ++mas2;
      --s2;
    }

    ++n;
  }
  if (s1 == 0)
  {
    for (int i = 0; i < s2 && n < SizeResult; ++i)
    {
      mas[n++] = *mas2++;
    }
  }
  else
  {
    for (int i = 0; i < s1 && n < SizeResult; ++i)
    {
      mas[n++] = *mas1++;
    }
  }
  return mas;
}

//Сортировка слиянием
void MergeSort(int* Result, int Size)
{
  int f = 1, l, ost;
  int* mas;
  while (f < Size)
  {
    l = 0;
    while (l < Size)
    {
      if (l + f >= Size) {
        break;
      }
      ost = (l + f * 2 > Size) ? (Size - (l + f)) : f;

      mas = Merge(Result + l, Result + l + f, f, ost);

      for (int i = 0; i < f + ost; ++i)
        Result[l+i] = mas[i];

      delete[] mas;

      l += f * 2;

    }
    f *= 2;
  }
}

//Поиск первых `k` элементов в отсортированном массиве
void K_Sorted(int* Result, int* Mas, int k, int n)
{
  int first_index = k;
  int x;
  for(int i = 0; i < k; ++i)
  {
    scanf("%d", &x);
    Result[i] = x;
  }
  MergeSort(Result, k);
  int second_index = k;
  int* temp;
  while ( second_index < n )
  {
    for(int i = 0; i < k && second_index < n; ++i, ++second_index)
    {
      scanf("%d", &x);
      Mas[i] = x;
    }
    MergeSort(Mas, first_index);
    temp = Merge(Result, Mas, k, first_index, k);

    for (int p = 0; p < k; ++p)
      Result[p] = temp[p];

    delete[] temp;
  }
}


//Для ускорения ввода и вывода используем си-ввод/вывод:
int main()
{
  int n = 0;
  int k = 0;
  scanf("%d %d\n", &n, &k);
//  printf("%d\n", k);
  int* Result = new int [k];
  int* Mas = new int [k];
  K_Sorted(Result, Mas, k, n);
  for ( int i = 0; i < k; ++i)
  {
    printf("%d ", Result[i]);
  }
  printf("\n");
  delete[] Mas;
  delete[] Result;
  return 0;
}