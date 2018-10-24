#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

void i2s(int i, string& s){
  stringstream ss;
  ss << i;
  ss >> s;
}

void s2i(string s, int& i){
  stringstream ss(s);
  ss >> i;
}

vector<string> string_split(const string &s, const string &seperator){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;
  while(i != s.size()){
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i] == seperator[x]){
          ++i;
          flag = 0;
          break;
        }
    }
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
          flag = 1;
          break;
        }
      if(flag == 0) 
      ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

int main(){
  //int i1 = 199, i21, i22;
  //string s1, s2="288_377", s3 = "finish";
  //i2s(i1, s1);
  //vector<string> vec_s = string_split(s2, "_");
  //s2i(vec_s[0], i21);
  //s2i(vec_s[1], i22);
  //cout << ("finish" == s3) << ", " << ("288" == s3) << endl;
  //cout << i1 << ", " << s1 << endl;
  //cout << s2 << ", " << i21 << " _ " << i22 << endl;

  vector<string> vec_s_0 = string_split("model-10000.uff", "model-");
  vector<string> vec_s_1 = string_split(vec_s_0[0], ".uff");
  int i;
  s2i(vec_s_1[0], i);
  cout << i << endl;
  return 0;
}
