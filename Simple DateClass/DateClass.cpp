#include <iostream>
#include <string>
#include <sstream>
#include <ctime>//can be used chrono


class DateTime
{
public:
	static std::string GetDateTimeString(const std::string &sep = ".")
	{
		time_t ms;
		time(&ms);

		struct tm *info = localtime(&ms);

		return 
			   //Time
			   std::string(info->tm_hour<10  ? "0" : "")+ToString(info->tm_hour)+sep+
			   std::string(info->tm_min <10  ? "0" : "")+ToString(info->tm_min)+sep+
			   std::string(info->tm_sec <10  ? "0" : "")+ToString(info->tm_sec)+"  "+
			   //Date
			   std::string(info->tm_mday <10 ? "0" : "")+ToString(info->tm_mday)+sep+
			   std::string(info->tm_mon+1<10 ? "0" : "")+ToString(info->tm_mon+1)+sep+
			   ToString(1900+info->tm_year);
	}
private:
	template<typename T>
	static std::string ToString(const T& value)
	{
		std::stringstream os;
		os << value;
		return os.str();
	}
};

//TEST
int main(){

	std::cout << DateTime::GetDateTimeString(":");


	getchar();
	return 0;
}