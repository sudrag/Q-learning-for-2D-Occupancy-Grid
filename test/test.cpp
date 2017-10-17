#include <gtest/gtest.h>
#include "../include/Qlearn-class.hpp"
#include <memory>

TEST(Qclass,findState) {
	Qclass Test;
	EXPECT_EQ(Test.findState(0, 0), 0);  //check if finding state correctly
}

TEST(Qclass,detAction) {
	Qclass Test;
	EXPECT_LT(Test.detAction(2), 4);
	EXPECT_GT(Test.detAction(3), -1);  //check if deciding relevant action
}

TEST(Qclass,rewardfunc) {
	Qclass Test;
	EXPECT_LT(Test.rewardfunc(1, 0, 0), 0); //check if assigning reward correctly
}

TEST(Qclass,futurereward) {
	Qclass Test;
	EXPECT_EQ(Test.futurereward(2600),-100000); //check if computing max Future value correctly
}

TEST(Qclass,Qupdate) {
	Qclass Test;
	Test.Qupdate(0, 0, 0, 0, 0);
	EXPECT_EQ(Test.Q[0][0], -25);  //check if computing max Future value correctly
}

TEST(Qclass,Train){
	Qclass Test;
	//Test.Train();
	EXPECT_EQ(Test.Train(),0);
}

TEST(Qclass,execute){
	Qclass Test;
	Test.Train();
	EXPECT_EQ(Test.execute(),0);
}

TEST(Qclass,plot){
	Qclass Test;
	//Test.plot();
	EXPECT_EQ(Test.plot(),0);
}
