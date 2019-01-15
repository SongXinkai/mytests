// g++ test0.cpp -I /usr/include/filesystem -L /usr/lib/x86_64-linux-gnu/ -lboost_filesystem  -lboost_system
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

using namespace std;

int main (){
  fs::path path("data/go");
  cout << path << endl;
  cout << path.has_filename() << endl;
  cout << path.filename() << endl;
  path /= "1.bin";
  cout << path << endl;
  cout << path.has_filename() << endl;
  cout << path.filename() << endl;
  cout << system_complete(path) << endl; // 
  cout << path.is_absolute() << endl;
  cout << path.extension() << endl;
  cout << path.root_path() << endl;
  cout << path.root_name() << endl;
  cout << path.relative_path() << endl;
  cout << path.root_directory() << endl;
  path = system_complete(path);
  cout << path.is_absolute() << endl;

  char file_name[] = "b";

  if ( 0 == access(file_name, 0) )  cout<<"access(): path exist."<<endl;
  return 0;
}

int get_filenames(const std::string& dir, std::vector<std::string>& filenames, bool recursive){
    fs::path path(dir);
    if (!fs::exists(path)){
        return -1;
    }
    fs::directory_iterator end_iter;
    for (fs::directory_iterator iter(path); iter!=end_iter; ++iter){
        if (fs::is_regular_file(iter->status())){
            filenames.push_back(iter->path().string());
        }
        if (recursive && fs::is_directory(iter->status())){
            get_filenames(iter->path().string(), filenames, recursive);
        }
    }
    return filenames.size();
}
