#include <iostream>
#include <vector>

using namespace std;

int main(){
  vector<int> a(5,1);
  cout << a.size() << endl;
  a.erase(a.begin()+2);
  cout << a.size() << endl;
  a.pop_back();
  cout << a.size() << endl;
  return 0;
}
