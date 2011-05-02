TTT.out : TicTacToe.o Board.o
	g++ -o TTT.out TicTacToe.o Board.o
  
TicTacToe.o : TicTacToe.cpp Board.cpp Board.h
	g++ -c TicTacToe.cpp
  
Board.o : Board.cpp Board.h
	g++ -c Board.cpp
  
clean:
	&nbps rm *.o TTT.out
