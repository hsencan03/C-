#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <condition_variable>
#include <string>
#include <utility>
#include <functional>

//#include <stdexcept>	ilerleyen kısımlarda bakılacak

static std::condition_variable cv;
static std::mutex mtx;
static int count = 0;

template<typename T>
class Serialization;
struct Node;
class MakeThread;


struct Node{
	Node *next;
	int ID;
	std::string name;

	Node():next(nullptr){}

	Node(int id, std::string name) {
		this->ID = id;
		this->name = name;
		next = nullptr;
	}
};
void add(Node *Root, int id, std::string name) {
	if (Root->next == nullptr) {
		Root->next = new Node(id, name);
		return;
	}

	add(Root->next, id, name);
}
int size(const Node *Root) {
	if (Root == nullptr)
		return 0;
	return size(Root->next) + 1;
}
void sort(Node *Root) {
	if (Root == nullptr)
		return;
	Node *iter = Root;
	int length = size(Root);

	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1; j++) {
			if (iter->ID > iter->next->ID) {
				int temp = iter->ID;
				std::string tmp = iter->name;
				iter->ID = iter->next->ID;
				iter->name = iter->next->name;
				iter->next->ID = temp;
				iter->next->name = tmp;
			}
			iter = iter->next;
		}
		iter = Root;
	}
}
void printNode(const Node *Root) {
	if (Root == nullptr)
		return;
	std::cout << Root->ID << " " << Root->name << std::endl;

	printNode(Root->next);
}
template<typename T>
class Serialization {
public:
	static bool serialize(T *object,int ID,std::string Path) {
		std::mutex m_mtx;
		std::unique_lock<std::mutex>sLock(m_mtx);
		std::ofstream File(Path, std::ios::binary);
		if (File.is_open() == false)
			return false;

		File.seekp(sizeof(T)*ID);
		File.write(reinterpret_cast<const char*>(&object), sizeof(T));
		File.close();
		return true;
	}
	static bool deserialize(std::string Path, T *object,int ID) {

		std::ifstream File(Path, std::ios::in | std::ios::binary);
		if (File.is_open() == false)
			return false;

		File.seekg(sizeof(T)*ID);
		File.read(reinterpret_cast<char*>(&object), sizeof(T));
		return true;
	}
};

class MakeThread {
public:
	template<typename T, typename = std::enable_if<std::is_function<T>::value>, typename... arg>
	static void run(T foo, arg&&... args) {
		count++;
		std::function<typename std::result_of<T(arg...)>::type()>task(std::bind(std::forward<T>(foo), std::forward<arg>(args)...));
		std::thread([task]() {
			std::unique_lock<std::mutex>lock(mtx);
			cv.wait(lock);
			task();
		}).detach();
	}
	static void start() {
		cv.notify_one();
		count--;
	}
	static void startAll() {
		cv.notify_all();
		count = 0;
	}
	static int countOfWait() {
		return count;
	}
};
bool serializeAll(Node *root,std::string path) {
	if (root == nullptr)
		return false;
	Node *iter = root;
	using namespace std::placeholders;
	while (iter != nullptr) {
		MakeThread::run(Serialization<Node>::serialize, iter, iter->ID, path);
		iter = iter->next;
	}
	MakeThread::startAll();
	return true;
}

Node *readAll(std::string path,std::pair<int,int> size){
	Node *root = new Node();	
	Node *iter = root;
	
	while (size.first != size.second) {
		Serialization<Node>::deserialize(path, iter, size.first++);
		iter->next = new Node();
		iter = iter->next;
	}
	return root;
}
auto main()->int {


	Node *root = new Node(1, "Huseyin");
	add(root, 2, "Enes");
	add(root, 3, "Evrim");
	add(root, 4, "Erdem");
	add(root, 5, "Baris");

	serializeAll(root,"D:\\Kali\\try.dat");

	//Node *ah = readAll("D:\\Kali\\try.dat",{1,5});

	//Node *temp = nullptr;

	//Serialization<Node>::deserialize("D:\\Kali\\try.dat", temp, 1);

	//printNode(ah);

	/*sort(root);
	printNode(root);*/
	
	std::cin.get();
}