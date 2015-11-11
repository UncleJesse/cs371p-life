#include "Life.h"



using namespace std;

class Life;
class AbstractCell;
class ConwayCell;
class FredkinCell;
class Cell;

abstract class AbstractCell{
	protected:

		virtual int countNeighbors(){}
};

class ConwayCell: public AbstractCell{

};

class FredkinCell: public AbstractCell{
	private:
		int age;
};

class Cell{
	private:
		AbstractCell* _ac;
};

template <typename T>;
class Life<T>{
	public:

		void print(int frequencyOut, ostream& os){

		}

		void processInput(istream& is, ostream& os){
			string cellType;
			getLine(s, cellType);

			string numRows;
			getLine(s, numRows);			
			int rows = atoi(numRows.c_str());

			string numCols;
			getLine(s, numCols);
			int cols = atoi(numCols.c_str());

			string numGens;
			getLine(s, numGens);
			int generations = atoi(numGens.c_str());

			string freqOut;
			getLine(s, freqOut);
			int frequencyOut = atoi(freqOut.c_str());
		}
};