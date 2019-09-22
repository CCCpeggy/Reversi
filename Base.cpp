#include "Base.h"

extern HANDLE handleOutput;

const unsigned int Color::B_PURPLE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_RED;
const unsigned int Color::B_GREEN = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN;
const unsigned int Color::B_CYAN = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN;
const unsigned int Color::B_RED = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED;
const unsigned int Color::F_PURPLE = FOREGROUND_BLUE | FOREGROUND_RED;
const unsigned int Color::F_GREEN = FOREGROUND_GREEN;
const unsigned int Color::F_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN;
const unsigned int Color::F_RED = FOREGROUND_RED;
const unsigned int Color::F_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const unsigned int Color::DEF_COLOR = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const unsigned int Color::TAG_CHOOSE_COLOR = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
const unsigned int Color::B_WHITE_F_GREEN = FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
const unsigned int Color::B_WHITE_F_RED = FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

const int Side::WHITE = 1;
const int Side::BLACK = -1;
const int Side::NONE = 0;


const unsigned int Direction::UP = 0; //0001
const unsigned int Direction::UP_RIGHT = 1; // 0011
const unsigned int Direction::RIGHT = 2; // 0010
const unsigned int Direction::DOWN_RIGHT = 3; // 0110
const unsigned int Direction::DOWN = 4; // 0100
const unsigned int Direction::DOWN_LEFT = 5; // 1100
const unsigned int Direction::LEFT = 6; // 1000
const unsigned int Direction::UP_LEFT = 7; // 

const char Key::REDO = 'y';
const char Key::UNDO = 'z';
const char Key::RESTART = 'r';
const char Key::AUTO = 'a';
const char Key::SET_SIZE = 's';
const char Key::SET_MUSIC = 'm';

int Parameter::SIZE = 6;
bool Parameter::MUSIC = true;

const string Draw::dialogueBox[10] = { "■———————————————————————■" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"■———————————————————————■" };

const int Cursor::BASIC_NOT_CHANGED = -1;
const int Cursor::RIGHT_NOT_CHANGED = -1;


int Key::keyBoard()
{
	DWORD consoleCnt;
	INPUT_RECORD input;
	while (ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &consoleCnt))
	{
		if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown == TRUE)
		{
			switch (input.Event.KeyEvent.wVirtualKeyCode) {
			case VK_UP: //26
			case VK_DOWN: //28
			case VK_LEFT: //25
			case VK_RIGHT: //27
			case VK_RETURN:
			case VK_ESCAPE:
				return input.Event.KeyEvent.wVirtualKeyCode;

			default:
				char inputChar = input.Event.KeyEvent.uChar.AsciiChar;
				if (inputChar >= 'A' && inputChar <= 'Z') inputChar = inputChar - 'A' + 'a';
				switch (inputChar)
				{
				case Key::REDO:
				case Key::UNDO:
				case Key::RESTART:
				case Key::AUTO:
				case Key::SET_SIZE:
				case Key::SET_MUSIC:
					return input.Event.KeyEvent.uChar.AsciiChar;
				}
			}

		}
	}

}

int Side::getTheOtherSide(int side)
{
	return side == Side::BLACK ? Side::WHITE : Side::BLACK;
}

void Parameter::setSize(int size)
{
	if (size > 0)
		SIZE = size;
}

int Parameter::getSize()
{
	return SIZE;
}

void Parameter::setMusic(bool music)
{
	MUSIC = music;
}

bool Parameter::getMusic()
{
	return MUSIC;
}

void Draw::drawDialogueBox(string title, int num, string unit)
{
#define DIALOG_CONTENT_LEN 46
	//TODO: 顯示數字對話框
	Cursor cursor = Cursor(1, 5);

	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	cursor.add(2, 2, DIALOG_CONTENT_LEN / 3);
	cursor << pair<string, int>(title, DIALOG_CONTENT_LEN);
	stringstream ss;
	ss << num << unit;
	cursor.nextLine().nextLine().nextLine().nextLine();
	cursor << Color::DEF_COLOR << pair<string, int>("　－　", DIALOG_CONTENT_LEN / 3);
	cursor.nextPos();
	cursor << Color::TAG_CHOOSE_COLOR << pair<string, int>(ss.str(), DIALOG_CONTENT_LEN / 3);
	cursor.nextPos();
	cursor << Color::DEF_COLOR << pair<string, int>("　＋　", DIALOG_CONTENT_LEN / 3);
}

int Draw::showNumberDialog(string title, int number, int max, int min, int right, string unit)
{
	clear();
	drawDialogueBox(title, number, unit);
	int getKey = Key::keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_ESCAPE) {
			number = -1;
			break;
		}
		if (getKey == VK_RIGHT || getKey == VK_LEFT) {
			number += getKey == VK_RIGHT ? 1 * right : -1 * right;
			number = number > max ? max : number;
			number = number < min ? min : number;
			drawDialogueBox(title, number, unit);
		}
		getKey = Key::keyBoard();
	}
	return number;
}

void Draw::clear()
{
	SetConsoleTextAttribute(handleOutput, Color::DEF_COLOR);
	system("cls");
}

Cursor::Cursor(int basicX, int basicY, int rightX, int rightY)
	:basicX(basicX), basicY(basicY), rightX(rightX), rightY(rightY), drawX(0), drawY(0)
{
	SetConsoleTextAttribute(handleOutput, Color::DEF_COLOR);
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
}

Cursor& Cursor::set(int newBasicX, int newBasicY, int newRightX, int newRightY)
{
	if (newBasicX >= 0) basicX = newBasicX;
	if (newBasicY >= 0) basicY = newBasicY;
	if (newRightX != RIGHT_NOT_CHANGED) rightX = newRightX;
	if (newRightY != RIGHT_NOT_CHANGED) rightY = newRightY;
	drawX = 0;
	drawY = 0;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor & Cursor::add(int newBasicX, int newBasicY, int newRightX, int newRightY)
{
	return set(newBasicX + basicX, newBasicY + basicY, newRightX, newRightY);
}

Cursor& Cursor::inputPos(int newDrawX, int newDrawY)
{
	drawY = newDrawY;
	drawX = newDrawX;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor& Cursor::nextLine()
{
	drawX = 0;
	drawY++;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor& Cursor::nextPos()
{
	drawX++;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor& Cursor::backPos()
{
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

void Cursor::inputPos(int drawX, int drawY, int basicX, int basicY, int rightX, int rightY)
{
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
}

void Cursor::setCursorHide()
{
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 1;
	lpCursor.bVisible = false;
	SetConsoleCursorInfo(handleOutput, &lpCursor);
}

Cursor Cursor::getSubCursor(int newDrawX, int newDrawY, int newRightX, int newRightY) const
{
	return Cursor(basicX + newDrawX * rightX, basicY + newDrawY * rightY, newRightX, newRightY);
}

Cursor& Cursor::operator<<(const unsigned int color)
{
	SetConsoleTextAttribute(handleOutput, color);
	return *this;
}

Cursor& Cursor::operator<<(const pair<string, int> outputString)
{
	int stringLength = outputString.first.length();
	int containerLength = outputString.second;
	int centerX = (containerLength - stringLength) / 2;
	if (stringLength < containerLength) {
		COORD pos;
		pos.X = basicX + centerX + drawX * rightX;
		pos.Y = basicY + drawY * rightY;
		SetConsoleCursorPosition(handleOutput, pos);
	}
	cout << outputString.first;
	return *this;
}

Cursor& Cursor::operator<<(const pair<int, int> coordinate)
{
	inputPos(coordinate.first, coordinate.second);
	return *this;
}

Cursor& Cursor::operator<<(const Cursor&)
{
	return *this;
}

int Cursor::getCursorX() const
{
	return basicX + drawX * rightX;
}

int Cursor::getCursorY() const
{
	return basicY + drawY * rightY;
}

int Cursor::getRightX() const
{
	return rightX;
}

int Cursor::getRightY() const
{
	return rightY;
}

Cursor::~Cursor()
{
	SetConsoleTextAttribute(handleOutput, Color::DEF_COLOR);
	Cursor::setCursorHide();
}
