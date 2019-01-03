/*
  g++ size_capacity.cpp -o size_capacity -pthread -std=c++11
*/
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

int main(){
  vector<long long> vec;
  clock_t clc_0 = 0, clc_1 = 0; 
  for (int i = 0; i < 100; ++i){
    vec.resize(pow(2, i+20)*10);
    cout << "old begin: " << &*(vec.begin());
    cout << ", old capacity: " << (long long)vec.capacity();
    clc_0 = clock();
    vec.push_back(0);
    clc_1 = clock();
    cout << ", new begin: " << &*(vec.begin());
    cout << ", push_back time: " << float(clc_1 - clc_0) / CLOCKS_PER_SEC;
    cout << ", size: " << (long long)vec.size();
    cout << ", capacity: " << (long long)vec.capacity() << endl;
  }
  return 0;
}
