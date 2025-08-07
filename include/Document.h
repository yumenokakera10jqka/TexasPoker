#ifndef INCLUDE_DOCUMENT_H
#define INCLUDE_DOCUMENT_H

class Element;

class Document
{
public:
	Document( const char* );
	~Document();

	const Element* getRoot() const;

private:
	Element* mRoot;
};

#endif