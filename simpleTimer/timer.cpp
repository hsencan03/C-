#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

//#include <ctime>

template<class Resulution=std::chrono::milliseconds>
class ExecutionTimer
{
public:
	using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock,
		std::chrono::steady_clock>;

	ExecutionTimer() = default;

	~ExecutionTimer() 
	{
		std::cout << "Elapsed: "
			<< (std::chrono::duration_cast<Resulution>((Clock::now() - mStart)).count()) << std::endl;
	}
private:
	Clock::time_point mStart = Clock::now();
};

int main() {
	//ctime
	//const auto start = time(nullptr);
	//std::cout << "Elapsed time: " << (time(nullptr) - start) << "s" << std::endl;
	{
		ExecutionTimer<> timer1;
		ExecutionTimer<std::chrono::seconds> timer2;
		//example
		std::vector<int> v(50000000);
		std::sort(std::begin(v), std::end(v));
	}

	std::cin.get();
	return 1;
}