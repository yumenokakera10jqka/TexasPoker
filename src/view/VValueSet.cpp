#include "VValueSet.h"
#include <cassert>

using namespace std;

VValueSet::VValueSet(void)
{
}

VValueSet::~VValueSet(void)
{
}

void VValueSet::addVValue( VValue at )
{
	mVValues.push_back( at );
}

const VValue& VValueSet::getVValue() const
{
	assert( mVValues.size() > 0 );
	return mVValues[0];
}

const VValue& VValueSet::getVValue( int idx ) const
{
	assert( mVValues.size() > (unsigned)idx );
	return mVValues[idx];
}

int VValueSet::getSize() const
{
	return mVValues.size();
}
