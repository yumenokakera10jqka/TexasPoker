#ifndef INCLUDE_TAG_H
#define INCLUDE_TAG_H
#include <string>

class Attribute;

class Tag
{
public:
	enum Type
	{
		START_TAG,
		END_TAG,
		NONE,
	};

	enum Sequence
	{
		SEQ_0,
		SEQ_1,
		SEQ_2,
		SEQ_3,
		SEQ_4,
		SEQ_5,
		SEQ_6,
		SEQ_7,
	};

	Tag();
	Tag( const char** );
	~Tag();

	bool isStartTag() const;
	std::string getName() const;
	Attribute* getAttributes() const;
	int getAttributeSize() const;

private:
	Type mType;
	std::string mName;
	Attribute* mAttributes;
	int mAttributeSize;

	bool isGeneralChar( char ) const;
	void addAttribute( Attribute* );
};

#endif