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

void ConwayCell::determineNextState(vector<ConwayCell*> neighbors){
	int numberOfLiveNeighbors=0;
	for(int i=0; i< (int)neighbors.size(); i++){
		if(neighbors[i]->isAlive())
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

void FredkinCell::determineNextState(vector<FredkinCell*> neighbors){
	int numberOfLiveNeighbors=0;
	for(int i=1; i< (int)neighbors.size(); i++){
		if(neighbors[i]->isAlive())
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

void FredkinCell::updateCell(){
	currentState=nextState;
	if(currentState){		
		age++;
		image=(age>10)?'+':(char)age;
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
Life::Life(const int& r,const int& c,const vector<ConwayCell*> cells): rows(r), cols(c),board(r * c){
	population=0;
	board.resize(0);
	cout<<cells.size()<<endl;	
	cout<<board.size()<<endl;
	for(int i=0; i<(int)cells.size(); i++){
		board.push_back(cells[i]);
		if(board.at(i)->isAlive())			
			population++;
	}
}

ConwayCell* Life::at(const int& x, const int& y){
	return board[cols * x + y];
}

vector<ConwayCell*> Life::cellNeighbors(int x, int y){
	vector<ConwayCell*> neighbors;
	for(int r=(x-1); r<=x+1; r++){
		for(int c=(y-1); c<=y+1; c++){
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

void Life::runTurn(){
	population=0;
	for(int r=0; r<rows; r++){
		for(int c=0; c<cols; c++){	
			vector<ConwayCell*> temp=cellNeighbors(r,c);
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
	//cout<<*this<<endl;
}

/*void Life::printBoard(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			cout<<at(i,j);
		}
		cout<<endl;
	}
}*/

vector<ConwayCell*>::iterator Life::begin(){
	return board.begin();
}

vector<ConwayCell*>::iterator Life::end(){
	return board.end();
}

std::ostream& operator << (std::ostream& os, Life& l){
	for(int r = 0; r < l.rows; ++r){
		for(int c = 0; c < l.cols; ++c){
			os << l.at(r , c);
		}
		os << endl;
	}
	return os;
}

void runInput(istream& r, ostream& os){
	cout << "start" << endl;
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
			
			vector<ConwayCell*> allCells;
			for(int currentR=0; currentR<rows; currentR++){
				string currentRow;
				getline(r, currentRow);				
				for(int i=0; i<cols; i++){
					if(currentRow[i]=='.'){
						ConwayCell* temp= new ConwayCell(false);
						allCells.push_back(temp);
					}
					else{
						ConwayCell* temp= new ConwayCell(true);
						allCells.push_back(temp);
					}
				}
			}

			Life l(rows,cols,allCells);

			cout<<"*** Life<"<<cellType<<"> "<<rows<<"x"<<cols<<"***\n"<<endl;
			for(int currentGen=0; currentGen<=generations; currentGen++){
				if(currentGen%frequencyOut==0){
					cout<<"Generation = "<<currentGen<<", Population = "<<l.population <<"."<<endl;
					cout<<l<<endl;
				}
				l.runTurn();
			}
			string nextLine;
			getline(r,nextLine);
	}
}