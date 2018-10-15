#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(){
  stringstream ss;
  string s = "c.";
  system("nvidia-smi");
  system(("touch " + s + "out").c_str());
  ss << "mv " << "c.out " << "b.out";
  system(ss.str().c_str());
  return 0;
}
