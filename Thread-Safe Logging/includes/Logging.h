#include <mutex>
#include <future>
#include <queue>
#include <string>

#include "Timer.h"
#include "Stream.h"
#include "Info.h"


class Logging
{
public:
	Logging();
	~Logging();

	void addQue(Info *,std::string);

	bool logOne();
	bool logAll();
	

private:
	std::mutex m_mutex;
	std::queue<std::pair<Info *,std::string>> m_que;
	Timer<std::chrono::milliseconds> *m_timer;
	Stream *m_stream;
	bool done;
};