#pragma once
#include "Action.h"
#include "VValueSet.h"
#include <string>

#define MENUSIZE_MAX 4

using namespace std;

class ActionMenuMediator
{
	friend class ActionMenuMediatorTest;
public:

	enum ActionValue
	{
		ACTION_MENU
	};

	static void create();
	static void destroy();
	static ActionMenuMediator* instance();

	void addRefObject( Action* );
	bool setInput( int );
	Action::Choice getInput() const;
	VValueSet getValue( ActionValue );
	string getSelectMenu() const;

private:
	ActionMenuMediator(void);
	~ActionMenuMediator(void);
	ActionMenuMediator( const ActionMenuMediator& );
	void operator =( const ActionMenuMediator& );

	void updateMenu();
	string getMenu( int ) const;

	static ActionMenuMediator* mInstance;
	Action* mAction;
	int mInput;
	int mMenuSize;
	Action::Choice mChoices[MENUSIZE_MAX];
};
