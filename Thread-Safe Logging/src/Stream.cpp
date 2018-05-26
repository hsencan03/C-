#include "Stream.h"


Stream::Stream()
{
}


Stream::~Stream()
{
}

bool Stream::write(std::string fileName, Info *inf)
{
	std::ifstream iFile(fileName);

	if (iFile.is_open() == false) 
	{
		std::ofstream oFile(fileName);

		if (oFile.is_open()) {
			oFile << (*inf);

			oFile.close();
			return true;
		}
		return false;
	}
	iFile.close();

	std::fstream File(fileName, std::ios::app);
	
	if (File.is_open()) {
		File << (*inf);
		return true;
	}
	return false;
}