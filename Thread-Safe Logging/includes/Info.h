#include <exception>
#include <string>

#include "Timer.h"

class Info
{
public:
	Info(std::exception *ex,std::string explanation)
	{
		this->exp = ex;
		this->explanation = explanation;

		currTime = Timer<>::now();
	}

	~Info() 
	{
		delete exp;
	}

	friend std::ostream& operator<<(std::ostream &os,const Info &inf)
	{
		os <<"Exception:"<<std::setw(5) << inf.exp->what() <<"\t"<<"Explanation:"<<std::setw(10) << inf.explanation <<"\t"<<"Date:"<<std::setw(10)<<inf.currTime << std::endl;
		return os;
	}

private:
	std::exception *exp;
	std::string currTime;
	std::string explanation;
};

