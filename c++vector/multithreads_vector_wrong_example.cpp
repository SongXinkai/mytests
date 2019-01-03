/*
 g++ multithreads_vector_wrong_example.cpp -o multithreads_vector_wrong -std=c++11 -pthread
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
  thread t1(fn, ref(b));
  int N = 4000000, M = 19*19*17;
  for (int i = 0; i < N; ++i){
    vector<float> fea(M, i);
    b.push_back(fea);
    if ((int)b.size() == (int)b.capacity()){
      cout << &*(b.begin()) << ", " << &*(b.begin()+1) << ", " << &*(b[0].begin()) << ", " << &*(b[0].begin()+1) << ", capacity grow: " << (int)b.capacity() << endl;
    }
  }
  t1.join();
  return 0;
}
