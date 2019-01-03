//#include <thread>
#include <functional>

void fn(int& a){a ++;}
int main (){
  int a = 0;
  std::ref(a) ++;
  //std::thread t(fn, std::ref(a));
  //t.join();
  return 0;
}
