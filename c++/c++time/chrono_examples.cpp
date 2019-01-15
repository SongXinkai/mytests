// system_clock example
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using std::chrono::system_clock;
using std::chrono::high_resolution_clock;

int main ()
{

  std::chrono::duration<int,std::ratio<60*60*24> > one_day (1);
  std::chrono::duration<int,std::ratio<1> > one_sec (1);

  system_clock::time_point today = system_clock::now();
  system_clock::time_point tomorrow = today + one_day;

  std::time_t tt;

  tt = system_clock::to_time_t ( today );
  std::cout << "today is: " << ctime(&tt);

  tt = system_clock::to_time_t ( tomorrow );
  std::cout << "tomorrow will be: " << ctime(&tt);
  return 0;
}
