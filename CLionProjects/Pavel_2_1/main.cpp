#include <iostream>

using namespace std;

int main()
{
    int **arr; // указатель для выделения памяти под массив
    int size; // размер массива

  // Ввод количества элементов массива
//  cout << "n = ";
  cin >> size;
/*
    if (size <= 0) {
      // Размер масива должен быть положитлеьным
        cerr << "Invalid size" << endl;
        return 1;
    }
*/
    arr = new int* [size]; // выделение памяти под массив

  // заполнение массива
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[2];
        for(int k = 0; k < 2; ++k) {
//      cout << "arr[" << i << "][" << k << "] = ";
            cin >> arr[i][k];
        }
    }

    int temp0 = 0;
    int temp1 = 0;// временная переменная для обмена элементов местами
// Сортировка массива пузырьком
    for (int i = 0; i < size - 1; ++i) {
      for (int j = 0; j < size - i - 1; ++j) {
        if (arr[j][0] > arr[j + 1][0]) {
          // меняем элементы местами
          temp0 = arr[j][0];
          arr[j][0] = arr[j + 1][0];
          arr[j + 1][0] = temp0;
          temp1 = arr[j][1];
          arr[j][1] = arr[j + 1][1];
          arr[j + 1][1] = temp1;
        } else if (arr[j][0] == arr[j + 1][0] && arr[j][1] > arr[j + 1][1]) {
          temp0 = arr[j][0];
          arr[j][0] = arr[j + 1][0];
          arr[j + 1][0] = temp0;
          temp1 = arr[j][1];
          arr[j][1] = arr[j + 1][1];
          arr[j + 1][1] = temp1;
        }
      }
    }

  // Вывод отсортированного массива на экран
  for (int i = 0; i < size; ++i) {
    for(int k = 0; k < 2; ++k) {
      cout << arr[i][k] << " ";
    }
    cout<< endl;
  }
  cout << endl;

  delete [] arr; // освобождение памяти;

  return 0;
}
