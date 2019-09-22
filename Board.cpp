#include "Board.h"

const string Board::symbol[3] = {
	"．—．",
	"｜　｜",
	"．—．"
};

Board::Board(int size, int nextSide):cursor(0, 0, 4, 2), size(size), piece(size), side(Side::NONE), nextSide(nextSide)
{
	Cursor thisCursor = cursor;
	for (int i = 0; i < size; i++) {
		piece[i].resize(size);
		for (int j = 0; j < size; j++) {
			Cursor subCursor = cursor.getSubCursor(j, i);
			piece[i][j] = new Piece(subCursor);
			thisCursor.nextPos();
		}
		thisCursor.nextLine();
	}
	int center = size / 2;
	for (int i = center - 1; i <= center; i++) {
		for (int j = center - 1; j <= center; j++) {
			int side = ((i == center) ^ (j == center)) ? Side::BLACK : Side::WHITE;
			piece[i][j]->put(side);
		}
	}
}

Board::Board(const Board& board, int side) :cursor(board.cursor), size(board.size), piece(board.size), side(side), nextSide(Side::NONE)
{
	for (int i = 0; i < size; i++) {
		piece[i].resize(size);
		for (int j = 0; j < size; j++) {
			piece[i][j] = new Piece(*board.piece[i][j]);
		}
	}
}

void Board::draw()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			Cursor subCursor = cursor.getSubCursor(j, i, 1, 1);
			for (int k = 0; k < 3; k++) {
				subCursor << symbol[k]; 
				subCursor.nextLine();
			}
			piece[i][j]->draw();
		}
	}
	drawPlayer();
}

void Board::drawPlayer()
{
	Cursor wordCursor(size * 2 - 2, size * 2 + 2);
	if (nextSide == Side::BLACK) wordCursor << "黑色玩家";
	else if (nextSide == Side::WHITE) wordCursor << "白色玩家";
}

void Board::putPiece(pair<int, int> pos)
{
	piece[pos.second][pos.first]->put(side);
	for (int direction = 0; direction < 8; direction++) {
		pair<int, int> pairPos = findPair(pos.first, pos.second, direction, side);
		if (pairPos.first < 0) continue;
		pair<int, int> right = getRight(direction);
		int rightX = right.first, rightY = right.second;
		for (int x = pos.first + rightX, y = pos.second + rightY; x != pairPos.first || y != pairPos.second; x += rightX, y += rightY) {
			piece[y][x]->turn();
		}
	}
	if (checkSide(Side::getTheOtherSide(side))) nextSide = Side::getTheOtherSide(side);
	else if (checkSide(Side::getTheOtherSide(side))) nextSide = side;
}

int Board::getWinner()
{
	int blackCount = getBlackCount(), whiteCount = getWhiteCount();
	if (blackCount == whiteCount) return Side::NONE;
	return blackCount > whiteCount ? Side::BLACK : Side::WHITE;
}

int Board::getSide()
{
	return side;
}

int Board::getNextSide()
{
	return nextSide;
}

int Board::getBlackCount()
{
	int count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			count += piece[i][j]->getSide() == Side::BLACK ? 1 : 0;
		}
	}
	return count;
}

int Board::getWhiteCount()
{
	int count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			count += piece[i][j]->getSide() == Side::WHITE ? 1 : 0;
		}
	}
	return count;
}

pair<int, int> Board::getNextBestStep()
{
	int maxX = -1, maxY = -1, maxValue = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int direction = 0; direction < 8; direction++) {
				if (piece[i][j]->getSide() == Side::NONE) {
					pair<int, int> pairPiece = findPair(j, i, direction, nextSide);
					if (pairPiece.first >= 0) {
						pair<int, int> right = getRight(direction);
						int distanceX = (pairPiece.first - j) * right.first;
						int distanceY = (pairPiece.second - i) * right.second;
						if (distanceX > maxValue || distanceY > maxValue) {
							maxValue = distanceX > distanceY ? distanceX : distanceY;
							maxX = j;
							maxY = i;
						}
					}
				}
			}
		}
	}
	return pair<int, int>(maxX, maxY);
}

void Board::select(int x, int y)
{
	piece[y][x]->select();
}

void Board::cancelSelect(int x, int y)
{
	piece[y][x]->cancelSelect();

}

Board::~Board()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			delete piece[i][j];
		}
	}
}


bool Board::checkPos(int x, int y, int side)
{
	if (piece[y][x]->getSide() != Side::NONE) return false;
	for (int direction = 0; direction < 8; direction++) {
		if (findPair(x, y, direction, side).first >= 0) return true;
	}
	return false;
}

pair<int, int> Board::getRight(int direction)
{
	int rightX = 0, rightY = 0;

	if (direction == Direction::LEFT || direction == Direction::UP_LEFT || direction == Direction::DOWN_LEFT) rightX = -1;
	else if (direction == Direction::RIGHT || direction == Direction::UP_RIGHT || direction == Direction::DOWN_RIGHT) rightX = 1;

	if (direction == Direction::UP || direction == Direction::UP_LEFT || direction == Direction::UP_RIGHT) rightY = -1;
	else if (direction == Direction::DOWN || direction == Direction::DOWN_LEFT || direction == Direction::DOWN_RIGHT) rightY = 1;
	return pair<int, int>(rightX, rightY);
}

bool Board::checkScope(int x, int y)
{
	return (x < size && y < size && x >= 0 && y >= 0);
}

bool Board::checkSide(int side)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int direction = 0; direction < 8; direction++) {
				if (piece[i][j]->getSide() == Side::NONE && findPair(j, i, direction, side).first >= 0) {
					return true;
				}
			}
		}
	}
	return false;
}

pair<int, int> Board::findPair(int x, int y, int direction, int side)
{
	int theOtherSide = Side::getTheOtherSide(side);
	pair<int, int> right = getRight(direction);
	int rightX = right.first, rightY = right.second;

	x += rightX;
	y += rightY;
	if (checkScope(x, y) && theOtherSide == piece[y][x]->getSide()) {
		do {
			if (piece[y][x]->getSide() == side) return pair<int, int>(x, y);
			x += rightX;
			y += rightY;
		} while (checkScope(x, y) && Side::NONE != piece[y][x]->getSide());
	}
	return pair<int, int>(-1, -1);
}