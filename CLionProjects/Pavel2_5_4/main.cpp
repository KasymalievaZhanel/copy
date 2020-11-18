#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>

/*
void HeapSort(std::vector<uint32_t >& values) {
  std::make_heap(values.begin(), values.end());
  for (auto i = values.end(); i != values.begin(); --i) {
    std::pop_heap(values.begin(), i);
  }
}
     */
int Summ(const std::vector<uint32_t >& values, int L) {
  uint32_t Summ = 0;
  for(uint32_t i = 0; i < values.size(); ++i){
    if (i % 2 == 0){
      Summ += values[i];
    }
  }
  Summ %= L;
  return Summ;
}


/*
//using namespace std;

// Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является
// индексом в arr[]. n - размер кучи

void heapify(std::vector<uint32_t >& arr, int n, int i)
{
    int largest = i;
// Инициализируем наибольший элемент как корень
    int l = 2*i + 1; // левый = 2*i + 1
    int r = 2*i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
    if (l < n && arr[l] >= arr[largest])
        largest = l;

   // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[r] >= arr[largest])
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void HeapSort(std::vector<uint32_t >& arr, int n)
{
  // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

   // Один за другим извлекаем элементы из кучи
    for (int i=n-1; i>=0; i--)
    {
        // Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

/* Вспомогательная функция для вывода на экран массива размера n*/
void printArray(int arr[], int n)
{
    for (int i=0; i<n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

*/


int main() {
  uint64_t N;
  uint64_t K;
  uint64_t M;
  uint64_t L;
  std::cin >>N>> K>> M>> L;
  std::vector <uint32_t> a(N);
  a[0] = K;
//std::cout<<a[0]<<std::endl;
  for (int i = 0; i < N-1; i++) {
    a[i+1] = (unsigned int)((a[i]*(unsigned long long)M)&0xFFFFFFFFU) % L;
//    std::cout<<a[i + 1]<<std::endl;
  }
//  HeapSort(a, a.size());
/*
  for (int i = 0; i < N; i++) {
    std::cout<<a[i]<<std::endl;
  }
  */

  uint32_t summ = Summ(a, L);
  std::cout<<summ;
  return 0;


}


#include<list>
#include<cmath>
using namespace std;

void display(int *array, int size) {
   for(int i = 0; i<size; i++)
      cout << array[i] << " ";
   cout << endl;
}

void radixSort(int *arr, int n, int max) {
   int i, j, m, p = 1, index, temp, count = 0;
   list<int> pocket[10];      //radix of decimal number is 10
   for(i = 0; i< max; i++) {
      m = pow(10, i+1);
      p = pow(10, i);
      for(j = 0; j<n; j++) {
         temp = arr[j]%m;
         index = temp/p;      //find index for pocket array
         pocket[index].push_back(arr[j]);
      }
      count = 0;
      for(j = 0; j<10; j++) {
         //delete from linked lists and store to array
         while(!pocket[j].empty()) {
            arr[count] = *(pocket[j].begin());
            pocket[j].erase(pocket[j].begin());
            count++;
         }
      }
   }
}

int main() {
   int n, max;
   cout << "Enter the number of elements: ";
   cin >> n;
   cout << "Enter the maximum digit of elements: ";
   cin >> max;
   int arr[n]; //create an array with given number of elements
   cout << "Enter elements:" << endl;
   for(int i = 0; i<n; i++) {
      cin >> arr[i];
   }
   cout << "Data before Sorting: ";
   display(arr, n);
   radixSort(arr, n, max);
   cout << "Data after Sorting: ";
   display(arr, n);
}