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
	protected:
		virtual int countNeighbors();


};

class ConwayCell: public AbstractCell{
	public:
		int countNeighbors();
};

class FredkinCell: public AbstractCell{
	private:
		int age;

	public:
		int countNeighbors();
};

class Cell{
	private:
		AbstractCell* _ac;
};

template <typename T>;
class Life<T>{
	public:
		void print(int frequencyOut);

		void processInput(istream& is, ostream& os);
};

#endif 
