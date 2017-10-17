#include <iostream>
#include <lib.hpp>
#include "Qlearn-class.hpp"
#include "Learn.cpp"

int main()
{
   Qclass Q1;
   //Q1.createGrid();
   Q1.Train();
   Q1.execute();
   Q1.plot();
}
