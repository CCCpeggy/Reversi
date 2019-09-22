#ifndef BOARD_CLASS_DEFINE
#define BOARD_CLASS_DEFINE
#include <string>
#include "Piece.h"
#include <vector>
using namespace std;

class Board {
private:
	int size;
	int side;
	int nextSide;
	const Cursor cursor;
	vector<vector<Piece*> > piece;
	pair<int, int> findPair(int x, int y, int direction, int side);
	pair<int, int> getRight(int direction);
	bool checkScope(int x, int y);
	bool checkSide(int side);
public:
	static const string symbol[3];
	Board(int size, int nextSide);
	Board(const Board&, int side);
	~Board();
	void draw();
	void drawPlayer();
	void putPiece(pair<int, int> pos);
	bool checkPos(int x, int y, int side);
	int getWinner();
	int getSide();
	int getNextSide();
	int getBlackCount();
	int getWhiteCount();
	pair<int, int> getNextBestStep();
	void select(int x, int y);
	void cancelSelect(int x, int y);
};

#endif // !1
