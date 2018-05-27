#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <atomic>
#include <fstream>
#include <string>
#include <vector>

struct Info 
{
	Info(int id,std::string txt):text(txt),ID(id){}
	
	std::string text;
	int ID;

	friend std::ostream& operator<<(std::ostream &os, const Info &inf)
	{
		os << inf.ID << "\t" << inf.text << std::endl;
		return os;
	}
};

class FileWriter {
public:
	
	FileWriter(int threadNum):size(threadNum) {
		tVec.resize(threadNum);
		finished = false;
		file.open("hello.txt", std::ios::app);
		
		for (int i = 0; i < size; i++) {
			tVec[i] = std::thread(&FileWriter::run, this);
			tVec[i].detach();
		}
	}
	~FileWriter(){
		finished = true;
		file.close();
	}
	
	void add(Info *inf)
	{
		iQue.push(std::move(inf));
	}

	void write_one() {
		m_cv.notify_one();
	}
	void writeAll() {
		while (!iQue.empty())
			m_cv.notify_all();
	}
private:
	void run() {
		while (!finished)
		{
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_cv.wait(lock, [&]() {return !iQue.empty(); });
				
				Info *temp = iQue.front();
				file << (*temp);
				iQue.pop();
				delete temp;
				std::cout << "DONE\n";
			}
		}
	}
private:
	std::queue<Info*> iQue;
	std::vector<std::thread>tVec;
	int size;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::atomic<bool> finished;

	std::fstream file;
};


auto main()->int {

	FileWriter writter(3);

	writter.add(new Info(15, "Her"));
	writter.add(new Info(25, "Zaman"));
	writter.add(new Info(35, "Her"));
	writter.add(new Info(45, "Yerde"));
	writter.add(new Info(55, "En"));
	writter.add(new Info(65, "Buyuk"));
	writter.add(new Info(75, "Fener"));


	writter.writeAll();
	
	std::cin.get();
	return 0;
}