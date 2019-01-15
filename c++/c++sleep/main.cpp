#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
  for (int i = 0; i < 10; ++i){
    sleep(1);
    cout << "1" << endl;
    usleep(500000);
    cout << "2" << endl;
  }
  return 0;
}
