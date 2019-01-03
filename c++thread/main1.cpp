#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

using namespace std;
mutex mtx;

void at_fn1 (atomic<int>* a, int N){
  for (int i = 0; i < N; ++i){
    (*a) ++;
  }
}

void mtx_fn2(vector<int> a) {
  mtx.lock();
  a.resize();
  mtx.unlock();
}

int main(){
  int N = 10, M = 100;
  vector<thread> my_ths;
  atomic<int> at_a(1);
  for (int i = 0; i < N; ++i){
    my_ths.emplace_back(at_fn1, &at_a, 10000);
  }
  for (auto &th: my_ths){
    th.join();
  }
  cout << at_a.load() << endl;
  return 0;
}
