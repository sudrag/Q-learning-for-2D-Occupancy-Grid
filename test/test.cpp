/**
 * @file        : test.cpp
 * @author      : Sudarshan Raghunathan
 * @copyright   : 2017 Sudarshan Raghunathan
 * @brief       : Test functions for the Q learning class
 */
#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include "../include/Qlearn-class.hpp"

/**
 * @brief Helps identify right state for x,y locations
 */
TEST(Qclass, findState) {
  Qclass Test;
  EXPECT_EQ(Test.findState(0, 0), 0);
}
/**
 * @brief Checks if action chosen is between 0 and 3
 */
TEST(Qclass, detAction) {
  Qclass Test;
  EXPECT_LT(Test.detAction(2), 4);
  EXPECT_GT(Test.detAction(3), -1);
}
/**
 * @brief Checks if reward is assigned correctly
 */
TEST(Qclass, rewardfunc) {
  Qclass Test;
  EXPECT_LT(Test.rewardfunc(1, 0, 0), 0);
}
/**
 * @brief Helps identify right state for x,y locations
 */
TEST(Qclass, futurereward) {
  Qclass Test;
  EXPECT_EQ(Test.futurereward(2600), -100000);
}
/**
 * @brief Helps identify right state for x,y locations
 */
TEST(Qclass, Qupdate) {
  Qclass Test;
  Test.Qupdate(0, 0, 0, 0, 0);
  EXPECT_EQ(Test.Q[0][0], -25);
}
/**
 * @brief Checks if training is completed
 */
TEST(Qclass, Train) {
  Qclass Test;
  EXPECT_EQ(Test.Train(), 0);
}
/**
 * @brief Checks if goal was reached
 */
TEST(Qclass, execute) {
  Qclass Test;
  Test.Train();
  EXPECT_EQ(Test.execute(), 0);
}
/**
 * @brief Checks if plot was completed
 */
TEST(Qclass, plot) {
  Qclass Test;
  EXPECT_EQ(Test.plot(), 0);
}
