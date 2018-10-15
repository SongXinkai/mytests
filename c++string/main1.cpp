#include <string>
#include <iostream>

using namespace std;

int main(){
  string a("aaaaassfaaaaa ff ");
  string b("ccc");
  string c("ff");
  cout << string::npos << endl;
  cout << a.find(b) << endl;
  cout << a.find(c) << endl;
  cout << a.find("f") << endl;
  return 0;
}
