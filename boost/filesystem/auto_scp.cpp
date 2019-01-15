// g++ auto_scp.cpp -I /usr/include/filesystem -L /usr/lib/x86_64-linux-gnu/ -lboost_filesystem  -lboost_system
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

using namespace std;

int get_filenames(const std::string dir, std::vector<std::string>& filenames, bool recursive){
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

int main(){
  string ip="10.2.5.146";
  string username = "root";
  string passwd = "novacation";
  string remote_dir = "/root/tmp/";
  string dir_name("data_dir");
  string backup_dir("backup_dir");
  vector<string> file_vec;
  string s;
  while(true) {
    vector<string>().swap(file_vec);
    get_filenames(dir_name, file_vec, false);
    for (int i = 0; i < file_vec.size(); ++i){
      if (file_vec[i].find(".finish") == string::npos){
        continue;
      }
      string file_finish = file_vec[i];
      string file_bin = file_vec[i].substr(0, file_finish.find(".finish"));
      s = "sshpass -p \"" + passwd + "\" scp -o StrictHostKeyChecking=no " + file_bin + " " + username + "@" + ip + ":" + remote_dir;
      if (system(s.c_str())){
        cout << "scp " << file_bin << " fail." << endl;
        continue;
      }
      s = "sshpass -p \"" + passwd + "\" scp -o StrictHostKeyChecking=no " + file_finish + " " + username + "@" + ip + ":" + remote_dir;
      system(s.c_str());
      s = "mv " + file_bin + " " + backup_dir;
      system(s.c_str());
      s = "mv " + file_finish + " " + backup_dir;
      system(s.c_str());
    }
  } 
  return 0;
}
