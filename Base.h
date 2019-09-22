#ifndef _Base__
#define _Base__
#include <string>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <sstream>

using namespace std;
class Side 
{
public:
	static const int WHITE;
	static const int BLACK;
	static const int NONE;
	static int getTheOtherSide(int side);
};

class Color {
public:
	static const unsigned int B_PURPLE;
	static const unsigned int B_GREEN;
	static const unsigned int B_CYAN;
	static const unsigned int B_RED;
	static const unsigned int F_PURPLE;
	static const unsigned int F_GREEN;
	static const unsigned int F_CYAN;
	static const unsigned int F_RED;
	static const unsigned int F_WHITE;
	static const unsigned int DEF_COLOR;
	static const unsigned int TAG_CHOOSE_COLOR;
	static const unsigned int B_WHITE_F_RED;
	static const unsigned int B_WHITE_F_GREEN;
};

class Direction {
public:
	static const unsigned int UP;
	static const unsigned int UP_RIGHT;
	static const unsigned int RIGHT;
	static const unsigned int DOWN_RIGHT;
	static const unsigned int DOWN;
	static const unsigned int DOWN_LEFT;
	static const unsigned int LEFT;
	static const unsigned int UP_LEFT;
};

class Key {
public:
	static const char REDO;
	static const char UNDO;
	static const char RESTART;
	static const char AUTO;
	static const char SET_SIZE;
	static const char SET_MUSIC;
	static int keyBoard();

};
#endif // !Base

class Parameter {
	static int SIZE;
	static bool MUSIC;
public:
	static void setSize(int size);
	static int getSize();
	static void setMusic(bool music);
	static bool getMusic();
};

class Draw {
private:
	static const string dialogueBox[10];
public:
	static void drawDialogueBox(string title, int num, string unit = "");
	static int showNumberDialog(string title, int number, int max, int min, int right, string unit);
	static void clear();
};

class Cursor
{
private:
	//��ǭ�
	int basicX;
	int basicY;
	//�[�v��
	int rightX;
	int rightY;
	//���ʭ�
	int drawX;
	int drawY;
public:
	static const int BASIC_NOT_CHANGED;
	static const int RIGHT_NOT_CHANGED;
	//�ظm�G ��ǭ�XY�B�[�v��XY
	Cursor(int = 0, int = 0, int = 1, int = 1);
	//���]�G��ǭȡB�[�v��
	Cursor& set(int = BASIC_NOT_CHANGED, int = BASIC_NOT_CHANGED, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	//���ʡG��ǭȡB�[�v��
	Cursor& add(int = 0, int = 0, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	//���ʿ�J�I
	Cursor& inputPos(int = 0, int = 0);
	//�N��J�I����U�@��@�}�l
	Cursor& nextLine();
	//�N��J�I����P�@�檺�U�@�ӿ�J�I�]���������A�u�O�O�H�[�v�ȧ@�����ʼзǡ^
	Cursor& nextPos();
	Cursor& backPos();
	static void inputPos(int drawX, int drawY, int basicX, int basicY, int rightX = 1, int rightY = 1);
	static void setCursorHide();
	//���o�lCursor
	Cursor getSubCursor(int newDrawX, int newDrawY, int newRightX = 1, int newRightY = 1) const;
	Cursor& operator<< (const unsigned int); //�]�w�C��
	Cursor& operator<< (const pair<string, int>); //��X�m���r��]��X�r��B�i��X���ס^
	Cursor& operator<< (const pair<int, int>); //�]�w�y��
	Cursor& operator<< (const Cursor&); //������
	//��X��r�A���F"unsigned int"�ҥi
	template <class T>
	Cursor& operator<< (const T outputString) {
		cout << outputString;
		return *this;
	}
	int getCursorX() const;
	int getCursorY() const;
	int getRightX() const;
	int getRightY() const;
	~Cursor();
};
