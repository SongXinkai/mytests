#include <iostream>
#include <vector>

using namespace std;

int main(){
  const int len0 = 3;
  int len1 = 3;
  int aa[len0] = {1,2,3};
  int bb[len1] = {11,22,33};
  cout << "aa: " << aa[0] << ", " << aa[1] << ", " << aa[2] << ", " << aa[3] << endl;
  cout << "bb: " << bb[0] << ", " << bb[1] << ", " << bb[2] << ", " << bb[3] << endl;
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
