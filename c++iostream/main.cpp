/* 
  Reference:
    https://en.cppreference.com/w/cpp/header/iomanip
*/
#include <iostream>
#include <iomanip>

using namespace std;

int main (){
  cout << 12 << '\r';
  cout << 2 << '\r';
  cout << 3 << '\r' << endl;

  int a = 12;
  cout << "dec: " << dec << a << endl;
  cout << "hex: " << hex << a << endl;
  cout << "oct: " << setbase(10) << a << endl;
  cout << "oct: " << setbase(3) << a << endl;
  char *pt = "China";
  cout << setw(10) << pt <<endl;
  cout << setw(-10) << pt <<endl;
  cout << setfill('*') << setw(10) << pt << endl;
  cout << setfill('*') << setw(-10) << pt << endl;
  double pi = 22.0 / 7.0;
  cout << "pi = " << setprecision(2) << pi << endl;
  cout << setiosflags(ios::scientific);
  cout << "pi = " << setprecision(5) << pi << endl;
  cout << resetiosflags(ios::scientific);
  cout << "pi = " << setprecision(2) << pi << endl; // set precision
  cout << "pi = " << setiosflags(ios::fixed) << setprecision(4) << pi << endl; // set precision behind point
  return 0;
}
