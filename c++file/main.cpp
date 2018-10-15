#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

int main(){
  //cout << fs::exist("a") << endl;
  //cout << fs::exist("b") << endl;
  cout << fs::is_directory("b") << endl;
  return 0;
}
