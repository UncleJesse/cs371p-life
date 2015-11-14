#include "Life.h"
#include <string>



using namespace std;

//ConwayCell
ConwayCell::ConwayCell(bool state){
	image= state? '*' :'.';
	currentState= state? false : true;
	nextState=false;
}

bool ConwayCell::isAlive(){
	return image!='.';
}

void ConwayCell::determineNextState(vector<ConwayCell> neighbors){
	int numberOfLiveNeighbors=0;
	for(int i=0; i< (int)neighbors.size(); i++){
		if(neighbors[i].isAlive())
			numberOfLiveNeighbors++;
	}
	if(currentState==false && numberOfLiveNeighbors==3){
		nextState=true;
		image='*';
	}
	if(currentState==true && (numberOfLiveNeighbors<2 ||numberOfLiveNeighbors>3) ){
		nextState=false;
		image='.';
	}
}

void ConwayCell::updateCell(){
	currentState=nextState;
	nextState=false;
}

std::ostream& operator << (std::ostream& os, const ConwayCell& cc){
  return os << cc.image;
}



//Life
Life::Life(const int& r,const int& c): rows(r), cols(c), board(r * c){
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
				if(!(r==x && c==y) && Life::inBounds(r,c))
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
	for(int currentGeneration=0; currentGeneration<generation; currentGeneration++)
		for(int r=0; r<rows; r++){
			for(int c=cols; c<cols; c++){	
					at(r,c).determineNextState(cellNeighbors(r,c));
				}
		}
		for(int r=0; r<rows; r++){
			for(int c=cols; c<cols; c++){	
					at(r,c).updateCell();
				}
		}
}


vector<ConwayCell>::iterator Life::begin(){
	return board.begin();
}

vector<ConwayCell>::iterator Life::end(){
	return board.end();
}


void runLife(istream& r, ostream& os){
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

	string s;
	while (getline(r, s)) {
		cout<<"s: "<<s<<endl;
		for(int i=0; i<(int)s.length(); i++){
			
		}
		getline(r, s);
	}
	
}