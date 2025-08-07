#ifndef INCLUDE_LOADER_H
#define INCLUDE_LOADER_H
#include <list>

class File;

class Loader
{
public:
	static Loader* instance();
	static void create();
	static void destroy();
	void createFile( File**, const char* );
	void destroyFile( File** );
	void update();

private:
	Loader(void);
	~Loader(void);
	Loader( Loader& );

	static Loader* mInstance;
	std::list<File*> mFiles;
};

#endif