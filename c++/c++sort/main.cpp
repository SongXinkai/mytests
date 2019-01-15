#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

/*    
  For lambda: 
    g++ main.cpp -std=c++11
*/

using namespace std;

bool my_compare_pair(pair<int, float> a, pair<int, float> b){
  return a.second < b.second;
}

int main(){
  vector<pair<int, float> > vec_pair;
  vector<float> vec_f;
  vector<int> vec_idx;
  const int len = 10;
  int a[len];
  for (int i = 0; i < len; i++){
    vec_pair.push_back(make_pair(i, 0.1 * (len - i)));
    vec_f.push_back(0.1 * (len - i));
    vec_idx.push_back(i);
    a[i] = i;
  }

  sort(vec_pair.begin(), vec_pair.end(), my_compare_pair);
  for (int i = 0; i < len; i++){
    cout << vec_pair[i].first << ", ";
  }
  cout << endl;

  sort(a, a+len, 
            [](int a, int b){
                return (a > b);
            }
        );
  for (int i = 0; i < len; ++i)
    cout << a[i] << ", ";
  cout << endl;

  sort(vec_idx.begin(), vec_idx.end(), 
            [vec_f](int a, int b){
                return vec_f[a] > vec_f[b];
            }
        );
  for (int i = 0; i < len; i++){
    cout << vec_idx[i] << ", ";
  }
  cout << endl;
  return 0;
}
