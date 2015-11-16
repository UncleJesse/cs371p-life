#include "Life.h"
#include <string>



using namespace std;

//ConwayCell
ConwayCell::ConwayCell(bool state){
	image= state? '*' :'.';
	currentState= state? true : false;
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

FredkinCell::FredkinCell(bool state){
	image= state? '0' :'-';
	age=0;
	currentState= state? true : false;
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
		age++;
		image=(age>10)?'+':age+'0';
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

//Life
template<typename T>
Life<T>::Life(const int& r,const int& c,const vector<T> cells): rows(r), cols(c),board(r * c){
	population=0;
	for(int i=0; i<(int)cells.size(); i++){
		board[i]=cells[i];
		if(board.at(i).isAlive())
			population++;
	}
}

template<typename T>
T* Life<T>::at(const int& x, const int& y){
	return &board[cols * x + y];
}

template<typename T>
vector<T> Life<T>::cellNeighbors(int x, int y){
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

template<typename T>
bool Life<T>::inBounds(int r,int c){
	return (r<rows) && (r>=0) && (c<cols) && (c>=0);
}


template<typename T>
void Life<T>::runTurn(){
	population=0;
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

template<typename T>
typename vector<T>::iterator Life<T>::begin(){
	return board.begin();
}

template<typename T>
typename vector<T>::iterator Life<T>::end(){
	return board.end();
}

template<typename T>
ostream& operator << (ostream& os, Life<T>& l){
	for(int r = 0; r < l.rows; ++r){
		for(int c = 0; c < l.cols; ++c){
			os << l.at(r , c);
		}
		os << endl;

	}
	return os;
}


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
						if(currentRow[i]=='.'){
							ConwayCell temp;
							allCells.push_back(temp);
						}
						else{
							ConwayCell temp(true);
							allCells.push_back(temp);
						}
					}
				}
				Life<ConwayCell> l(rows,cols,allCells);

			cout<<"*** Life<"<<cellType<<"> "<<rows<<"x"<<cols<<"***\n"<<endl;
			for(int currentGen=0; currentGen<=generations; currentGen++){
				if(currentGen%frequencyOut==0){
					cout<<"Generation = "<<currentGen<<", Population = "<<l.population <<"."<<endl;
					cout<<l<<endl;
				}
				l.runTurn();
			}
			}
			else{
				vector<FredkinCell> allCells;
				for(int currentR=0; currentR<rows; currentR++){
					string currentRow;
					getline(r, currentRow);
					for(int i=0; i<cols; i++){
						if(currentRow[i]=='-'){
							FredkinCell temp;
							allCells.push_back(temp);
						}
						else{
							FredkinCell temp(true);
							allCells.push_back(temp);
						}
					}
				}
				Life<FredkinCell> l(rows,cols,allCells);

			cout<<"*** Life<"<<cellType<<"> "<<rows<<"x"<<cols<<"***\n"<<endl;
			for(int currentGen=0; currentGen<=generations; currentGen++){
				if(currentGen%frequencyOut==0){
					cout<<"Generation = "<<currentGen<<", Population = "<<l.population <<"."<<endl;
					cout<<l<<endl;
				}
				l.runTurn();
			}			
			}
			string nextLine;
			getline(r,nextLine);
	}
}