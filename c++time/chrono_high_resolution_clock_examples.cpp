// high_resolution_clock example
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
  std::cout << std::endl;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  
  
  std::cout<<"in seconds time:";
  duration<double,std::ratio<1,1>> duration_s(t2-t1);
  std::cout<<duration_s.count()<<" seconds"<<std::endl;
  
  std::cout<<"in millisecond time:";
  //duration<double,std::ratio<1,1000>> duration_ms(t2-t1);
  duration<double,std::ratio<1,1000>> duration_ms=duration_cast<duration<double,std::ratio<1,1000>>>(t2-t1);
  std::cout<<duration_ms.count()<<" milliseconds"<<std::endl;
  
  std::cout<<"in microsecond time:";
  //duration<double,std::ratio<1,1000000>> duration_ms(t2-t1);
  duration<double,std::ratio<1,1000000>> duration_mcs=duration_cast<duration<double,std::ratio<1,1000000>>>(t2-t1);
  std::cout<<duration_mcs.count()<<" microseconds"<<std::endl;
  

  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "It took me " << time_span.count() << " seconds.";
  std::cout << std::endl;

  return 0;
}
