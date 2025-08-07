#include "stdafx.h"
#include "Loader.h"
#include "File.h"
#include "MyMacro.h"
#include <fstream>

using namespace std;

Loader* Loader::mInstance = 0;

Loader::Loader(void)
{
}

Loader::~Loader(void)
{
}

Loader* Loader::instance()
{
	return mInstance;
}

void Loader::create()
{
	if( mInstance != 0 )
	{
		return;
	}
	mInstance = new Loader();
}

void Loader::destroy()
{
	if( mInstance == 0)
	{
		return;
	}
	SAFE_DELETE( mInstance );
}

void Loader::createFile( File** file, const char* fileName )
{
	if( file == 0 )
	{
		return;
	}

	typedef list<File*>::iterator It;

	for( It i = mFiles.begin(); i != mFiles.end(); i++ )
	{
		if( (*i)->mName == fileName )
		{
			return;
		}
	}
	
	*file = new File( fileName );
	mFiles.push_back( *file );
}

void Loader::destroyFile( File** file )
{
	if( file == 0 )
	{
		return;
	}

	typedef list<File*>::iterator It;

	for( It i = mFiles.begin(); i != mFiles.end(); i++ )
	{
		if( (*i)->mName == (*file)->mName )
		{
			SAFE_DELETE( (*i) );
			mFiles.erase( i );
			*file = 0;
			return;
		}
	}
}

void Loader::update()
{
	typedef list<File*>::iterator It;

	for( It i = mFiles.begin(); i != mFiles.end(); i++ )
	{
		if( (*i)->isReady() == false )
		{
			ifstream inputFile( (*i)->mName.c_str(), ifstream::binary );
			inputFile.seekg( 0, ifstream::end );
			int size = inputFile.tellg();
			inputFile.seekg( 0, ifstream::beg );
			char* data = new char[size];
			inputFile.read( data, size );
			(*i)->mSize = size;
			(*i)->mFileData = data;
		}
	}
}