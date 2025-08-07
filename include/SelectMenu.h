#pragma once
#include <string>

using namespace std;

class SelectMenu
{
public:
	SelectMenu( int );
	~SelectMenu(void);

	void addWord( string );
	void draw();
	int getInput() const;

private:
	string* mWords;
	int mWordMax;
	int mWordNum;
	int mResponse;
};
