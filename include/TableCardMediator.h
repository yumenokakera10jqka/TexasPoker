#pragma once
#include "VValueSet.h"

class TableCard;

class TableCardMediator
{
	friend class TableCardMediatorTest;
public:

	enum TableCardValue
	{
		TABLECARD_CARD
	};

	static void create();
	static void destroy();
	static TableCardMediator* instance();

	void addRefObject( TableCard* );
	VValueSet getValue( TableCardValue ) const;

private:
	TableCardMediator(void);
	~TableCardMediator(void);
	TableCardMediator( const TableCardMediator& );
	void operator =( const TableCardMediator& );

	static TableCardMediator* mInstance;
	TableCard* mTableCard;
};
