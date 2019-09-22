#include "Piece.h"

map<int, string> Piece::symbol = {
	{Side::WHITE, "¡´"},
	{Side::BLACK, "¡³"},
	{Side::NONE, "¡@"}
};

void Piece::turn()
{
	side = side == Side::BLACK ? Side::WHITE : Side::BLACK;
	draw();
}

void Piece::put(int newSide)
{
	side = newSide;
	draw();
}

int Piece::getSide()
{
	return side;
}


Piece::Piece(Cursor cursor, int side, bool selected)
	: cursor(cursor), side(side), selected(selected)
{
}

Piece::Piece(const Piece& piece) : cursor(piece.cursor), side(piece.side), selected(piece.selected)
{

}

void Piece::draw()
{
	cursor.inputPos(2, 1);
	cursor << (selected ? Color::TAG_CHOOSE_COLOR : Color::DEF_COLOR);
	cursor << symbol[side];
}

void Piece::select()
{
	selected = true;
	draw();
}

void Piece::cancelSelect()
{
	selected = false;
	draw();
}
