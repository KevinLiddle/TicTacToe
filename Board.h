#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "math.h"
#include <string>
#include <sstream>

using namespace std;

class Board{
public:
	Board();
	vector<Board> NextPossibleBoards;
	void CopyBoard(Board Model);
	void DrawBoard();
	void ScoreNodesInTree();
	Board* MakeMachineMove(int mark);
	void CreateTree();
	Board* FindNextBoard(int space, int first);
	
	int FindOpenSpace(int index);
	void SetBestMoveX(int index);
	void SetBestMoveO(int index);
	void SetWinnerOfPath(int PlayerTurn, int index);
	
	bool XWinsHorizontally();
	bool OWinsHorizontally();
	bool XWinsVertically();
	bool OWinsVertically();
	bool XWinsDiagonally();
	bool OWinsDiagonally();
	int Winner();
	bool FullBoard();
	bool GameIsOver();
	void PrintEndOfGameMessage(int first);
	int GetUserInput();
	
	bool operator==(Board OtherBoard);
	
	void SetScore(int x);
	void SetTurn(int x);
	void SetState(int x, int y);
	int GetState(int x);
	int GetScore();
	int GetTurn();
private:
	int score;
	int turn;
	int state[9];// 1 for X, -1 for O, 0 for nothing

};

#endif