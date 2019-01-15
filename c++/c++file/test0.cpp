#include <unistd.h>
#include <iostream>

using namespace std;

int main (){
  char file_name[] = "b";
  if ( 0 == access(file_name, 0) )  cout<<"access(): path exist."<<endl;
  return 0;
}
