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

abstract class AbstractCell{
	private:
		bool isAlive;
	protected:
		virtual void determineState(Life& life);


};

class ConwayCell: public AbstractCell{
	private:
		bool isAlive;
	public:
		void determineState(Life& life);
};

class FredkinCell: public AbstractCell{
	private:
		bool isAlive;
		int age;

	public:
		void determineState(Life& life);
};

class Cell{
	private:
		AbstractCell* _ac;
};

template <typename T>;
class Life<T>{
	private:
		vector<Cell> board;
		int maxX;
		int maxY;
	public:
		void print(int frequencyOut);

		void processInput(istream& is, ostream& os);
};

#endif 
