/**
 * @file Life.c++
 * @brief Implementation of ConwayCell, FredkinCell, and Cell
 *
 * @author Juan Villegas
 * @author Jesse Mendoza
 */
#include "Life.h"
#include <string>



using namespace std;

/**
 * @brief One argument constructor for ConwayCell, 
 * nextState is false by default and is changed in determineNextState if certain
 * conditions are met. 
 * @param takes in a char that determines its initial liveness
 */
ConwayCell::ConwayCell(char state){
	image= state;
	currentState= state=='*'? true : false;
	nextState=false;
}

/**
 * @brief Method used to make copy of ConwayCell
 */
ConwayCell* ConwayCell::clone() const{
	return new ConwayCell(*this);
}

/**
 * @brief determines next state of this ConwayCell depending on the number of live neighbors
 * it has. The Life class collects a vector of the ConwayCell's neighbors and passes it so that
 * the ConwayCell can count them.
 * @param neighbors surrounding the cell
 */
void ConwayCell::determineNextState(vector<AbstractCell*> neighbors){
	int numberOfLiveNeighbors=0;
	for(int i=0; i< (int)neighbors.size(); i++){
		if(neighbors[i]!=nullptr && neighbors[i]->isAlive())
			numberOfLiveNeighbors++;
	}
	if(currentState==false && numberOfLiveNeighbors==3){
		nextState=true;
	}
	else if(currentState==true && (numberOfLiveNeighbors<2 ||numberOfLiveNeighbors>3) ){
		nextState=false;
	}
	else{
		nextState=currentState;
	}
}

/**
 * @brief Once the next state is determined, it is saved in nextState, which is then used in this method
 * to update the ConwayCell for the next turn.
 */
void ConwayCell::updateCell(){
	currentState=nextState;
	image= nextState?'*':'.';
}

/**
 * @brief Method that returns the currentState of this ConwayCell, used by Life to count the population
 * of the board, and in the method determineNextState to determine the next state of the ConwayCell.
 * @retval returns whether current cell is alive or not
 */
bool ConwayCell::isAlive(){
	return currentState;
}

/**
 * @brief Method that overrides the << operator to print out the image of this ConwayCell.
 */
std::ostream& operator << (std::ostream& os, const ConwayCell* cc){
  return os << cc->image;
}

/**
 * @brief Method that overrides the = operator to create a copy of this ConwayCell.
 */
ConwayCell& ConwayCell::operator = (const ConwayCell &rhs){
	image=rhs.image;
	currentState=rhs.currentState;
	nextState=rhs.nextState;
	return *this;
}

/**
 * @brief One argument constructor for FredkinCell, nextState is false by default and is changed in determineNextState if certain
 * conditions are met. All FredkinCells begin life at age 0.
 * @param takes in a char that determines its initial liveness, 
 */
FredkinCell::FredkinCell(char state){
	image= state;
	age=0;
	currentState= state=='0'? true : false;
	nextState=false;
}

/**
 * @brief Method used to make copy of FredkinCell
 */
FredkinCell* FredkinCell::clone() const{
	return new FredkinCell(*this);
}

/**
 * @brief Method that determines next state of this FredkinCell depending on the number of live neighbors
 * it has. The Life class collects a vector of the FredkinCell's neighbors and passes it so that
 * the FredkinCell can count them.
 * @param neighbors surrounding the cell
 */
void FredkinCell::determineNextState(vector<AbstractCell*> neighbors){
	//a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
	int numberOfLiveNeighbors=0;
	for(int i=1; i< (int)neighbors.size(); i+=2){
		if(neighbors[i]!=nullptr && neighbors[i]->isAlive())
			numberOfLiveNeighbors++;
	}
	if(currentState==false && (numberOfLiveNeighbors==1 || numberOfLiveNeighbors==3)){
		nextState=true;
	}
	else if(currentState==true && (numberOfLiveNeighbors==2 ||numberOfLiveNeighbors==4 || numberOfLiveNeighbors==0) ){
		nextState=false;
	}
	else if(currentState==true && (numberOfLiveNeighbors==1 || numberOfLiveNeighbors==3)){
		nextState=currentState;
		age++;
	}
	else{
		nextState=currentState;
	}
}


/**
 * @brief Once the next state is determined, it is saved in nextState, which is then used in this method
 * to update the FredkinCell for the next turn. 
 */
void FredkinCell::updateCell(){
	currentState=nextState;
	if(currentState){
		image=(age>=10)?'+':age+'0';
	}
	else
		image ='-';

}

/**
 * @brief Method that returns the currentState of this FredkinCell, used by Life to count the population
 * of the board, and in the method determineNextState to determine the next state of the FredkinCell.
 * @retval current state of cell
 */
bool FredkinCell::isAlive(){
	return currentState;
}


/**
 * @brief Method that overrides the << operator to print out the image of this FredkinCell.
 */
std::ostream& operator<<(std::ostream& os, const FredkinCell* fc){
	return os << fc->image;
}

/**
 * @brief Method that overrides the = operator to create a copy of this FredkinCell.
 */
FredkinCell& FredkinCell::operator= (const FredkinCell &rhs){
	image=rhs.image;
	currentState=rhs.currentState;
	nextState=rhs.nextState;
	age=rhs.age;
	return *this;
}

/**
 * @brief One argument constructor for Cell, nextState is false by default and is changed in determineNextState if certain
 * conditions are met, depending on the type of AbstractCell being represented. Cell can 
 * represent either a FredkinCell or ConwayCell. 
 * @retval takes in a char that determines its initial liveness
 */
Cell::Cell(char image){
	if(image=='.' || image=='*'){
		isFCell=false;
		_c=new ConwayCell(image);
	}
	else{
		isFCell=true;
		_c=new FredkinCell(image);
	}
}

/**
 * @brief Another one argument constructor for Cell that takes in a reference to another Cell and
 * creates a copy of it
 */
Cell::Cell(Cell const &c): _c(c._c->clone()){
	isFCell=true;
}

/**
 * @brief Destructor for Cell that destroys the underlying AbstractCell
 */
Cell::~Cell(){
	delete _c;
}

/**
 * @brief Method used to make copy of Cell
 */
Cell* Cell::clone() const{
	return new Cell(*this);
}

/**
 * @brief Once the next state is determined, it is saved in nextState, which is then used in this method
 * to update the Cell for the next turn. FredkinCells are mutated to ConwayCells at age 2.
 */
void Cell::updateCell(){
	if(isFCell && reinterpret_cast<FredkinCell*>(_c)->age==2){
		delete _c;
		_c=new ConwayCell('*');
	}
	else{
		_c->updateCell();
	} 
}

/**
 * @brief Method that determines next state of this Cell depending on the number of live neighbors
 * it has. The Life class collects a vector of the Cell's neighbors and passes it so that
 * the Cell can count them.
 * @param vector of neighbors surrounding cell
 */
void Cell::determineNextState(vector<AbstractCell*> neighbors){
	_c->determineNextState(neighbors);
}

/**
 * @brief Method that returns the currentState of this Cell, used by Life to count the population
 * of the board, and in the method determineNextState to determine the next state of the Cell.
 * @retval current state of cell
 */
bool Cell::isAlive(){
	return _c->isAlive();
}


/**
 * @brief Method that overrides the = operator to create a copy of this Cell.
 */
Cell& Cell::operator= (Cell const &c){
	isFCell=c.isFCell;
<<<<<<< HEAD
	delete _c;
=======
	if(_c!=nullptr)
		delete _c;
>>>>>>> master
	_c= c.clone();
	return *this;
}

/**
 * @brief Method that returns a string representation of the image of the cell being represented.
 */
string Cell::toString(){
	string s;
	if(isFCell)
		s=reinterpret_cast<FredkinCell*>(_c)->image;
	else
		s=reinterpret_cast<ConwayCell*>(_c)->image;
	return s;
}

/**
 * @brief Method that overrides the << operator to print out the image of this Cell.
 */
ostream& operator<<(std::ostream& os, Cell* c){
	return os << c->toString();
}


/**
 * @brief Method that reads the input from RunLife.in and prints the results to RunLife.out. It parses the information
 * that is passed in, creates a Life object, and passes the information to Life's methods to be processed.
 */
void runInput(istream& r, ostream& os){
		while(!r.eof()){
			string cellType;
			getline(r, cellType);

			string numRows;
			getline(r, numRows);
			int rows = atoi(numRows.c_str());

			string numCols;
			getline(r, numCols);
			int cols = atoi(numCols.c_str());

			string numGens;
			getline(r, numGens);
			int generations = atoi(numGens.c_str());

			string freqOut;
			getline(r, freqOut);
			int frequencyOut = atoi(freqOut.c_str());


			if(cellType=="ConwayCell"){
				vector<ConwayCell> allCells;
				for(int currentR=0; currentR<rows; currentR++){
					string currentRow;
					getline(r, currentRow);
					for(int i=0; i<cols; i++){
						ConwayCell temp(currentRow[i]);
						allCells.push_back(temp);
					}
				}
				Life<ConwayCell> l(rows,cols,allCells);
				cout<<"*** Life<"<<cellType<<"> "<<rows<<"x"<<cols<<"***\n"<<endl;
				for(int currentGen=0; currentGen<=generations; currentGen++){
					if(currentGen%frequencyOut==0){
						cout<<l<<endl;
					}					
					l.runTurn();		
				}
			}
			
			else if(cellType=="FredkinCell"){
				vector<FredkinCell> allCells;
				for(int currentR=0; currentR<rows; currentR++){
					string currentRow;
					getline(r, currentRow);
					for(int i=0; i<cols; i++){
						FredkinCell temp(currentRow[i]);
						allCells.push_back(temp);
					}
				}
				Life<FredkinCell> l(rows,cols,allCells);	
				cout<<"*** Life<"<<cellType<<"> "<<rows<<"x"<<cols<<"***\n"<<endl;
				for(int currentGen=0; currentGen<=generations; currentGen++){
					if(currentGen%frequencyOut==0){
						cout<<l<<endl;
					}
					l.runTurn();
				}		
			}
			else if(cellType=="Cell"){
				vector<Cell> allCells;
				for(int currentR=0; currentR<rows; currentR++){
					string currentRow;
					getline(r, currentRow);
					for(int i=0; i<cols; i++){
						Cell temp(currentRow[i]);
						allCells.push_back(temp);
					}
				}
				Life<Cell> l(rows,cols,allCells);	
				cout<<"*** Life<"<<cellType<<"> "<<rows<<"x"<<cols<<"***\n"<<endl;
				for(int currentGen=0; currentGen<=generations; currentGen++){
					if(currentGen%frequencyOut==0){
						cout<<l<<endl;
					}
					l.runTurn();
				}		
			}					
			string nextLine;
			getline(r,nextLine);
	}
}

