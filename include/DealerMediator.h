#pragma once
#include "VValueSet.h"

class Dealer;

class DealerMediator
{
	friend class DealerMediatorTest;
public:

	enum DealerValue
	{
		DEALER_ROUND,
		DEALER_POT,
		DEALER_GAME
	};

	static void create();
	static void destroy();
	static DealerMediator* instance();

	void addRefObject( Dealer* );
	VValueSet getValue( DealerValue ) const;

private:
	DealerMediator(void);
	~DealerMediator(void);
	DealerMediator( const DealerMediator& );
	void operator =( const DealerMediator& );

	static DealerMediator* mInstance;
	Dealer* mDealer;
};
