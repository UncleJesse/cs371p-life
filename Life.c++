#include "Life.h"
#include <string>



using namespace std;

bool ConwayCell::isAlive(){
	return true;
}
//ConwayCell
void ConwayCell::determineNextState(vector<ConwayCell> neighbors){
	int numOfLiveNeighbors=0;
	for(int i=0; i< (int)neighbors.size(); i++){
		if(neighbors[i].isAlive())
			numOfLiveNeighbors++;
	}
}


ConwayCell::ConwayCell(){
	image='.';
	currentState=false;
	nextState=false;
}



//Life
Life::Life(const int& r,const int& c) : rows(r), cols(c), board(r * c){
	generation=0;
}

ConwayCell Life::at(const int& x, const int& y){
	return board[rows * x + y];
}

vector<ConwayCell> Life::cellNeighbors(int x, int y){
	vector<ConwayCell> neighbors;
	for(int r=(x-1); r<x+1; r++){
		for(int c=(y-1); c<y+1; c++){
			{	
				if(r!=c && Life::inBounds(r,c))
					neighbors.push_back(Life::at(r,c));
			}
		}
	}
	return neighbors;
}

bool Life::inBounds(int r,int c){
	return (r<rows) && (r>=0) && (c<cols) && (c>=0);
}

void Life::runTurn(vector<ConwayCell> board){
	for(int r=0; r<rows; r++){
		for(int c=cols; c<cols; c++){	
				at(r,c).determineNextState(cellNeighbors(r,c));
			}
		}
}

vector<ConwayCell>::iterator Life::begin(){
	return board.begin();
}

vector<ConwayCell>::iterator Life::end(){
	return board.end();
}

std::ostream& operator << (std::ostream& os, Life& l){

	/* Generate row numbers and contents of board */
	for(int i = 0; i < l.rows; ++i){
		os << (i % 10);	/* row number */
		/* display creature or . if empty space*/
		for(int j = 0; j < l.cols; ++j){
				ConwayCell c = l.at(i , j);
				os << ".";
		}
		/* start a newline*/
		if(i < l.rows - 1)	 os << "\n";
	}
	return os;

}

/*
void processInput(istream& r, ostream& os){

	string cellType;
	getline(r, cellType);
	cout<<"cellType: "<<cellType<<endl;

	string numRows;
	getline(r, numRows);			
	int rows = atoi(numRows.c_str());
	cout<<"numRows: "<<rows<<endl;

	string numCols;
	getline(r, numCols);
	int cols = atoi(numCols.c_str());
	cout<<"cols: "<<cols<<endl;
	
	string numGens;
	getline(r, numGens);
	int generations = atoi(numGens.c_str());
	cout<<"generations: "<<generations<<endl;
	
	string freqOut;
	getline(r, freqOut);
	int frequencyOut = atoi(freqOut.c_str());
	cout<<"frequency: "<<frequencyOut<<endl;

	string s;
	while (getline(r, s)) {
		cout<<"s: "<<s<<endl;
		getline(r, s);
	}
	
}*/