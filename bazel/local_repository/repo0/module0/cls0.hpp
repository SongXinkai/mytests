#ifndef CLS0_HPP
#define CLS0_HPP

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class cls0 {
public:
  cls0();
  ~cls0();
  int get_count();
  void add_data(float );
private:
  int m_count;
  vector<float> m_data;
};
#endif
