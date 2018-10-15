#include <random>
#include <iostream>

using namespace std;

static thread_local std::random_device g_random_device;
static thread_local std::minstd_rand g_random_engine(g_random_device());
int N = 100;

int main(){
  int min = 999999999;
  int max = -1;
  for (int i = 0; i < N; ++i){
    int a = g_random_engine();
    cout << int(g_random_engine() % 10) << ", ";
  }
  cout << endl;
  return 0;
}
