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

/**
 * AbstractCell is an "abstract" class that contains virtual methods that are overridden by
 * its children, ConwayCell, FredkinCell, and Cell.
 */
class AbstractCell{
	public:
		virtual void updateCell()=0;
		virtual bool isAlive()=0;
		/**
	 	 * Destructor is made virtual so that the child destructor is called when destroying object 
	 	 */
		virtual ~AbstractCell(){};
		virtual void determineNextState(vector<AbstractCell*>)=0;
		virtual AbstractCell* clone() const=0;
	};
/**
 * ConwayCell is a child of AbstractCell and implements all of its methods, along with overriding 
 * the << and = operators. It has a one argument constructor, which is the char that is read in  
 * from RunLife.in in the runInput method.
 */
class ConwayCell: public AbstractCell{
	/**
	 * the Cell class is a friend class so that it can access private data members 
	 */
	friend class Cell;
	/**
 	 * The private data members of ConwayCell are two booleans that represent the current state (live
 	 * or dead) and the next state in the evolution of this ConwayCell respectively. The char image is
 	 * the character that will be printed out each turn.
 	 */
	private:
		bool currentState;
		bool nextState;
		char image;
	public:
		/**
	 	 * One argument constructor for ConwayCell, takes in a char that determines its initial
	 	 * liveness, nextState is false by default and is changed in determineNextState if certain
	 	 * conditions are met. 
	 	 */
		ConwayCell(char state='.');
		/**
	 	 * Method used to make copy of ConwayCell
	 	 */
		virtual ConwayCell* clone() const;
		/**
	 	 * Method that determines next state of this ConwayCell depending on the number of live neighbors
	 	 * it has. The Life class collects a vector of the ConwayCell's neighbors and passes it so that
	 	 * the ConwayCell can count them.
	 	 */
		void determineNextState(vector<AbstractCell*> neighbors);
		/**
	 	 * Once the next state is determined, it is saved in nextState, which is then used in this method
	 	 * to update the ConwayCell for the next turn.
	 	 */
		void updateCell();
		/**
	 	 * Method that returns the currentState of this ConwayCell, used by Life to count the population
	 	 * of the board, and in the method determineNextState to determine the next state of the ConwayCell.
	 	 */
		bool isAlive();
		/**
	 	 * Method that overrides the << operator to print out the image of this ConwayCell.
	 	 */
		friend std::ostream& operator<<(std::ostream& os, const ConwayCell* cc);
		/**
	 	 * Method that overrides the = operator to create a copy of this ConwayCell.
	 	 */
		ConwayCell& operator = (const ConwayCell &rhs);
};
/**
 * FredkinCell is a child of AbstractCell and implements all of its methods, along with overriding 
 * the << and = operators. It has a one argument constructor, which is the char that is read in  
 * from RunLife.in in the runInput method.
 */
class FredkinCell: public AbstractCell{
	/**
	 * the Cell class is a friend class so that it can access private data members 
	 */
	friend class Cell;
	/**
 	 * The private data members of FredkinCell are two booleans that represent the current state (live
 	 * or dead) and the next state in the evolution of this FredkinCell respectively. The char image is
 	 * the character that will be printed out each turn. FredkinCells also age every turn they are alive,
 	 * which is tracked by the int age. FredkinCell also requires a prevState boolean that indicates whether
 	 * it was alive or dead in the previous turn, that way the age is only incremented when it is alive
 	 * in consecutive turns.
 	 */
	private:
		bool currentState;
		bool nextState;
		char image;
		int age;
	public:
		/**
	 	 * One argument constructor for FredkinCell, takes in a char that determines its initial
	 	 * liveness, nextState is false by default and is changed in determineNextState if certain
	 	 * conditions are met. All FredkinCells begin life at age 0.
	 	 */
		FredkinCell(char state='-');
		/**
	 	 * Method used to make copy of FredkinCell
	 	 */
		virtual FredkinCell* clone() const;
		/**
	 	 * Method that determines next state of this FredkinCell depending on the number of live neighbors
	 	 * it has. The Life class collects a vector of the FredkinCell's neighbors and passes it so that
	 	 * the FredkinCell can count them.
	 	 */
		void determineNextState(vector<AbstractCell*> neighbors);
		/**
	 	 * Once the next state is determined, it is saved in nextState, which is then used in this method
	 	 * to update the FredkinCell for the next turn. 
	 	 */
		void updateCell();
		/**
	 	 * Method that returns the currentState of this FredkinCell, used by Life to count the population
	 	 * of the board, and in the method determineNextState to determine the next state of the FredkinCell.
	 	 */
		bool isAlive();
		/**
	 	 * Method that overrides the << operator to print out the image of this FredkinCell.
	 	 */
		friend std::ostream& operator<<(std::ostream& os, const FredkinCell* cc);
		/**
	 	 * Method that overrides the = operator to create a copy of this FredkinCell.
	 	 */
		FredkinCell& operator = (const FredkinCell &rhs);
};
/**
 * Cell is a child of AbstractCell and implements all of its methods, along with overriding 
 * the << and = operators. It has two one argument constructors, one of which takes a char that 
 * is read in from RunLife.in in the runInput method, and another that creates a new Cell object
 * using a reference to an existing one. Cell acts as a handler for ConwayCell and FredkinCell so
 * that Life can create heterogenous boards.
 */
class Cell: public AbstractCell{
	/**
 	 * Cell's private data members are a boolean indicating whether the Cell is representing a
 	 * FredkinCell or ConwayCell, and an AbstractCell* that points to the object being represented
 	 */
	private:
		bool isFCell;
		AbstractCell* _c;
	public:
		/**
	 	 * One argument constructor for Cell, takes in a char that determines its initial
	 	 * liveness, nextState is false by default and is changed in determineNextState if certain
	 	 * conditions are met, depending on the type of AbstractCell being represented. Cell can 
	 	 * represent either a FredkinCell or ConwayCell.
	 	 */
		Cell(char image='.');
		/**
 	 	 * Another one argument constructor for Cell that takes in a reference to another Cell and
 	 	 * creates a copy of it
 	 	 */
		Cell(Cell const &c);
		/**
 	 	 * Destructor for Cell that destroys the underlying AbstractCell
 	 	 */
		~Cell();
		/**
	 	 * Method used to make copy of Cell
	 	 */
		virtual Cell* clone() const;
		/**
	 	 * Once the next state is determined, it is saved in nextState, which is then used in this method
	 	 * to update the Cell for the next turn. FredkinCells are mutated to ConwayCells at age 2.
	 	 */
		void updateCell();
		/**
	 	 * Method that determines next state of this Cell depending on the number of live neighbors
	 	 * it has. The Life class collects a vector of the Cell's neighbors and passes it so that
	 	 * the Cell can count them.
	 	 */
		void determineNextState(vector<AbstractCell*> neighbors);
		/**
	 	 * Method that returns the currentState of this Cell, used by Life to count the population
	 	 * of the board, and in the method determineNextState to determine the next state of the Cell.
	 	 */
		bool isAlive();
		/**
	 	 * Method that returns a string representation of the image of the cell being represented.
	 	 */
		string toString();
		/**
	 	 * Method that overrides the << operator to print out the image of this Cell.
	 	 */
		friend std::ostream& operator<<(std::ostream& os, const Cell* c);
		/**
	 	 * Method that overrides the = operator to create a copy of this Cell.
	 	 */
		Cell& operator= (Cell const &c);
};
/**
 * Class Life is a template class that creates a board of T cells, which can be either ConwayCells, 
 * FredkinCells, or both(Cells). T is read in from RunLife.in in the runInput method.Life passes 
 * information to the individual cells so that they can evolve each turn accordingly, and it prints 
 * the board along with the live population and generation.
 */
template<class T>
class Life{
	/**
 	 * The private data members of Life are the number of rows and columns of the board(ints rows and cols),
 	 * a vector of T cells that represents the board, and ints that keep track of the population and
 	 * current generation(currentGen). The rows, cols, and T are read in from RunLife.in by the runInput method.
 	 */
	private:
		const int rows;
		const int cols;
		vector<T> board;
		int population;
		int currentGen;
	public:
		/**
 		 * Life has a 3 argument constructor that takes two ints that indicate the number of rows
 		 * and columns for the board, and a vector of T cells to create the initial board. The currentGen
 		 * starts at 0, and the population is determined by calling the isAlive() method of each T cell.
 		 */
		Life(const int& r,const int& c,const vector<T> cells): rows(r), cols(c),board(0){
			population=0;
			currentGen=0;
			for(int i=0; i<(int)cells.size(); i++){
				board.push_back(cells[i]);
				if(board.at(i).isAlive())
					population++;
			}
		}
		/**
 		 * Life's runTurn method is called in the runInput method to advance to the next turn, invoking
 		 * each T cell's determineNextState and updateCell methods. The population and currentGen are
 		 * updated accordingly.
 		 */
		void runTurn(){
			population=0;
			currentGen++;
			for(int r=0; r<rows; r++){
				for(int c=0; c<cols; c++){
					vector<AbstractCell*> temp=cellNeighbors(r,c);	
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
		/**
 		 * Method that insures that the given coordinates are within the board's boundaries.
 		 */
		bool inBounds(int r,int c){
			return (r<rows) && (r>=0) && (c<cols) && (c>=0);
		}
		/**
 		 * Method that collects the neighbors of each T cell in a vector so that it can be passed
 		 * to each T cell to be used to determine its next state(live or dead).
 		 */
		vector<AbstractCell*> cellNeighbors(int x, int y){
			vector<AbstractCell*> neighbors(9);
			int vectorIndex=0;
			for(int r=(x-1); r<=x+1; r++){
				for(int c=(y-1); c<=y+1; c++){
					{
						if(!(r==x && c==y) && inBounds(r,c))
							neighbors[vectorIndex]=at(r,c);
						vectorIndex++;
					}
				}
			}
			return neighbors;
		}
		/**
 		 * Method that returns a pointer to the T cell at the given coordinates.
 		 */
		T* at(const int& x, const int& y){
			return &board[cols * x + y];
		}
		/**
 		 * Method that returns an iterator that points to the first T cell on the board(in the vector).
 		 */
		typename vector<T>::iterator begin(){
			return board.begin();
		}
		/**
 		 * Method that returns an iterator pointing to the position after the last T cell on the board.
 		 */
		typename vector<T>::iterator end(){
			return board.end();
		}
		/**
 		 * Method that overrides the << operator to print out the board in the runInput method. The frequency
 		 * with which it prints is determined at runtime by an int passed in from RunLife.in.
 		 */
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
/**
 * Method that reads the input from RunLife.in and prints the results to RunLife.out. It parses the information
 * that is passed in, creates a Life object, and passes the information to Life's methods to be processed.
 */
void runInput(istream& r, ostream& os);

#endif