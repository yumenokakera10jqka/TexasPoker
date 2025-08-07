#ifndef INCLUDE_FILE_H
#define INCLUDE_FILE_H
#include <string>

class File
{
public:
	File( const char* );
	~File();

	int getSize() const;
	void setSize( int );
	const char* getFileData() const;
	void setFileData( char* );
	bool isReady() const;

private:
	friend class FileOut;
	friend class Loader;
	char* mFileData;
	int mSize;
	std::string mName;

};

#endif