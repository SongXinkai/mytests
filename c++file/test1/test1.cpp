#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

int main(){
  cout << fs::exists("a") << endl;
  cout << fs::exists("b") << endl;
  cout << fs::is_directory("b") << endl;
  return 0;
}
