#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(){
  string a("1.bin.finish");
  string b(".finish");
  string c("1.bin");
  vector<string> v;
  v.push_back(a);
  v.push_back(b);
  v.push_back(c);
  cout << string::npos << endl;
  cout << a.find(b) << endl;
  if (string::npos != a.find(b)){
    cout << a << " find " << b << ", at " << a.find(b) << endl;
    cout << a.substr(0, a.find(b)) << " + " << b << " = " << a << endl;
  }
  vector<string>::iterator it_str = find(v.begin(), v.end(), c);
  cout << (it_str == v.end()) << ", " << *it_str << endl;
  return 0;
}
