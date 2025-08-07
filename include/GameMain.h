#pragma once

class Config;
class GameBuilder;
class View;
class Sequence;

class GameMain
{
public:
	enum State
	{
		ST_STARTMENU,
		ST_PLAY,
		ST_EXIT,
		ST_NONE
	};

	GameMain(void);
	~GameMain(void);

	void gameStart( void );
	void gameInitialize( void );
	void moveTo( State );

private:
	State startMenu();
	State play();
	void cleanUp();
	State getMoveTo();

	Config* mConfig;
	GameBuilder* mGameBuilder;
	View* mView;
	Sequence* mSequence;

	State mState;
	State mMoveTo;
};
