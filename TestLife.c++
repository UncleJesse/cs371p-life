#define private public

#include <stdexcept>
#include "gtest/gtest.h"

#include "Life.h"


using namespace std;

 TEST(Test_ConwayCell, CC_constructor1) {
 	ConwayCell x('.');
 	ASSERT_TRUE(x.currentState == false);
 	ASSERT_TRUE(x.nextState == false);
 }

 TEST(Test_ConwayCell, CC_constructor2) {
 	ConwayCell x('*');
 	ASSERT_TRUE(x.nextState == false);
 }

 TEST(Test_ConwayCell, CC_constructor3) {
 	ConwayCell x('*');
 	ASSERT_TRUE(x.currentState == true);
 	ASSERT_TRUE(x.image == '*');
 }

 TEST(Test_ConwayCell, CC_isAlive1) {
 	ConwayCell x('-'); 	
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_ConwayCell, CC_isAlive2) {
 	ConwayCell x('*'); 
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_ConwayCell, CC_isAlive3) {
 	ConwayCell x('.');
 	x.currentState = true; 
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_ConwayCell, CC_determineNextState1) {
 	ConwayCell x('*');
 	vector<AbstractCell*> v;
 	for(int i=0; i<8; i++){
 		ConwayCell* temp = new ConwayCell(true);
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_ConwayCell, CC_determineNextState2) {
 	ConwayCell x('*');
 	vector<AbstractCell*> v;
 	for(int i=0; i<8; i++){
 		ConwayCell* temp = new ConwayCell(false);
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_ConwayCell, CC_determineNextState3) {
 	ConwayCell x('*');
 	vector<AbstractCell*> v;
 	ConwayCell* a = new ConwayCell('*');
 	ConwayCell* b = new ConwayCell('.');
 	ConwayCell* c = new ConwayCell('*');
 	ConwayCell* d = new ConwayCell('*');
 	ConwayCell* e = new ConwayCell('.');
 	ConwayCell* f = new ConwayCell('.');
 	ConwayCell* g = new ConwayCell('.');
 	ConwayCell* h = new ConwayCell('.'); 
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
 	ASSERT_TRUE(x.currentState);
 	ASSERT_TRUE(x.nextState);
 }

 TEST(Test_ConwayCell, CC_updateCell1) {
 	ConwayCell x('*');
 	x.updateCell(); 
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_ConwayCell, CC_updateCell2) {
 	ConwayCell x('.');
 	x.nextState = true;
 	x.updateCell();
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_ConwayCell, CC_updateCell3) {
 	ConwayCell x('*');
 	vector<AbstractCell*> v;
 	for(int i=0; i<8; i++){
 		ConwayCell* temp = new ConwayCell('.');
 		v.push_back(temp);
 	}
 	x.determineNextState(v);
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_FredkinCell, FC_constructor1){
 	FredkinCell x('-');
 	ASSERT_FALSE(x.currentState);
 	ASSERT_FALSE(x.nextState);
 	ASSERT_EQ(x.image, '-');
 }

 TEST(Test_FredkinCell, FC_constructor2){
 	FredkinCell x('0');
 	ASSERT_TRUE(x.currentState);
 	ASSERT_FALSE(x.nextState);
 	ASSERT_EQ(x.image, '0');
 }

 TEST(Test_FredkinCell, FC_constructor3){
 	FredkinCell x('-');
 	x.currentState=false;
 	ASSERT_FALSE(x.isAlive());
 	ASSERT_EQ(x.image, '-');
 }

 TEST(Test_FredkinCell, FC_isAlive1){
	FredkinCell x('0');
	ASSERT_TRUE(x.isAlive());
	ASSERT_EQ(x.image, '0');
 }

 TEST(Test_FredkinCell, FC_isAlive2){
	FredkinCell x('-');
	ASSERT_FALSE(x.currentState);
	ASSERT_EQ(x.image, '-');
	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_FredkinCell, FC_isAlive3){
	FredkinCell x('0');
	ASSERT_TRUE(x.currentState);
	ASSERT_FALSE(x.nextState);
	ASSERT_EQ(x.image, '0');
 }

 TEST(Test_FredkinCell, FC_determineNextState1){
 	FredkinCell x('0');
 	vector<AbstractCell*> v;
 	for(int i=0; i<8; i++){
 		FredkinCell* temp = new FredkinCell('0');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_FredkinCell, FC_determineNextState2){
 	FredkinCell x('0');
 	vector<AbstractCell*> v;
 	for(int i=0; i<8; i++){
 		FredkinCell* temp = new FredkinCell('-');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_FredkinCell, FC_determineNextState3){
 	FredkinCell x('-');
 	vector<AbstractCell*> v;
 	FredkinCell* a = new FredkinCell('0');
 	FredkinCell* b = new FredkinCell('-');
 	FredkinCell* c = new FredkinCell('0');
 	FredkinCell* d = new FredkinCell('0');
 	FredkinCell* e = new FredkinCell('-');
 	FredkinCell* f = new FredkinCell('-');
 	FredkinCell* g = new FredkinCell('-');
 	FredkinCell* h = new FredkinCell('-'); 
 	v.push_back(a);
 	v.push_back(b);
 	v.push_back(c);
 	v.push_back(d);
 	v.push_back(e);
 	v.push_back(f);
 	v.push_back(g);
 	v.push_back(h);
 	x.determineNextState(v);
 	ASSERT_FALSE(x.isAlive());
 	ASSERT_FALSE(x.currentState);
 	ASSERT_TRUE(x.nextState);
 }

 TEST(Test_FredkinCell, FC_updateCell1) {
 	FredkinCell x('0');
 	x.updateCell(); 
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_FredkinCell, FC_updateCell2) {
 	FredkinCell x('-');
 	x.nextState = true;
 	x.updateCell();
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_FredkinCell, FC_updateCell3) {
 	FredkinCell x('0');
 	vector<AbstractCell*> v;
 	for(int i=0; i<8; i++){
 		FredkinCell* temp = new FredkinCell('-');
 		v.push_back(temp);
 	}
 	x.determineNextState(v);
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 }



 TEST(Test_Life, Life_constructor1){
 	vector<ConwayCell> v;
	ConwayCell a('*');
	ConwayCell b('.');
	ConwayCell c('*');
	ConwayCell d('*');
	ConwayCell e('.');
	ConwayCell f('.');
	ConwayCell g('.');
	ConwayCell h('.'); 
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);
	v.push_back(e);
	v.push_back(f);
	v.push_back(g);
	v.push_back(h);
 	Life<ConwayCell> l(4, 4, v);
 	ASSERT_TRUE(l.board.size() == 16);
 	ASSERT_EQ(l.population, 3);
 }

 TEST(Test_Life, Life_constructor2){
 	vector<FredkinCell> f;
	FredkinCell i('0');
	FredkinCell j('-');
	FredkinCell k('0');
	FredkinCell l('0');
	FredkinCell m('-');
	FredkinCell n('-');
	FredkinCell o('0');
	FredkinCell p('-'); 
	f.push_back(i);
	f.push_back(j);
	f.push_back(k);
	f.push_back(l);
	f.push_back(m);
	f.push_back(n);
	f.push_back(o);
	f.push_back(p);
 	Life<FredkinCell> li(4, 8, f);
 	ASSERT_TRUE(li.board.size() == 32);
 	ASSERT_EQ(li.population, 4);
 }

 /*TEST(Test_Life, Life_constructor3){
 	vector<Cell> v;
 	ConwayCell a(true);
	ConwayCell b(false);
	ConwayCell c(true);
	ConwayCell d(true);
	FredkinCell i(true);
	FredkinCell j(false);
	FredkinCell k(true);
	FredkinCell l(true);
 	Life<Cell> l(5, 5, v);
 	ASSERT_TRUE(l.board.size() == 25);
 }*/

 TEST(Test_Life, runTurn1){
 	vector<ConwayCell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	l.runTurn();
 	ASSERT_EQ(l.population, 4);
 }

 TEST(Test_Life, runTurn2){
 	vector<FredkinCell> v;
 	for(int i=0; i<9; i++){
 		FredkinCell temp('0');
 		v.push_back(temp);
 	}
 	Life<FredkinCell> l(3, 3, v);
 	l.runTurn();
 	ASSERT_EQ(l.population, 4);
 }

 /*TEST(Test_Life, runTurn1){
 	vector<Cell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp(true);
 		v.push_back(temp);
 	}
 	Life<Cell> l(3, 3, v);
 	l.runTurn();
 	ASSERT_EQ(l.population, 4);
 }*/

 TEST(Test_Life, cellNeighbors1){
 	vector<ConwayCell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	l.runTurn(); 	
 	vector<AbstractCell*> neighbors = l.cellNeighbors(1, 1);
 	ASSERT_EQ(l.population, 4);
 	ASSERT_EQ(neighbors.size(), 9);
 	int liveNeighbors = 0; 	
 	for(int i=0; i<(int)neighbors.size(); i++){
 		if(neighbors[i]!=nullptr && neighbors[i]->isAlive()){
 			liveNeighbors++;
 		}
 	}
 	ASSERT_EQ(liveNeighbors, 4);

 }

 TEST(Test_Life, cellNeighbors2){
 	vector<FredkinCell> v;
	for(int i=0; i<16; i++){
 		FredkinCell temp('0');
 		v.push_back(temp);
 	}
 	Life<FredkinCell> l(4, 4, v);
 	l.runTurn();
 	vector<AbstractCell*> neighbors = l.cellNeighbors(1, 1);
 	ASSERT_EQ(l.population, 8);
 	ASSERT_EQ(neighbors.size(), 9);
 	int liveNeighbors = 0;
 	for(int i=0; i<(int)neighbors.size(); i++){
 		if(neighbors[i]!=nullptr && neighbors[i]->isAlive()){
 			liveNeighbors++;
 		}
 	}
 	ASSERT_EQ(liveNeighbors, 4);
 }

 /*TEST(Test_Life, cellNeighbors3){
 	vector<FredkinCell> v;
	for(int i=0; i<16; i++){
 		FredkinCell temp('0');
 		v.push_back(temp);
 	}
 	Life<FredkinCell> l(4, 4, v);
 	l.runTurn();
 	vector<FredkinCell> neighbors = l.cellNeighbors(1, 1);
 	ASSERT_EQ(l.population, 8);
 	ASSERT_EQ(neighbors.size(), 9);
 	int liveNeighbors = 0;
 	for(int i=0; i<(int)neighbors.size(); i++){
 		if(neighbors[i].isAlive()){
 			liveNeighbors++;
 		}
 	}
 	ASSERT_EQ(liveNeighbors, 4);
 }*/

 TEST(Test_Life, inBounds1){
 	vector<ConwayCell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	ASSERT_TRUE(l.inBounds(2, 2));
 	ASSERT_FALSE(l.inBounds(3, 3));
 }

 TEST(Test_Life, inBounds2){
 	vector<FredkinCell> v;
 	for(int i=0; i<9; i++){
 		FredkinCell temp('0');
 		v.push_back(temp);
 	}
 	Life<FredkinCell> l(3, 3, v);
 	ASSERT_TRUE(l.inBounds(0, 0));
 	ASSERT_FALSE(l.inBounds(0, 3));
 }

 /*TEST(Test_Life, inBounds2){
 	vector<Cell> v;
 	for(int i=0; i<9; i++){
 		Cell temp('0');
 		v.push_back(temp);
 	}
 	Life<Cell> l(3, 3, v);
 	ASSERT_TRUE(l.inBounds(0, 0));
 	ASSERT_FALSE(l.inBounds(0, 3));
 }*/