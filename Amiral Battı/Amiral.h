#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;
class Log{
protected:
	static void Kaydet(string,bool,int);
};
class Ship:public Log{
protected:
	string ships[5]={"00000","0000","000","000","00"};
};
class Amiral:public Ship{
	string Pmap[10][10],Umap[10][10],PUser[10][10],PC[10][10];
public:	
	Amiral(){sifirla();}
	int kazandimi();
	void GemiYerlestir(int,int,int,char);
	void ShowMap(bool);
	void Menu();
	void sifirla();
	void UserShips();
	void PGemi(int ship);
	void EkranaBas();
	void Oyun();
};

