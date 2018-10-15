#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
  for (int i = 0; i < 10; ++i){
    sleep(2);
    cout << "1" << endl;
    usleep(2000000);
    cout << "2" << endl;
  }
  return 0;
}
