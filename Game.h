#ifndef GAME_CLASS_DEFINE
#define GAME_CLASS_DEFINE
#include "Board.h"
#include <vector>
class Game
{
public:
	Game();
	~Game();
	vector<Board*> boards;
	int boardIndex;
	int side;
	void play();
private:
	int size;
	Cursor wordCursor;
	pair<int, int> choosePiece(pair<int, int> pos);
	int pushBoard(Board* board);
	void redoBoard();
	void undoBoard();
};

#endif // !GAME_CLASS_DEFINE
