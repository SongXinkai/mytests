#include <iostream>
#include <fstream>

using namespace std;

int main(){
  ofstream f;
  f.open("out.txt", ios::app|ios::out);
  f << "line1, " << 1;
  f << ", " << 2;
  f << "\n";
  f << "line2, " << 1;
  f << ", " << 2;
  f << "\n";
  
  return 0;
}
