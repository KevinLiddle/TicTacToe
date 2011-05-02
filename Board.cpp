#include "Board.h"


Board::Board(){
	for(int i=0; i<9; i++)
		state[i] = 0;
	score = -5;
	turn = 1;
}
void Board::SetScore(int x){
	score = x;
}
void Board::SetTurn(int x){
	turn = x;
}
void Board::SetState(int x, int y){
	state[x] = y;
}
int Board::GetState(int x){
	return state[x];
}
int Board::GetTurn(){
	return turn;
}
int Board::GetScore(){
	return score;
}
void Board::CopyBoard(Board Model){
	score = Model.score;
	for(int i=0; i<9; i++){
		state[i] = Model.state[i];
	}
}
bool Board::XWinsHorizontally(){
	return ((GetState(0) == 1 && GetState(1) == 1 && GetState(2) == 1) ||
		(GetState(3) == 1 && GetState(4) == 1 && GetState(5) == 1) ||
		(GetState(6) == 1 && GetState(7) == 1 && GetState(8) == 1));
}
bool Board::OWinsHorizontally(){
	return ((GetState(0) == -1 && GetState(1) == -1 && GetState(2) == -1) ||
                (GetState(3) == -1 && GetState(4) == -1 && GetState(5) == -1) ||
                (GetState(6) == -1 && GetState(7) == -1 && GetState(8) == -1));
}
bool Board::XWinsVertically(){
	return ((GetState(0) == 1 && GetState(3) == 1 && GetState(6) == 1) ||
                (GetState(1) == 1 && GetState(4) == 1 && GetState(7) == 1) ||
                (GetState(2) == 1 && GetState(5) == 1 && GetState(8) == 1));
}
bool Board::OWinsVertically(){
	return ((GetState(0) == -1 && GetState(3) == -1 && GetState(6) == -1) ||
                (GetState(1) == -1 && GetState(4) == -1 && GetState(7) == -1) ||
                (GetState(2) == -1 && GetState(5) == -1 && GetState(8) == -1));
}
bool Board::XWinsDiagonally(){
	return ((GetState(0) == 1 && GetState(4) == 1 && GetState(8) == 1) ||
		(GetState(2) == 1 && GetState(4) == 1 && GetState(6) == 1));
}
bool Board::OWinsDiagonally(){
	return ((GetState(0) == -1 && GetState(4) == -1 && GetState(8) == -1) ||
                (GetState(2) == -1 && GetState(4) == -1 && GetState(6) == -1));
}
int Board::Winner(){
	if(XWinsHorizontally() || XWinsVertically() || XWinsDiagonally()) return 1;
	if(OWinsHorizontally() || OWinsVertically() || OWinsDiagonally()) return -1;
	return 0;
}
bool Board::FullBoard(){
	for(int i=0; i<9; i++){
		if(GetState(i) == 0) return false;
	}
	return true;
}
bool Board::GameIsOver(){
	return ( FullBoard() || XWinsHorizontally() || OWinsHorizontally() ||
		XWinsVertically() || OWinsVertically() ||
		XWinsDiagonally() || OWinsDiagonally() );
}
void Board::PrintEndOfGameMessage(int first){
	if(first == 1) DrawBoard();
	if(Winner() == first) cout << "This is a mistake. You're not supposed to win!" << endl;
	else if(Winner() == (-1)*first) cout << "You lost to The Machine, as you should." << endl;
	else cout << "You have tied The Machine. Congratulations!" << endl;
}
int Board::GetUserInput(){
	
	int space = 0;
	bool go = true;
	string spaceInput;

	while(go){
		cout << "Enter Space Number (1-9): ";
		cin >> space;
		space--;
		if(space > 8 || space < 0 || GetState(space) != 0)
		cout << "Invalid Space!!!\n" << endl;
		else go = false;
	}
	return space;
}

int Board::FindOpenSpace(int index){
	while(index < 9 && GetState(index) != 0){
		index++;
	}
	return index;
}

void Board::CreateTree(){
	Board TemporaryBoard;
	int index = 0;

	if(!GameIsOver()){
		while(index < 9){
			index = FindOpenSpace(index);
			if(index >= 9) break;
			TemporaryBoard.CopyBoard(*this);
			TemporaryBoard.SetState(index,turn);
			TemporaryBoard.SetTurn((-1)*turn);
			NextPossibleBoards.push_back(TemporaryBoard);
			index++;
			NextPossibleBoards.back().CreateTree();
		}
	}
}
Board* Board::FindNextBoard(int space, int first){
	
	Board TemporaryBoard;
	
	TemporaryBoard.CopyBoard(*this);
	TemporaryBoard.SetState(space,first);
	for(unsigned int j = 0; j < NextPossibleBoards.size(); j++){
		if(TemporaryBoard == NextPossibleBoards[j]){
			return &NextPossibleBoards[j];
		}
	}
	return NULL;
}


void Board::DrawBoard(){

	char* marker;
	for(int i=0; i<5; i++){
		if(i!=1 && i!=3){
			for(int j=0; j<3; j++){
				switch(GetState(j+(3*i)/2)){
					case 1: marker = "X ";
						break;
					case -1: marker = "O ";
						break;
					case 0: marker = "  ";
						break;
					default:
						break;
				}
				if(j<2) cout << marker << "|";
				else cout<< marker;
			}
			cout << "\n";
		}
		else{
			cout << "--|--|--" <<endl;
		}
	}
}

void Board::SetBestMoveX(int index){

	if(NextPossibleBoards[index].GetScore() == 1)
		SetScore(1);
	else if(NextPossibleBoards[index].GetScore() == 0 && GetScore() != 1)
		SetScore(0);
	else if(NextPossibleBoards[index].GetScore() == -1 && GetScore() != 1 && GetScore() != 0)
		SetScore(-1);
}
void Board::SetBestMoveO(int index){

	if(NextPossibleBoards[index].GetScore() == -1)
		SetScore(-1);
	else if(NextPossibleBoards[index].GetScore() == 0 && (GetScore() != -1))
		SetScore(0);
	else if(NextPossibleBoards[index].GetScore() == 1 && (GetScore() != -1 && GetScore() != 0))
		SetScore(1);
}
void Board::SetWinnerOfPath(int PlayerTurn, int index){

	if(PlayerTurn == 1) SetBestMoveX(index);
	else if(PlayerTurn == -1) SetBestMoveO(index);
}


void Board::ScoreNodesInTree(){

	if(NextPossibleBoards.empty()){
		SetScore(Winner());
	}
	else{
		for(unsigned int i=0; i<NextPossibleBoards.size(); i++){
			NextPossibleBoards[i].ScoreNodesInTree();
			SetWinnerOfPath(GetTurn(), i);
		}
	}
}


Board * Board::MakeMachineMove(int mark){

	Board * temp = new Board();
	for(unsigned int it = 0; it < NextPossibleBoards.size(); it++){
		if(NextPossibleBoards[it].GetScore() == mark){
			return &(NextPossibleBoards[it]);
		}
		else if(NextPossibleBoards[it].GetScore() == 0 && temp->GetScore() != mark)
			temp = &(NextPossibleBoards[it]);
		else if(NextPossibleBoards[it].GetScore() == (-1)*mark && temp->GetScore() != 0 && temp->GetScore() != mark)
			temp = &(NextPossibleBoards[it]);
	}
	return &(*temp);
}

bool Board::operator==(Board OtherBoard){
	
	for(int i=0; i<9; i++){
		if(GetState(i) != OtherBoard.GetState(i)) return false;
	}
	return true;
}