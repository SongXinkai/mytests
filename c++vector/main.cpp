#include <iostream>
#include <vector>

using namespace std;

int main(){
  vector<int> a(5,1);
  vector<int> b = {1,1,1,1,1};
  vector<int> c = {1,1,1};
  vector<int> d;
  d = a;
  cout << (a==b) << (a==c) << (a==d) << endl;
  cout << "a capacity: " << a.capacity() << ", addr: " << &*(a.begin()) << endl;
  cout << "b capacity: " << b.capacity() << ", addr: " << &*(b.begin()) << endl;
  cout << "c capacity: " << c.capacity() << ", addr: " << &*(c.begin()) << endl;
  cout << "d capacity: " << d.capacity() << ", addr: " << &*(d.begin()) << endl;
  return 0;
}
