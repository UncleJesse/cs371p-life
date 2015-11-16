#include "Life.h"
#include <string>



using namespace std;

//ConwayCell
ConwayCell::ConwayCell(char state){
	image= state;
	currentState= state=='*'? true : false;
	nextState=false;
}

bool ConwayCell::isAlive(){
	return currentState;
}

void ConwayCell::determineNextState(vector<ConwayCell> neighbors){
	int numberOfLiveNeighbors=0;
	for(int i=0; i< (int)neighbors.size(); i++){
		if(neighbors[i].isAlive())
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

void ConwayCell::updateCell(){
	currentState=nextState;
	image= nextState?'*':'.';
}

std::ostream& operator << (std::ostream& os, const ConwayCell* cc){
  return os << cc->image;
}

ConwayCell& ConwayCell::operator = (const ConwayCell &rhs){
	image=rhs.image;
	currentState=rhs.currentState;
	nextState=rhs.nextState;
	return *this;
}
//Fredkin Cell

FredkinCell::FredkinCell(char state){
	image= state;
	age=0;
	currentState= state=='0'? true : false;
	nextState=false;
}

void FredkinCell::determineNextState(vector<FredkinCell> neighbors){
	//a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
	int numberOfLiveNeighbors=0;
	for(int i=1; i< (int)neighbors.size(); i+=2){
		if(neighbors[i].isAlive())
			numberOfLiveNeighbors++;
	}
	if(currentState==false && (numberOfLiveNeighbors==1 || numberOfLiveNeighbors==3)){
		nextState=true;
	}
	else if(currentState==true && (numberOfLiveNeighbors==2 ||numberOfLiveNeighbors==4 || numberOfLiveNeighbors==0) ){
		nextState=false;
	}
	else{
		nextState=currentState;
	}
}

void FredkinCell::updateCell(){
	currentState=nextState;
	if(currentState){
		image=(age>10)?'+':age+'0';
		age++;
	}
	else
		image ='-';

}
bool FredkinCell::isAlive(){
	return currentState;
}

std::ostream& operator<<(std::ostream& os, const FredkinCell* fc){
	return os << fc->image;
}
FredkinCell& FredkinCell::operator= (const FredkinCell &rhs){
	image=rhs.image;
	currentState=rhs.currentState;
	nextState=rhs.nextState;
	age=rhs.age;
	return *this;
}
//Cell
Cell::Cell(char image){
	
}

//RunInput
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
			string nextLine;
			getline(r,nextLine);
	}
}

