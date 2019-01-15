/*
 g++ multithreads_vector_correct_example.cpp -o multithreads_vector_correct -std=c++11 -pthread
*/
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include <time.h>

using namespace std;

void fn(vector<vector<float> >& vec){
  while(true){
    int len = vec.size();
    if (len > 0 && vec[len-1].size()>0){
      cout << "thread 1, vec.size() = " << len;
      cout << ", begin addr: "  << &*(vec.begin());
      cout << ", vec[-1][0] = " << vec[len-1][0] << endl;
    }
    sleep(0.2);
  }
}

int main(){
  vector<vector<float> > b;
  int N = 100000, M = 19*19*17;
  b.resize(N);
  for (int i = 0; i < N; ++i){
    b[i].resize(M);
  }
  cout << "b init done." << endl;
  thread t1(fn, ref(b));
  for (int i = 0; i < N; ++i){
    for (int j = 0; j < M; ++j){
      b[i][j] = float(j);
    }
  }
  t1.join();
  return 0;
}
