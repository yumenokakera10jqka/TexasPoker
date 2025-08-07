#pragma once
#include "VValueSet.h"

class MatchCondition;

class MatchConditionMediator
{
	friend class MatchConditionMediatorTest;
public:

	enum MatchConditionValue
	{
		MATCH_PLAYERNAME,
		MATCH_RANK,
		MATCH_CHIPAMOUNT,
		MATCH_GAMENUM
	};

	static void create();
	static void destroy();
	static MatchConditionMediator* instance();

	void addRefObject( MatchCondition* );
	VValueSet getValue( MatchConditionValue ) const;

private:
	MatchConditionMediator(void);
	~MatchConditionMediator(void);
	MatchConditionMediator( const MatchConditionMediator& );
	void operator =( const MatchConditionMediator& );

	static MatchConditionMediator* mInstance;
	MatchCondition* mMatchCondition;
};
