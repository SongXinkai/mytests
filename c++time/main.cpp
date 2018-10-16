#include <unistd.h>
#include <iostream>
#include <time.h>

using namespace std;

int main(){
  time_t a = 0, b;
  if (a == 0){
    cout << "xx" << endl;
  }
  time(&a); // time.h
  sleep(4); // unistd.h
  time(&b);
  cout << a << ", " << b << endl;
  cout << b -a << endl;

  clock_t clc_a = 0, clc_b = 0;
  clc_a=clock(); // time.h
  sleep(4); // unistd.h
  clc_b=clock();
  cout << clc_a << ", " << clc_b <<", CLOCKS_PER_SEC: " << CLOCKS_PER_SEC<< endl;
  cout << (clc_b - clc_a) / CLOCKS_PER_SEC << endl;

  return 0;
}
