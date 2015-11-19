/**
 * @file Life.h
 * @brief AbstractCell, ConwayCell, FredkinCell, Cell, and Life
 *
 * @author Juan Villegas
 * @author Jesse Mendoza
 */
#ifndef Life_h
#define Life_h

#include <cassert>   // assert
#include <vector>    // vector
#include <string>    // getline, string
#include <iterator>  // iterator
#include <iostream>  // endl, istream, ostream
#include <sstream>   // istringstream, ostringstream
#include <stdlib.h>  // srand, rand 


using namespace std;

class AbstractCell;
class ConwayCell;
class FredkinCell;
class Cell;

/**
 * @class AbstractCell
 * @brief AbstractCell is an "abstract" class that contains virtual methods that are 
 * overridden byits children, ConwayCell, FredkinCell, and Cell.
 */
class AbstractCell{
	public:
		virtual void updateCell()=0;
		virtual bool isAlive()=0;
		/**
	 	 * @brief Destructor is made virtual so that the child destructor is called when destroying object 
	 	 */
		virtual ~AbstractCell(){};
		virtual void determineNextState(vector<AbstractCell*>)=0;
		virtual AbstractCell* clone() const=0;
	};
/**
 * @class ConwayCell
 * @brief ConwayCell is a child of AbstractCell and implements all of its methods, along with overriding 
 *        the << and = operators. It has a one argument constructor, which is the char that is read in  
 *        from RunLife.in in the runInput method.
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
		ConwayCell(char state='.');
		virtual ConwayCell* clone() const;
		void determineNextState(vector<AbstractCell*> neighbors);
		void updateCell();
		bool isAlive();
		friend std::ostream& operator<<(std::ostream& os, const ConwayCell* cc);
		ConwayCell& operator = (const ConwayCell &rhs);
};
/**
 * @class FredkinCell 
 * @brief is a child of AbstractCell and implements all of its methods, along with overriding 
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
		FredkinCell(char state='-');
		virtual FredkinCell* clone() const;
		void determineNextState(vector<AbstractCell*> neighbors);
		void updateCell();
		bool isAlive();
		friend std::ostream& operator<<(std::ostream& os, const FredkinCell* cc);
		FredkinCell& operator = (const FredkinCell &rhs);
};
/**
 * @class Cell
 * @brief Cell is a child of AbstractCell and implements all of its methods, along with overriding 
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
		Cell(char image='.');
		Cell(Cell const &c);
		~Cell();
		virtual Cell* clone() const;
		void updateCell();
		void determineNextState(vector<AbstractCell*> neighbors);
		bool isAlive();
		string toString();
		friend std::ostream& operator<<(std::ostream& os, const Cell* c);
		Cell& operator= (Cell const &c);
};
/**
 * @clas Life 
 * @brief a template class that creates a board of T cells, which can be either ConwayCells, 
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
 		 * @brief Life has a 3 argument constructor that takes two ints that indicate the number of rows
 		 * and columns for the board, and a vector of T cells to create the initial board. The currentGen
 		 * starts at 0, and the population is determined by calling the isAlive() method of each T cell.
 		 * @param rows
 		 * @param columns
 		 * @param vector of Cellsof type T
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
 		 * 
 		 * @brief Life's runTurn method is called in the runInput method to advance to the next turn, invoking
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
 		 * @brief Method that insures that the given coordinates are within the board's boundaries.
 		 * @retval return whether x and y are in bounds
 		 */
		bool inBounds(int r,int c){
			return (r<rows) && (r>=0) && (c<cols) && (c>=0);
		}

		/**
 		 * @brief Method that collects the neighbors of each T cell in a vector so that it can be passed
 		 * to each T cell to be used to determine its next state(live or dead).
 		 * @param x coordinate
 		 * @param y coordinate
 		 * @retval vector of AbstaractCell* neighbors
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
 		 * @brief Method that returns a pointer to the T cell at the given coordinates.
 		 * @param x coordinate
 		 * @param y coordinate 
 		 * @retval T* to item on board
 		 */
		T* at(const int& x, const int& y){
			return &board[cols * x + y];
		}
		/**
 		 * @brief Method that returns an iterator that points to the first T cell on the board(in the vector).
 		 */
		typename vector<T>::iterator begin(){
			return board.begin();
		}
		/**
 		 * @brief Method that returns an iterator pointing to the position after the last T cell on the board.
 		 */
		typename vector<T>::iterator end(){
			return board.end();
		}

		/*
 		 * @brief Method that overrides the << operator to print out the board in the runInput method. The frequency
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

void runInput(istream& r, ostream& os);

#endif