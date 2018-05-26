#include <iostream>
#include "Logging.h"

int main() {

	Logging lg;

	lg.addQue(new Info(new std::runtime_error("RunTimeError"), "Error in main function in line 10"), "Hello.txt");

	std::cout << lg.logOne();


	std::cin.get();
	return 0;
}