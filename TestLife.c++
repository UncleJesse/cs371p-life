#define private public

#include <stdexcept>
#include "gtest/gtest.h"

#include "Life.h"


using namespace std;

 TEST(Test_ConwayCell, CC_constructor1) {
 	ConwayCell x('.');
 	ASSERT_FALSE(x.currentState);
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_ConwayCell, CC_constructor2) {
 	ConwayCell x('*');
 	ASSERT_FALSE(x.nextState);
 }

 TEST(Test_ConwayCell, CC_constructor3) {
 	ConwayCell x('*');
 	ASSERT_TRUE(x.currentState);
 	ASSERT_TRUE(x.image == '*');
 }

 TEST(Test_ConwayCell, CC_clone1){
 	ConwayCell x('.');
 	ConwayCell* y=x.clone();
 	ASSERT_FALSE(y->isAlive());
 	delete y;
 }

 TEST(Test_ConwayCell, CC_clone2){
 	ConwayCell x('*');
 	ConwayCell* y=x.clone();
 	ASSERT_TRUE(y->isAlive());
 	delete y;
 }

 TEST(Test_ConwayCell, CC_clone3){
 	ConwayCell x('.');
 	ConwayCell* y=x.clone();
 	ASSERT_NE(y, &x);
 	delete y;
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
 	for(int i=0; i<9; i++){
 		ConwayCell* temp = new ConwayCell('*');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
 }

 TEST(Test_ConwayCell, CC_determineNextState2) {
 	ConwayCell x('*');
 	vector<AbstractCell*> v;
 	for(int i=0; i<9; i++){
 		ConwayCell* temp = new ConwayCell('.');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
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
 	ConwayCell* j = new ConwayCell('.'); 
 	v.push_back(a);
 	v.push_back(b);
 	v.push_back(c);
 	v.push_back(d);
 	v.push_back(e);
 	v.push_back(f);
 	v.push_back(g);
 	v.push_back(h);
 	v.push_back(j);
 	x.determineNextState(v);
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_TRUE(x.currentState);
 	ASSERT_TRUE(x.nextState);
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
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
 	for(int i=0; i<9; i++){
 		ConwayCell* temp = new ConwayCell('.');
 		v.push_back(temp);
 	}
 	x.determineNextState(v);
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
 }

 TEST(Test_ConwayCell, CC_assignment1){
 	ConwayCell x('*');
 	ConwayCell y('.');
 	y = x;
 	ASSERT_TRUE(y.isAlive());
 }

 TEST(Test_ConwayCell, CC_assignment2){
 	ConwayCell x('.');
 	ConwayCell y('*');
 	y = x;
 	ASSERT_FALSE(y.isAlive());
 }

 TEST(Test_ConwayCell, CC_assignment3){
 	ConwayCell x('*');
 	ConwayCell y('.');
 	y = x;
 	ASSERT_TRUE(y.image=='*');
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

 TEST(Test_FredkinCell, FC_clone1){
 	FredkinCell x('-');
 	FredkinCell* y=x.clone();
 	ASSERT_FALSE(y->isAlive());
 	delete y;
 }

 TEST(Test_FredkinCell, FC_clone2){
 	FredkinCell x('0');
 	FredkinCell* y=x.clone();
 	ASSERT_TRUE(y->isAlive());
 	delete y;
 }

 TEST(Test_FredkinCell, FC_clone3){
 	FredkinCell x('-');
 	FredkinCell* y=x.clone();
 	ASSERT_NE(y, &x);
 	delete y;
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
 	for(int i=0; i<9; i++){
 		FredkinCell* temp = new FredkinCell('0');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
 }

 TEST(Test_FredkinCell, FC_determineNextState2){
 	FredkinCell x('0');
 	vector<AbstractCell*> v;
 	for(int i=0; i<9; i++){
 		FredkinCell* temp = new FredkinCell('-');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	ASSERT_FALSE(x.nextState);
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
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
 	FredkinCell* j = new FredkinCell('-');
 	v.push_back(a);
 	v.push_back(b);
 	v.push_back(c);
 	v.push_back(d);
 	v.push_back(e);
 	v.push_back(f);
 	v.push_back(g);
 	v.push_back(h);
 	v.push_back(j);
 	x.determineNextState(v);
 	ASSERT_FALSE(x.isAlive());
 	ASSERT_FALSE(x.currentState);
 	ASSERT_TRUE(x.nextState);
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
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
 	for(int i=0; i<9; i++){
 		FredkinCell* temp = new FredkinCell('-');
 		v.push_back(temp);
 	}
 	x.determineNextState(v);
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
 }

 TEST(Test_FredkinCell, FC_assignment1){
 	FredkinCell x('0');
 	FredkinCell y('-');
 	y = x;
 	ASSERT_TRUE(y.isAlive());
 }

 TEST(Test_FredkinCell, FC_assignment2){
 	FredkinCell x('-');
 	FredkinCell y('0');
 	y = x;
 	ASSERT_FALSE(y.isAlive());
 }

 TEST(Test_FredkinCell, FC_assignment3){
 	FredkinCell x('0');
 	FredkinCell y('-');
 	y = x;
 	ASSERT_TRUE(y.image=='0');
 }

 TEST(Test_Cell, Cell_constructor1){
 	Cell x('.');
 	ASSERT_FALSE(x.isFCell);
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_Cell, Cell_constructor2) {
 	Cell x('*');
 	ASSERT_FALSE(x.isFCell);
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_Cell, Cell_constructor3) {
 	Cell x('0');
 	ASSERT_TRUE(x.isFCell);
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_Cell, Cell_clone1){
 	Cell x('0');
 	Cell* y=x.clone();
 	ASSERT_TRUE(y->isAlive());
 	delete y;
 }

 TEST(Test_Cell, Cell_clone2){
 	Cell x('*');
 	Cell* y=x.clone();
 	ASSERT_TRUE(y->isAlive());
 	delete y;
 }

 TEST(Test_Cell, Cell_clone3){
 	Cell x('.');
 	Cell* y=x.clone();
 	ASSERT_FALSE(y->isAlive());
 	delete y;
 }

 TEST(Test_Cell, Cell_updateCell1){
 	Cell x('*');
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_Cell, Cell_updateCell2){
 	Cell x('.');
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_Cell, Cell_updateCell3){
 	Cell x('0');
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_Cell, Cell_determineNextState1){
 	Cell x('*');
 	vector<AbstractCell*> v;
 	for(int i=0; i<9; i++){
 		Cell* temp = new Cell('*');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
 }

 TEST(Test_Cell, Cell_determineNextState2){
 	Cell x('0');
 	vector<AbstractCell*> v;
 	for(int i=0; i<9; i++){
 		Cell* temp = new Cell('0');
 		v.push_back(temp);
 	}
 	x.determineNextState(v); 
 	ASSERT_TRUE(x.isAlive());
 	x.updateCell();
 	ASSERT_FALSE(x.isAlive());
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
 }

 TEST(Test_Cell, Cell_determineNextState3){
 	Cell x('*');
 	vector<AbstractCell*> v;
 	Cell* a = new Cell('*');
 	Cell* b = new Cell('.');
 	Cell* c = new Cell('*');
 	Cell* d = new Cell('0');
 	Cell* e = new Cell('-');
 	Cell* f = new Cell('.');
 	Cell* g = new Cell('-');
 	Cell* h = new Cell('.');
 	Cell* j = new Cell('.'); 
 	v.push_back(a);
 	v.push_back(b);
 	v.push_back(c);
 	v.push_back(d);
 	v.push_back(e);
 	v.push_back(f);
 	v.push_back(g);
 	v.push_back(h);
 	v.push_back(j);
 	x.determineNextState(v);
 	ASSERT_TRUE(x.isAlive());
 	x.updateCell();
 	ASSERT_TRUE(x.isAlive());
 	for(int i=0; i<9; i++){
 		delete v[i];
 	}
 }

 TEST(Test_Cell, Cell_isAlive1){
 	Cell x('.');
 	ASSERT_FALSE(x.isAlive());
 }

 TEST(Test_Cell, Cell_isAlive2){
 	Cell x('0');
 	ASSERT_TRUE(x.isAlive());
 }

 TEST(Test_Cell, Cell_isAlive3){
 	Cell x('*');
 	ASSERT_TRUE(x.isAlive());
 }



 TEST(Test_Cell, Cell_toString1){
 	Cell x('*');
 	string s = "*";
 	ASSERT_EQ(x.toString(), s);
 }

 TEST(Test_Cell, Cell_toString2){
 	Cell x('0');
 	string s = "0";
 	ASSERT_EQ(x.toString(), s);
 }

 TEST(Test_Cell, Cell_toString3){
 	Cell x('.');
 	string s = ".";
 	ASSERT_EQ(x.toString(), s);
 }

 TEST(Test_Cell, Cell_assignment1){
 	Cell x('0');
 	Cell y('.');
 	y = x;
 	ASSERT_TRUE(y.isAlive());
 }

 TEST(Test_Cell, Cell_assignment2){
 	Cell x('-');
 	Cell y('*');
 	y = x;
 	ASSERT_FALSE(y.isAlive());
 }

 TEST(Test_Cell, Cell_assignment3){
 	Cell x('0');
 	Cell y('*');
 	y = x;
 	ASSERT_TRUE(y.isAlive());
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
 	ASSERT_TRUE(l.board.size() == 8);
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
 	ASSERT_TRUE(li.board.size() == 8);
 	ASSERT_EQ(li.population, 4);
 }

 TEST(Test_Life, Life_constructor3){
 	vector<Cell> v;
 	Cell a('*');
	Cell b('.');
	Cell c('*');
	Cell d('*');
	Cell e('0');
	Cell f('-');
	Cell g('0');
	Cell h('0');
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);
	v.push_back(e);
	v.push_back(f);
	v.push_back(g);
	v.push_back(h);
 	Life<Cell> l(5, 5, v);
 	ASSERT_TRUE(l.board.size() == 8);
 	ASSERT_EQ(l.population, 6);
 }

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

 TEST(Test_Life, runTurn3){
 	vector<ConwayCell> v;
	for(int i=0; i<5; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	for (int i=0; i<4; i++){
 		ConwayCell temp('.');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	l.runTurn();
 	ASSERT_EQ(l.population, 4);
 }

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

 TEST(Test_Life, cellNeighbors3){
 	vector<ConwayCell> v;
	for(int i=0; i<4; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	for(int i=0; i<4; i++){
 		ConwayCell temp('.');
 		v.push_back(temp);
 	}
 	for(int i=0; i<4; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	for(int i=0; i<4; i++){
 		ConwayCell temp('.');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(4, 4, v);
 	l.runTurn();
 	vector<AbstractCell*> neighbors = l.cellNeighbors(1, 1);
 	ASSERT_EQ(l.population, 6);
 	ASSERT_EQ(neighbors.size(), 9);
 	int liveNeighbors = 0;
 	for(int i=0; i<(int)neighbors.size(); i++){
 		if(neighbors[i]!=nullptr && neighbors[i]->isAlive()){
 			liveNeighbors++;
 		}
 	}
 	ASSERT_EQ(liveNeighbors, 4);
 }

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

 TEST(Test_Life, inBounds3){
 	vector<Cell> v;
 	for(int i=0; i<9; i++){
 		Cell temp('0');
 		v.push_back(temp);
 	}
 	Life<Cell> l(3, 3, v);
 	ASSERT_TRUE(l.inBounds(0, 0));
 	ASSERT_FALSE(l.inBounds(0, 3));
 }

 TEST(Test_Life, at1){
 	vector<ConwayCell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	ASSERT_TRUE(l.at(1, 0)->isAlive());
 }

 TEST(Test_Life, at2){
 	vector<ConwayCell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp('.');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	ASSERT_FALSE(l.at(2, 2)->isAlive());
 }

 TEST(Test_Life, at3){
 	vector<Cell> v;
	for(int i=0; i<9; i++){
 		Cell temp('0');
 		v.push_back(temp);
 	}
 	Life<Cell> l(3, 3, v);
 	ASSERT_TRUE(l.at(0, 0)->isAlive());
 }

 TEST(Test_Life, begin1){
 	vector<ConwayCell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	vector<ConwayCell>::iterator it = l.begin();
 	ASSERT_TRUE(it->isAlive());
 }

 TEST(Test_Life, begin2){
 	vector<FredkinCell> v;
	for(int i=0; i<9; i++){
 		FredkinCell temp('0');
 		v.push_back(temp);
 	}
 	Life<FredkinCell> l(3, 3, v);
 	vector<FredkinCell>::iterator it = l.begin();
 	it++;
 	ASSERT_TRUE(it->isAlive());
 }

 TEST(Test_Life, begin3){
 	vector<Cell> v;
	for(int i=0; i<9; i++){
 		Cell temp('.');
 		v.push_back(temp);
 	}
 	Life<Cell> l(3, 3, v);
 	vector<Cell>::iterator it = l.begin();
 	ASSERT_FALSE(it->isAlive());
 }

 TEST(Test_Life, end1){
 	vector<ConwayCell> v;
	for(int i=0; i<9; i++){
 		ConwayCell temp('*');
 		v.push_back(temp);
 	}
 	Life<ConwayCell> l(3, 3, v);
 	vector<ConwayCell>::iterator it = l.end();
 	it--;
 	ASSERT_TRUE(it->isAlive());
 }

 TEST(Test_Life, end2){
 	vector<FredkinCell> v;
	for(int i=0; i<9; i++){
 		FredkinCell temp('0');
 		v.push_back(temp);
 	}
 	Life<FredkinCell> l(3, 3, v);
 	vector<FredkinCell>::iterator it = l.end();
 	it--;
 	ASSERT_TRUE(it->isAlive());
 }

 TEST(Test_Life, end3){
 	vector<Cell> v;
	for(int i=0; i<9; i++){
 		Cell temp('.');
 		v.push_back(temp);
 	}
 	Life<Cell> l(3, 3, v);
 	vector<Cell>::iterator it = l.end();
 	it--;
 	it--;
 	ASSERT_FALSE(it->isAlive());
 }