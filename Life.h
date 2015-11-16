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

class AbstractCell;
class ConwayCell;
class FredkinCell;
class Cell;

class AbstractCell{
	protected:
		virtual void updateCell()=0;
		virtual bool isAlive()=0;
		//virtual void determineNextState(vector<AbstractCell> neighbors);
	};

class ConwayCell: public AbstractCell{
	private:
		bool currentState;
		bool nextState;
		char image;
	public:
		ConwayCell(char state='.');
		void determineNextState(vector<ConwayCell> neighbors);
		void updateCell();
		bool isAlive();
		friend std::ostream& operator<<(std::ostream& os, const ConwayCell* cc);
		ConwayCell& operator= (const ConwayCell &rhs);
};

class FredkinCell: public AbstractCell{
	private:
		bool currentState;
		bool nextState;
		char image;
		int age;
	public:
		FredkinCell(char state='-');
		void determineNextState(vector<FredkinCell> neighbors);
		void updateCell();
		bool isAlive();
		friend std::ostream& operator<<(std::ostream& os, const FredkinCell* cc);
		FredkinCell& operator= (const FredkinCell &rhs);
};

//If Life is instantiated with Cell, then when a FredkinCell's age is to become 2, and only then, it becomes a live ConwayCell instead.
class Cell{
	private:
		bool isFCell;
		AbstractCell* _c;
	public:
		Cell(char image);
		Cell(AbstractCell* &rhs);
		~Cell();
		void updateCell();
		AbstractCell* operator->();

};

template<class T>
class Life{
	private:
		const int rows;
		const int cols;
		vector<T> board;
		int population;
		int currentGen;

	public:
		Life(const int& r,const int& c,const vector<T> cells): rows(r), cols(c),board(r * c){
			population=0;
			currentGen=0;
			for(int i=0; i<(int)cells.size(); i++){
				board[i]=cells[i];
				if(board.at(i).isAlive())
					population++;
			}
		}
		void runTurn(){
			population=0;
			currentGen++;
			for(int r=0; r<rows; r++){
				for(int c=0; c<cols; c++){
					vector<T> temp=cellNeighbors(r,c);
					at(r,c)->determineNextState(temp);
				}
			}
			for(int r=0; r<rows; r++){
				for(int c=0; c<cols; c++){
						at(r,c)->updateCell();
						if(at(r,c)->isAlive())
							population++;
					}
			}
		}
		bool inBounds(int r,int c){
			return (r<rows) && (r>=0) && (c<cols) && (c>=0);
		}
		vector<T> cellNeighbors(int x, int y){
			vector<T> neighbors(9);
			int vectorIndex=0;
			for(int r=(x-1); r<=x+1; r++){
				for(int c=(y-1); c<=y+1; c++){
					{
						if(!(r==x && c==y) && Life::inBounds(r,c))
							neighbors[vectorIndex]=*Life::at(r,c);
						vectorIndex++;
					}
				}
			}
			return neighbors;
		}
		T* at(const int& x, const int& y){
			return &board[cols * x + y];
		}
		typename vector<T>::iterator begin(){
			return board.begin();
		}
		typename vector<T>::iterator end(){
			return board.end();
		}
		friend ostream& operator << (ostream& os, Life<T>& l){
			cout<<"Generation = "<<l.currentGen<<", Population = "<<l.population <<"."<<endl;
			for(int r = 0; r < l.rows; ++r){
				for(int c = 0; c < l.cols; ++c){
					os << l.at(r , c);
				}
				os << endl;
		
			}
			return os;
		}
};

void runInput(istream& r, ostream& os);

#endif