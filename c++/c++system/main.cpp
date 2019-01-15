#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(){
  stringstream ss;
  string s = "c.";
  int a = system(("touch " + s + "out").c_str());
  cout << a << endl;
  ss << "mv " << "d.out " << "b.out";
  a = system(ss.str().c_str());
  cout << a << endl;
  return 0;
}
