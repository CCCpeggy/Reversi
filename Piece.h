#ifndef PIECE_CLASS_DEFINE
#define PIECE_CLASS_DEFINE
#include "Base.h"
#include <string>
#include <map>

class Piece
{
private:
	int side;
	bool selected = false;
	Cursor cursor;
	static map<int, string> symbol;

public:
	Piece(Cursor cursor, int side = Side::NONE, bool selected = false);
	Piece(const Piece&);
	void draw();
	void select();
	void cancelSelect();
	void turn();
	void put(int side);
	int getSide();
};


#endif // !PIECE_CLASS_DEFINE
