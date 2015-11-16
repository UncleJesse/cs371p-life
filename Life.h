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
	protected: 
		virtual void determineNextState(vector<ConwayCell> neighbors)=0;
		virtual void updateCell()=0;
		virtual bool isAlive()=0;
	};

class ConwayCell: AbstractCell{
	private:
		bool currentState;
		bool nextState;
		char image;
	public:		
		ConwayCell(bool state=false);
		void determineNextState(vector<ConwayCell> neighbors);
		void updateCell();
		bool isAlive();
		friend std::ostream& operator<<(std::ostream& os, const ConwayCell* cc);
		ConwayCell& operator= (const ConwayCell &rhs);
};

class FredkinCell: AbstractCell{
	private:
		bool currentState;
		bool nextState;
		char image;
		int age;
	public:		
		FredkinCell(bool state=false);
		void determineNextState(vector<FredkinCell*> neighbors);
		void updateCell();
		bool isAlive();
		friend std::ostream& operator<<(std::ostream& os, const FredkinCell* cc);
		FredkinCell& operator= (const FredkinCell &rhs);
};

class Life{
	private:
		const int rows;
		const int cols;
		vector<ConwayCell> board;
		
	public:
	    int population;
		Life(const int& r,const int& c,const vector<ConwayCell> cells);
		void runTurn();
		bool inBounds(int r, int c);
		vector<ConwayCell> cellNeighbors(int x, int y);
		ConwayCell* at(const int& x, const int& y);
		vector<ConwayCell>::iterator begin();
		vector<ConwayCell>::iterator end();
		friend std::ostream& operator<<(std::ostream& os, Life& l);

};
void runInput(istream& r, ostream& os);


#endif 