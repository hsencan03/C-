#include <iostream>
#include <string>
#include <mutex>
#include <functional>
#include <vector>

template<typename returnType, typename ...Args>
class Lazy {
public:
	Lazy(returnType(*func)(Args...)) {
		this->func = func;
	}
	~Lazy() = default;

	void execute(Args...arg) {
		std::call_once(flag,func,std::forward<Args>(arg)...);
	}
private:
	std::function<returnType(Args...)>func;
	std::once_flag flag;
};


void example(int a, std::string b) {

	std::cout << a << " " << b << std::endl;
	std::once_flag flag;
}

int main() {

	Lazy<void, int, std::string>heto(example);

	std::vector<std::thread>tvec;

	heto.execute(15, "hello");

	std::cin.get();
}