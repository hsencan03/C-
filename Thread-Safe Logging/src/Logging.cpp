#include "Logging.h"


Logging::Logging()
{
	m_timer = new Timer<std::chrono::milliseconds>();
	m_stream = new Stream();
}

Logging::~Logging()
{
	delete m_timer;
	delete m_stream;
}

void Logging::addQue(Info *inf, std::string fileName) 
{
	m_que.push(std::make_pair(inf, fileName));
}

bool Logging::logOne()
{
	{
		if (m_que.empty())
			return false;
		std::unique_lock<std::mutex>lock(m_mutex);
		if (Stream::write(m_que.front().second, m_que.front().first)) {
			return true;
			delete m_que.front().first;
			m_que.pop();
		}
		return false;
	}
}
bool Logging::logAll() 
{
	std::unique_lock<std::mutex>lock(m_mutex);
	while (!m_que.empty())
	{
		if (Stream::write(m_que.front().second, m_que.front().first))
		{
			delete m_que.front().first;
			m_que.pop();
		}
		return false;
	}
	return true;
}
