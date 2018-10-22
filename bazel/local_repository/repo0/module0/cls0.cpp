#include "cls0.hpp"

cls0::cls0(){
  m_count = 0;
}

cls0::~cls0(){
}

int cls0::get_count(){
  return m_count;
}

void cls0::add_data(float dat){
  m_data.push_back(dat);
  m_count ++;
}
