#include "Board.h"

using namespace std;

int ChooseUserTurn(){
	int input = 0;
	while(input != 1 && input != -1){
		cout << "Enter 1 to go first (X) or 2 to go second (O): ";
		cin >> input;
		if(input == 2) input = -1;
	}
	return input;
}

bool PlayOrQuit(){
	string str;
	cout << "Press Q to Quit, or any other key to play again: ";
	cin.ignore();
	getline (cin, str);
	return !(str == "q" || str == "Q");
}



int main(){

	int spot;
	int first = 0;
	bool UserIsStillPlaying = true;
	Board BlankBoard;
	Board * CurrentBoard;

	BlankBoard.CreateTree();
	BlankBoard.ScoreNodesInTree();


	while(UserIsStillPlaying){
		CurrentBoard = &BlankBoard;
		first = ChooseUserTurn();
		
		while(!CurrentBoard->GameIsOver()){
			if(first == -1 && !CurrentBoard->GameIsOver())
				CurrentBoard = &(*(CurrentBoard->MakeMachineMove((-1)*first)));
				
			CurrentBoard->DrawBoard();
			
			if(CurrentBoard->GameIsOver())
				break;
				
			spot = CurrentBoard->GetUserInput();
			
			CurrentBoard = &(*(CurrentBoard->FindNextBoard(spot, first)));
			
			if(first == 1 && !CurrentBoard->GameIsOver())
				CurrentBoard = &(*(CurrentBoard->MakeMachineMove((-1)*first)));
		}
		CurrentBoard->PrintEndOfGameMessage(first);
		
		UserIsStillPlaying = PlayOrQuit();
		first = 0;
	}

	return 0;
}
