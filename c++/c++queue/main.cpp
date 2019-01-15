#include <queue>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

int main (){
  queue<int> q;
  cout << "q.empty(): " << q.empty() << endl;
  q.push(0);
  q.push(1);
  q.push(2);
  q.push(3);
  cout << "q.size(): " << q.size() << endl;
  cout << "q.front(): " << q.front() << endl;
  cout << "q.size(): " << q.size() << endl;
  cout << "q.back(): " << q.back() << endl;
  cout << "q.size(): " << q.size() << endl;
  q.pop();
  cout << "q.size(): " << q.size() << endl;
  cout << "q.front(): " << q.front() << endl;
  cout << "q.size(): " << q.size() << endl;
  cout << "q.back(): " << q.back() << endl;
  cout << "q.size(): " << q.size() << endl;
  //cout << "q.front(): " << q.pop() << endl;
  return 0;
}
