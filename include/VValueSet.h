#pragma once
#include "VValue.h"
#include <vector>

using namespace std;

class VValueSet
{
public:
	VValueSet(void);
	~VValueSet(void);

	void addVValue( VValue at );
	const VValue& getVValue() const;
	const VValue& getVValue( int ) const;
	int getSize() const;

private:
	vector<VValue> mVValues;
};
