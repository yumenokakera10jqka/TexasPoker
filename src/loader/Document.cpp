#include "MyMacro.h"
#include "Document.h"
#include "Element.h"
#include "Tag.h"

Document::Document( const char* data )
{
	Tag tag;
	mRoot = new Element( tag, &data );
}

Document::~Document()
{
	SAFE_DELETE( mRoot );
}

const Element* Document::getRoot() const
{
	return mRoot;
}
