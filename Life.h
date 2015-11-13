#ifndef Life_h
#define Life_h

#include <cassert>   // assert
#include <vector> // vector
#include <string>   // getline, string
#include <iterator> // iterator
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream, ostringstream
#include <stdlib.h>     /* srand, rand */


using namespace std;

class Life;
class AbstractCell;
class ConwayCell;
class FredkinCell;
class Cell;

class AbstractCell{
	private:
		char image;
		bool currentState;
		bool nextState;
	protected: 
		virtual void determineNextState(vector<ConwayCell> neighbors)=0;
		virtual bool isAlive()=0;


};

class ConwayCell: AbstractCell{
	private:
		char image;
		bool currentState;
		bool nextState;
	public:
		ConwayCell();
		void determineNextState(vector<ConwayCell> neighbors);
		bool isAlive();
};

class Life{
	private:
		vector<ConwayCell> board;
		const int rows;
		const int cols;
		int generation;
	public:
		Life(const int& r,const int& c);
		void runTurn(vector<ConwayCell> board);
		bool inBounds(int r, int c);
		ConwayCell at(const int& x, const int& y);
		vector<ConwayCell> cellNeighbors(int x, int y);
		vector<ConwayCell>::iterator begin();
		vector<ConwayCell>::iterator end();
		friend std::ostream& operator<<(std::ostream& os, Life& l);

};

void processInput(istream& s, ostream& os);

#endif 
