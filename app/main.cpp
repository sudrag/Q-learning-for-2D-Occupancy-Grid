/**
 * @fileName    : main.cpp
 * @author      : Sudarshan Raghunathan
 * @copyright   : 2017 Sudarshan Raghunathan
 * @section DESCRIPTION
 * Qlearning class member function declarations
 */
#include <lib.hpp>
#include <iostream>
#include "Qlearn-class.hpp"
#include "Learn.cpp"

int main() {
  Qclass Q1;
  Q1.Train();
  Q1.execute();
  Q1.plot();
}
