#include <iostream>
using namespace std;
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <vector>


using Date = struct {
  uint16_t year; /* год */
  uint16_t day; /* день месяца */
  uint16_t mon; /* месяц, январь=1 */
  int is_not_living;//1-live, 0-dead
  bool is_allowed_to_be;//1-allowed
};


int func(string * person, int size) {
  int k = 0;
  int index = 0;
  int max = 0;
  vector <int> temp = {0};
  for (int i = 0; i < size; ++i) {
    int allow =(int)person[i][8] - 48;
//    cout<<"MMM"<<!allow<<endl;
    if(!allow) {
      ++k;
    }
    else {
      temp.push_back(k);
      ++index;
//      //cout<<"maxI "<<max<<endl;
      k--;
      /*
      if(k < 0)
          //cout<<"ERROR"<<endl;
          */
    }
    for(int i = 0; i < temp.size(); ++i) {
      if (temp[i] > max) {
        max = temp[i];
      }
    }
  }
  return max;

}


void qsortRecursive(string *mas, int size) {
  //Указатели в начало и в конец массива
  int i = 0;
  int j = size - 1;
  // //cout<<i<<" "<<j<<endl;
  /*  for(int i = 0; i < size; ++i) {
     cout << mas[i] << endl;
   }*/
  //cout<<"size"<<size<<endl;

  //Центральный элемент массива
  string mid = mas[size / 2];

  //Делим массив
  do {
    //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
    //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
    while(mas[i] < mid ) {
      if(i == size / 2) {
        break;
      }
      i++;
      //cout<<"i "<<i<<endl;
    }// || (mas[i].dt == mid.dt && mas[i].is_living && mas[j].is_living != mid.is_living)
    //В правой части пропускаем элементы, которые больше центрального

    while (mas[j] > mid) {
      if(j == size / 2 ) {
        break;
      }
      j--;
      //cout<<"j "<<j<<endl;
    }

    //Меняем элементы местами
    if (i <= j) {

      string tmp = mas[i];
      mas[i]= mas[j];
      mas[j] = tmp;
      i++;
      j--;


    }
  }while(i <= j);

  if(j > 0) {
    //cout<<"левый кусок"<<endl;
    qsortRecursive(mas, j + 1);
  }
  if (i < size) {

    qsortRecursive(&mas[i], size - i);

  }
}

string To_String(uint32_t year, uint32_t month, uint32_t day){
  string a;
  for(int k = 1000; k >= 1; k /= 10){
    if (year / k < 1){
      a += "0";
      continue;
    }
    a += to_string(year);
    break;
  }
  if (month < 10) {
    a += "0";
    a += to_string(month);
  } else
    a += to_string(month);
  if (day < 10) {
    a += "0";
    a += to_string(day);
  } else
    a += to_string(day);
  return a;
}


int main() {
  int N;

  cin>> N;
  if(N == 0) {
    cout<<"0"<<endl;
    return 0;
  }

  Date person[2 * N];
  int man = 0;
  string person_all[2 * N];
  int index = 0;
  for(int i = 0; i < 2 * N; ++i) {

    if (i % 2 == 0) {
      man += 1;
      person[i].is_not_living = 0;
    }
    else {
      person[i].is_not_living = 1;
    }
    cin>>person[i].day>>person[i].mon>>person[i].year;
    //cout<<person[i].day<<person[i].mon<<person[i].year<<endl;
  }

  for (int i =0; i < 2 * N; i += 2) {
    person[i].year += 18;

    std::string a = "";//to_string(person[i].year);
    a += To_String(person[i].year, person[i].mon, person[i].day);
    //   cout<<"AAAAA " <<a<<endl;

    string dd = "";//to_string(person[i + 1].year);
    dd += To_String(person[i + 1].year, person[i+1].mon, person[i].day - 1);
//    cout<<"DDDDD " <<dd<<endl;


    if (a >= dd) {
      continue;
    } else {
//      cout<<"Cout "<<endl;
      string dd80 = "";
      dd80 += To_String(person[i].year + 80 - 18, person[i + 1].mon, person[i + 1].day - 1);
      //     cout<<"DD800000DD " <<dd80<<endl;//to_string(person[i].year + 80 - 18);

      dd = (dd > dd80 ? dd80 : dd);//конец участий, включительно
//     person_all[index].dt = a;
      //cout<<"ERROR"<<endl;
      a += to_string(person[i].is_not_living);
      dd += to_string(person[i + 1].is_not_living);

      person_all[index++] = a;
      person_all[index++] = dd;
    }
  }


  int size = index;
  qsortRecursive(person_all, size);

  int max = func(person_all, size);
  cout<<max<<endl;

  return 0;
}

