#include <unistd.h>
#include <sys/syscall.h>
#include <iostream>
#include <string>

using namespace std;

void print_pid(char* s, int& a){
  cout << s << ", pid: " << syscall(__NR_getpid) << ", tid: " << syscall(__NR_gettid) << endl;
  s = "2";
  a ++;
}

int main(){
  int a = 0;
  print_pid("1", a);
  char* s = "sxk ";
  pid_t child_pid;
  child_pid = fork();
  print_pid(s, a);
  cout << a << ", " << &a << endl;
  child_pid = fork();
  print_pid(s, a);
  cout << a << ", " << &a << endl;
  child_pid = fork();
  print_pid(s, a);
  cout << a << ", " << &a << endl;
  return 0;
}
