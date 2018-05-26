#pragma warning(disable : 4996) //for vsc++
#include <chrono>
#include <ctime>


template<class Resulution=std::chrono::milliseconds>
class Timer
{
public:
	Timer() = default;
	
	void start() 
	{
		m_start = Clock::now();
	}
	double end() 
	{
		return  (std::chrono::duration_cast<Resulution>((Clock::now() - mStart)).count());
	}
	static std::string now()
	{
		std::time_t tt = std::time(NULL);
		std::string s = std::ctime(&tt);
		return s.substr(0, s.size() - 1);
	}

private:
	using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock,
		std::chrono::steady_clock>;

	Clock::time_point m_start;
};
