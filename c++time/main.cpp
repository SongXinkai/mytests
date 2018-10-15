#include <unistd.h>
#include <iostream>
#include <time.h>

using namespace std;

int main(){
  time_t a = 0, b;
  if (a == 0){
    cout << "xx" << endl;
  }
  time(&a);
  sleep(4);
  time(&b);
  cout << a << ", " << b << endl;
  cout << b -a << endl;
  return 0;
}
