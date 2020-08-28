#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "algorytm.h"

bool answer;

using namespace std;
void start ()
{
    do
   {
      answer = cycle();
   } while (answer);

}
