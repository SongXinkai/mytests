#include <iostream>
#include <functional>
#include <thread>
#include <atomic>

using namespace std;

void fn1 (int& a, int N){
  for (int i = 0; i < N; ++i){
    a ++;
  }
}

void fn2 (int& a, int N){
  for (int i = 0; i < N; ++i){
    a ++;
  }
}

void at_fn1 (atomic<int>* a, int N){
  for (int i = 0; i < N; ++i){
    (*a) ++;
  }
}

void at_fn2 (atomic<int>* a, int N){
  for (int i = 0; i < N; ++i){
    (*a) ++;
  }
}

int main(){
  int N = 100;

  int a = 0;
  int error_count = 0;
  for (int i = 0; i < N; ++i){
    a = 0;
    thread t1(fn1, ref(a), 10000);
    thread t2(fn2, ref(a), 10000);
    t1.join();
    t2.join();
    if (a != 20000) error_count ++;
  }
  cout << float(error_count) / N << endl;

  atomic<int> at_a(0);
  error_count = 0;
  for (int i = 0; i < N; ++i){
    at_a = 0;
    thread t1(at_fn1, &at_a, 10000);
    thread t2(at_fn2, &at_a, 10000);
    t1.join();
    t2.join();
    if (at_a.load() != 20000) error_count ++;
  }
  cout << float(error_count) / N << endl;
  return 0;
}
