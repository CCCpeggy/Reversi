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
	//基準值
	int basicX;
	int basicY;
	//加權值
	int rightX;
	int rightY;
	//移動值
	int drawX;
	int drawY;
public:
	static const int BASIC_NOT_CHANGED;
	static const int RIGHT_NOT_CHANGED;
	//建置： 基準值XY、加權值XY
	Cursor(int = 0, int = 0, int = 1, int = 1);
	//重設：基準值、加權值
	Cursor& set(int = BASIC_NOT_CHANGED, int = BASIC_NOT_CHANGED, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	//移動：基準值、加權值
	Cursor& add(int = 0, int = 0, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	//移動輸入點
	Cursor& inputPos(int = 0, int = 0);
	//將輸入點移到下一行一開始
	Cursor& nextLine();
	//將輸入點移到同一行的下一個輸入點（類似ｔａｂ，只是是以加權值作為移動標準）
	Cursor& nextPos();
	Cursor& backPos();
	static void inputPos(int drawX, int drawY, int basicX, int basicY, int rightX = 1, int rightY = 1);
	static void setCursorHide();
	//取得子Cursor
	Cursor getSubCursor(int newDrawX, int newDrawY, int newRightX = 1, int newRightY = 1) const;
	Cursor& operator<< (const unsigned int); //設定顏色
	Cursor& operator<< (const pair<string, int>); //輸出置中字串（輸出字串、可輸出長度）
	Cursor& operator<< (const pair<int, int>); //設定座標
	Cursor& operator<< (const Cursor&); //不做事
	//輸出文字，除了"unsigned int"皆可
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
