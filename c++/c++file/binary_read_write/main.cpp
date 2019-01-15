// g++ main.cpp -std=c++11
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

void read(const string file, vector<vector<float> >& feas, 
    vector<vector<float> >& pis, vector<float>& vs){
  int steps_in = 0;
  int winner_in = 0;
  char feas_in[1000 * 17*19*19];
  float pis_in[1000 * 362]; 
  std::ifstream input(file, ios::in | ios::binary);
  input.read((char*)&steps_in, sizeof(int));
  // CHECK_LE(steps_in, 1000);
  input.read((char*)&winner_in, sizeof(int));
  input.read((char*)feas_in, sizeof(char) * 19*19*17 * steps_in);
  input.read((char*)pis_in, sizeof(float) * (19*19+1) * steps_in);
  input.close();
  feas.resize(steps_in);
  pis.resize(steps_in);
  vs.resize(steps_in);
  for (int step = 0; step < steps_in; ++step){
    feas[step].resize(17*19*19);
    pis[step].resize(1+19*19);
    for (int j = 0; j < 17*19*19; ++j){
      feas[step][j] = feas_in[step*17*19*19 + j] ? 1.0 : 0.0;
    }
    for (int j = 0; j < 1+19*19; ++j){
      pis[step][j] = pis_in[step*(1+19*19)+j];
    }
    if ((step%2==0)^(winner_in==1)){ // self lose
      vs[step] = -1.0;
    }else{
      vs[step] = 1.0;
    }
  }
}

void write(const string file){
  int steps_out = 400;
  int winner_out = 1; // 1: black win, 0: white win
  unsigned char* feas_out = new unsigned char[steps_out * 17*19*19];
  float* pis_out = new float[steps_out * 362];
  srand((int)time(0));
  for (int i = 0; i < steps_out; ++i){
    int position_0 = int(361.0 * rand()/(RAND_MAX+1.0));
    int position_1 = int(361.0 * rand()/(RAND_MAX+1.0));
    while(position_1 == position_0){
      position_1 = int(361.0 * rand()/(RAND_MAX+1.0));
    }
    for (int c = 0; c < 16; ++c){
      feas_out[i*17*19*19+position_0*17+c] = (unsigned char)1;
    }
    for (int c = 0; c < 2; ++c){
      feas_out[i*17*19*19+position_1*17+c] = (unsigned char)1;
    }
    pis_out[i * 362 + position_0] = 0.9;
    pis_out[i * 362 + position_1] = 0.1;

    for (int j = 0; j < 19*19; ++j){
      feas_out[i*17*19*19+j*17+16] = (i%2==0) ? (unsigned char)1 : (unsigned char)0;
    }
  }
  std::ofstream output(file, ios::out | ios::binary );
  output.write((char*)&steps_out, sizeof(int));
  output.write((char*)&winner_out, sizeof(int));
  output.write((char*)feas_out, sizeof(char) * 19*19*17*steps_out);
  output.write((char*)pis_out, sizeof(float) * (19*19+1) * steps_out);
  output.close();
  std::ofstream finish_out(file+".finish", ios::out | ios::binary );
  finish_out.close();
}

int main (){
  stringstream ss;
  // for (int i = 0; i < 1000; ++i){
  //   ss.str("");
  //   ss << "go/" << i << ".bin";
  //   write(ss.str());
  // }
  vector<vector<float> > feas;
  vector<vector<float> > pis;
  vector<float> vs;
  read("0.bin", feas, pis, vs);
  cout << feas.size() << ", " << pis.size() << ", " << vs.size() << ", " << endl;
  for (int i = 0; i < feas.size(); ++i){
    cout << "========" << i << "======" << endl;
    for (int j = 0; j < 19*19; ++j){
      cout << j << ": ";
      for (int c = 0; c < 17; ++c){
        cout << feas[i][j*17+c] << ", ";
      }
      cout << endl;
    }
    for (int j = 0; j < pis[i].size(); ++j){
      if (pis[i][j] != 0){
        cout << "(" << j << "-" << pis[i][j] << "), ";
      }
    }
    cout << endl << vs[i] << endl;
  }

  return 0;
}
