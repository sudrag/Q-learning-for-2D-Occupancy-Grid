/**
 * @file        : /app/main.cpp
 * @author      : Sudarshan Raghunathan
 * @copyright   : 2017 Sudarshan Raghunathan
 * @brief       : Qlearning class member function declarations
 */
#include <lib.hpp>
#include <iostream>
#include "Qlearn-class.hpp"
#include "Learn.cpp"

/**
   * @brief Main function to execute the code
   */
int main() {
  Qclass Q1;
  Q1.Train();
  Q1.execute();
  Q1.plot();
}
