#include "stdafx.h"
#include "File.h"
#include "MyMacro.h"
#include <fstream>

using namespace std;

File::File( const char* fileName ):
mName( fileName ), mFileData( 0 ), mSize( 0 )
{
}

File::~File()
{
	SAFE_DELETE_ARRAY( mFileData );
}

int File::getSize() const
{
	return mSize;
}

void File::setSize( int size )
{
	mSize = size;
}

const char* File::getFileData() const
{
	return mFileData;
}

void File::setFileData( char* data )
{
	mFileData = data;
}

bool File::isReady() const
{
	return (mFileData != 0);
}
