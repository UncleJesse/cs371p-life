#define private public

#include <stdexcept>
#include "gtest/gtest.h"

#include "Life.h"


using namespace std;

 TEST(Test_ConwayCell, CC_constructor1) {
 	ConwayCell x(false);
 	ASSERT_TRUE(x.currentState == false);
 	ASSERT_TRUE(x.nextState == false);
 }

 TEST(Test_ConwayCell, constructor2) {
 	ConwayCell x(true);
 	ASSERT_TRUE(x.nextState == false);
 }

 TEST(Test_ConwayCell, constructor3) {
 	ConwayCell x(true);
 	ASSERT_TRUE(x.currentState == true);
 	ASSERT_TRUE(x.image == '*');
 }

 TEST(Test_ConwayCell, isAlive1) {
 	ConwayCell x(false); 	
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_ConwayCell, isAlive2) {
 	ConwayCell x(true); 
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_ConwayCell, isAlive3) {
 	ConwayCell x(false);
 	x.image = '*'; 
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_ConwayCell, determineNextState1) {
 	ConwayCell x(true);
 	vector<ConwayCell*> v;
 	for(int i=0; i<8; i++){
 		ConwayCell temp(true);
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_ConwayCell, determineNextState2) {
 	ConwayCell x(true);
 	vector<ConwayCell*> v;
 	for(int i=0; i<8; i++){
 		ConwayCell temp(false);
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_ConwayCell, determineNextState3) {
 	ConwayCell x(true);
 	vector<ConwayCell*> v;
 	ConwayCell a(true);
 	ConwayCell b(false);
 	ConwayCell c(true);
 	ConwayCell d(false);
 	ConwayCell e(false);
 	ConwayCell f(false);
 	ConwayCell g(false);
 	ConwayCell h(false); 
 	v.push_back(a);
 	v.push_back(b);
 	v.push_back(c);
 	v.push_back(d);
 	v.push_back(e);
 	v.push_back(f);
 	v.push_back(g);
 	v.push_back(h);
 	x.determineNextState(v);
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_TRUE(x.nextState);
 }

 TEST(Test_ConwayCell, updateCell1) {
 	ConwayCell x(true);
 	x.updateCell(); 
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_ConwayCell, updateCell2) {
 	ConwayCell x(false);
 	x.nextState = true;
 	x.updateCell();
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_ConwayCell, updateCell3) {
 	ConwayCell x(true);
 	vector<ConwayCell*> v;
 	for(int i=0; i<8; i++){
 		ConwayCell temp(false);
 		v.push_back(temp);
 	}
 	x.determineNextState(v);
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 }

 vector<ConwayCell*> v;
 

 /*TEST(Test_Life, Life_constructor1){
 	Life l(4, 4);
 	ASSERT_TRUE(l.board.size() == 0);
 }

 TEST(Test_Life, Life_constructor2){
 	Life l(4, 8);
 	ASSERT_TRUE(l.board.size() == 0);
 }

 TEST(Test_Life, Life_constructor3){
 	Life l(4, 4);
 	ASSERT_TRUE(l.rows == 4);
 	ASSERT_TRUE(l.cols == 4);
 }*/