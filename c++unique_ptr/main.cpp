#include <iostream>
#include <memory>

using namespace std;

class A{
public:
  A(){ num = 0; }
  int get_num(){ return num; }
protected:
  int num;
};

int main(){
  auto a = unique_ptr<A>(new A);
  cout << a->get_num() << endl;
  return 0;
}
