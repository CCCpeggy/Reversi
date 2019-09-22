#include "Game.h"
Game::Game() :side(Side::BLACK), boardIndex(-1), size(Parameter::getSize()), wordCursor(size * 2 - 2, size * 2 + 2)
{
	pushBoard(new Board(size, side));
	boards[boardIndex]->draw();
	if(Parameter::getMusic()) PlaySound((char*)"forest.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Game::play()
{
	pair<int, int> pos = pair<int, int>(0, 0);
	while(true) {
		pos = choosePiece(pos);
		if (pos.first < 0) break;
		pushBoard(new Board(*boards[boardIndex], side));
		boards[boardIndex]->putPiece(pos);
		boards[boardIndex]->drawPlayer();
		side = boards[boardIndex]->getNextSide();
		if (side == Side::NONE) {
			int winSide = boards[boardIndex]->getWinner();
			wordCursor.inputPos(0, 0);
			if (winSide == Side::NONE) wordCursor << "雙方平手";
			else if (winSide == Side::BLACK) wordCursor << "黑色獲勝";
			else if (winSide == Side::WHITE) wordCursor << "白色獲勝";
			Key::keyBoard();
			break;
		}
	}

	Draw::clear();
}

int Game::pushBoard(Board* board)
{
	if(boardIndex >= 0)
		boards.erase(boards.begin() + boardIndex + 1, boards.end());
	boardIndex++;
	boards.push_back(board);
	return boards.size() - 1;
}

void Game::redoBoard()
{
	if ((boardIndex + 1) < boards.size()) {
		boardIndex++;
		boards[boardIndex]->draw();
		side = boards[boardIndex]->getNextSide();
	}
}

void Game::undoBoard()
{
	if (boardIndex - 1 >= 0) {
		boardIndex--;
		boards[boardIndex]->draw();
		side = boards[boardIndex]->getNextSide();
	}
}

pair<int, int> Game::choosePiece(pair<int, int> pos)
{
	int tmpX = pos.first, tmpY = pos.second;
	do {
		boards[boardIndex]->select(tmpX, tmpY);
		int getKey = Key::keyBoard();
		while (getKey != VK_RETURN) {
			if (getKey == VK_RIGHT || getKey == VK_LEFT || getKey == VK_DOWN || getKey == VK_UP) {
				boards[boardIndex]->cancelSelect(tmpX, tmpY);
				if (getKey == VK_RIGHT) {
					tmpX++;
				}
				else if (getKey == VK_LEFT) {
					tmpX--;
				}
				else if (getKey == VK_DOWN) {
					tmpY++;
				}
				else if (getKey == VK_UP) {
					tmpY--;
				}
				tmpX = (tmpX + size) % size;
				tmpY = (tmpY + size) % size;
				boards[boardIndex]->select(tmpX, tmpY);
			}
			
			else if (getKey == Key::UNDO) {
				undoBoard();
			}
			else if (getKey == Key::REDO) {
				redoBoard();
			}
			else if (getKey == Key::RESTART) {
				return pair<int, int>(-1, -1);
			}
			else if (getKey == Key::AUTO) {
				boards[boardIndex]->cancelSelect(tmpX, tmpY);
				return boards[boardIndex]->getNextBestStep();
			}
			else if (getKey == Key::SET_SIZE) {
				Parameter::setSize(Draw::showNumberDialog("棋盤格數", Parameter::getSize(), 16, 6, 2, "格"));
				return pair<int, int>(-1, -1);
			}
			else if (getKey == Key::SET_MUSIC) {
				Parameter::setMusic(!Parameter::getMusic());
				if(Parameter::getMusic())
					PlaySound((char*)"forest.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				else
					PlaySound(NULL, NULL, SND_FILENAME);
			}
			getKey = Key::keyBoard();
		}
	} while (!boards[boardIndex]->checkPos(tmpX, tmpY, boards[boardIndex]->getNextSide()));
	boards[boardIndex]->cancelSelect(tmpX, tmpY);
	return pair<int, int>(tmpX, tmpY);
}

Game::~Game()
{
}
