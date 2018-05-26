#include <fstream>
#include <iomanip>
#include <string>

#include "Info.h"

class Stream
{
public:
	Stream();
	~Stream();

	static bool write(std::string fileName, Info *inf);
};

