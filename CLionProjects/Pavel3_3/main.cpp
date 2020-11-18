#include <iostream>
#include <vector>
//#include <algorithm>

void medianOfThree (std::vector<int>&, int, int); // Установка медианы в нужное место
int partition (std::vector <int> &, int, int); // Нахождение места элемента
int K_Statistic (std::vector<int>&, int, int, int); //к-я статистика

int main ()
{
  int n = 0;
  std::cin >> n;
  int k = 0;
  std::cin >> k;
  std::vector<int> vec(n, 0);
  for (int i = 0; i < n ; ++i)
  {
    std::cin >> vec[i];
  }

  std::cout << K_Statistic (vec, 0, n - 1, k);

// nth_element ( a.begin(), a.begin() + k, a.end() );
// std::cout << a[k];
}

int K_Statistic (std::vector<int>& vec, int begin, int end, int k)
{
  // Модификация quick_sort для поиска к-й статистики

  int p = -1;
  while ( p != k )
  {
    p = partition (vec, begin, end);
    if (p < k)
      begin = p + 1;
    else
      end = p - 1;
  }

  return vec[k];
}

void medianOfThree (std::vector<int>& a, int left, int right)
{
  // Установка элементов с индексами left, right, ( left + right ) / 2
  // В порядке [средний, минимальный, максимальный] на позиции
  // [left, ( left + right ) / 2, right]
  // т.е. на месте a[left] становится средний из 3х элементов
  int mid = ( left + right ) / 2;
  if (a[mid] > a[right])
    std::swap (a[mid], a[right]);
  if (a[left] < a[mid])
    std::swap ( a[left], a[mid]);
  if (a[left] > a[right])
    std::swap (a[left], a[right]);
}

int partition (std::vector <int> &a, int left, int right)
{
  // Метод прохода двумя итераторами от конца массива к началу.
  medianOfThree( a, left, right);
  int i = right;//максимальный
  int j = right;
  bool step = false;

  while (j > left)//макс > средний
  {
    // Ускорение для повторяющихся элементов
    while (a[left] == a[j] && j > left)
    {
      if (step)
        std::swap(a[i--], a[j--]);
      else
        --j;
      step =! step;
    }

    while (a[j] < a[left] && j > left)
      --j;

    while (a[j] > a[left] && j > left)
      std::swap(a[j--], a[i--]);
  }
  std::swap (a[left], a[i]);

  return i;
}

