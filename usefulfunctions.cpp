#include <iostream>
include <string>
#include <time.h>
#include <cmath>
using namespace std;

int time_left(float x,float y)
{
  return int(y-x/CLOCKS_PER_SEC)-1;
}

int convert_to_int(string x)
{
  int k = x.length();

  int i , r = 0;
  for(i=k-1;i>=0;i--)
  {
  
    r = r + pow(10,i)*(x[k-i-1]-'0');
  }

  return r;
}

int main()
{

return 0;

}
