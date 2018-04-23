//harita ve oyun
#ifndef CHESS_HPP
#define CHESS_HPP
#include <string>
#include "LinkedList.hpp"
#include "Exception.hpp"
#define N 8

class Piece;
std::string map[N][N];
LinkedList<Piece*>pieces;


//TAÞLAR
typedef std::pair<int,int> Point;
enum EMove{Left=0,Right,Down,Up,TLCorner,TRCorner,LLCorner,LRCorner};
enum Horse{LeftTop=0,RightTop,Right1,Right2,Left1,Left2,LowerLeft,LowerRight};

//base class
class Piece{
public:
	virtual void move();
	virtual void eat();
	virtual Point getPoint();
	virtual bool getColor();
	virtual std::string getName();
};
Piece *getPiece(Point p){
	if(map[p.first][p.second]==" ")
		return nullptr;
	
	for(int i=0;i<pieces.size();i++){
		if(pieces.at(i)->data->getPoint().first==p.first && pieces.at(i)->data->getPoint().second==p.second)
			return pieces.at(i)->data;
	}
	return nullptr;
}
bool check(Point p,EMove e,int count){
	switch(e){
		case Up:
			for(int i=1;i<=count;i++)
				if(map[p.first-i][p.second]!=" ")
					return false;
			return true;
		case Down:
			for(int i=1;i<=count;i++)
				if(map[p.first+i][p.second]!=" ")
					return false;
				return true;
		case Left:
			for(int i=1;i<=count;i++)
				if(map[p.first][p.second-i]!=" ")
					return false;
				return true;
		case Right:
			for(int i=1;i<=count;i++)
				if(map[p.first][p.second+i]!=" ")
					return false;
				return true;
		case TLCorner:
			for(int i=1;i<=count;i++)
				if(map[p.first-i][p.second-i]!=" ")
					return false;
				return true;
		case TRCorner:
			for(int i=1;i<=count;i++)
				if(map[p.first-i][p.second+i]!=" ")
					return false;
				return true;
		case LLCorner:
			for(int i=1;i<=count;i++)
				if(map[p.first+i][p.second-i]!=" ")
					return false;
				return true;
		case LRCorner:
			for(int i=1;i<=count;i++)
				if(map[p.first+i][p.second+i]!=" ")
					return false;
				return true;
	}	
}
bool check(Point p,Horse h){
	switch(h){
		case LeftTop:
			if(map[p.first-2][p.second-1]==" ")
				return true;
			return false;
		case RightTop:
			if(map[p.first-2][p.second+1]==" ")
				return true;
			return false;
		case Left1:
			if(map[p.first-1][p.second-2]==" ")
				return true;
			return false;
		case Right1:
			if(map[p.first-1][p.second+2]==" ")
				return true;
			return false;
		case Left2:
			if(map[p.first+1][p.second-2]==" ")
				return true;
			return false;
		case Right2:
			if(map[p.first+1][p.second+2]==" ")
				return true;
			return false;	
		case LowerLeft:
			if(map[p.first+2][p.second-1]==" ")
				return true;
			return false;
		case LowerRight:
			if(map[p.first+2][p.second+1]==" ")
				return true;
			return false;		
	}
}
EMove getRotate(Point p,Point ep){		
	if(p.second=ep.second)
		return (p.first>ep.first ? Up : Down);
	else if(p.first==ep.first)
		return (p.second>ep.second ? Left : Right);
	else if(p.first>ep.first && p.second>ep.second)
		return TLCorner;
	else if(p.first>ep.first && p.second<ep.second)
		return TRCorner;
	else if(p.first<ep.first && p.second<ep.second)
		return LRCorner;
	else if(p.first<ep.first && p.second<ep.second)
		return LRCorner;
}
int getFar(Point p,Point ep,EMove e){
	switch(e){
		case Up:
			return ep.first-p.first;
		case Down:
			return p.first-ep.first;
		case Left:
			return p.second-ep.second;
		case Right:
			return ep.second-p.second;
		case TLCorner:
			return p.first-ep.first;
		case TRCorner:
			return p.first-ep.first;
		case LRCorner:
			return ep.first-p.first;
		case LLCorner:
			return ep.first-p.first;
	}
}


class King:public Piece{
public:
	King(int x,int y,bool color,std::string name){
		p.first=x;
		p.second=y;
		this->color=color;
		this->name=name;
	}
	void move(EMove e){
		switch(e){
			case Left:
				this->p.second--;
				break;
			case Right:
				this->p.second++;
				break;
			case Down:
				this->p.first++;
				break;
			case Up:
				this->p.first--;
				break;
			case TLCorner:
				this->p.first--;
				this->p.second--;
				break;
			case TRCorner:
				this->p.first--;
				this->p.second++;
				break;
			case LLCorner:
				this->p.first++;
				this->p.second--;
				break;
			case LRCorner:
				this->p.first++;
				this->p.second++;
			default:
				throw new MoveException("Hatali Yon Giridli");
		}
	}
	void eat(Point p){
		if((this->p.first-p.first==1 || this->p.first-p.first==-1) && (this->p.second-p.second==1 || this->p.second-p.second==-1) && getPiece(p)->getColor()!=this->color){
			this->p.first=p.first;
			this->p.second=p.second;
			pieces.remove(getPiece(p));
		}
	}
	Point getPoint()const{return this->p;}
	bool getColor()const{return this->color;}
	std::string getName(){return this->name;}
private:
	Point p;
	bool color;
	std::string name;
};

class Pawn:public Piece{
public:
	Pawn(int x,int y,bool color,std::string name){
		p.first=x;
		p.second=y;
		this->color=color;
		this->name=name;
	}
	void move(EMove e,bool isFirst){
		if(e!=Up)
			throw new MoveException("Piyon Sadece Ileri Haraket Eder");
		else if(isFirst && e==Up)
			this->p.first-=2;
		else
			this->p.first--;
	}
	void eat(Point p){
		if(this->p.first-p.first==1 && (this->p.second-p.second==-1 || this->p.second-p.second==1) && getPiece(p)->getColor()!=this->color){
			this->p.first=p.first;
			this->p.second=p.second;
			pieces.remove(getPiece(p));
		}
	}
	Point getPoint()const{return this->p;}
	bool getColor()const{return this->color;}
	std::string getName(){return this->name;}
private:
	Point p;
	bool color;
	std::string name;
};

class Queen:public Piece{
public:
	Queen(int x,int y,bool color,std::string name){
		p.first=x;
		p.second=y;
		this->color=color;
		this->name=name;
	}
	void move(EMove e,int count){
		switch(e){
			case Up:
				if(check(this->p,e,count))
					this->p.first-count;
				else
					throw new MoveException("Vezirin Onu Acik Degil");
			case Down:
				if(check(this->p,e,count)){
					this->p.first+count;
					break;
				}
				else
					throw new MoveException("Vezirin Onu Acik Degil");
			case Left:
				if(check(this->p,e,count)){
					this->p.second-count;
					break;
				}
				else
					throw new MoveException("Vezirin Onu Acik Degil");
			case Right:
				if(check(this->p,e,count)){
					this->p.second+count;
					break;
				}
				else
					throw new MoveException("Vezirin Onu Acik Degil");
			case TLCorner:
				if(check(this->p,e,count)){
					this->p.first-count;
					this->p.second-count;
					break;
				}
				else
					throw new MoveException("Vezirin Onu Acik Degil");
			case TRCorner:
				if(check(this->p,e,count)){
					this->p.first-count;
					this->p.second+count;
					break;
				}
				else
					throw new MoveException("Vezirin Onu Acik Degil");
			case LLCorner:
				if(check(this->p,e,count)){
					this->p.first+count;
					this->p.second-count;
					break;
				}
				else
					throw new MoveException("Vezirin Onu Acik Degil");		
			case LRCorner:
				if(check(this->p,e,count)){
					this->p.first+count;
					this->p.second+count;
					
				}	
		}
	}
	void eat(Point p){
		if(getPiece(p)->getColor()!=this->color){
			if(check(p,getRotate(this->p,p),getFar(this->p,p,getRotate(this->p,p)))){
				this->p.first=p.first;
				this->p.second=p.second;
				pieces.remove(getPiece(p));
			}
		}
	}
	Point getPoint()const{return this->p;}
	bool getColor()const{return this->color;}
	std::string getName(){return this->name;}
private:
	Point p;
	bool color;
	std::string name;
};

class Rook:public Piece{
public:
	Rook(int x,int y,bool color,std::string name){
		p.first=x;
		p.second=y;
		this->color=color;
		this->name=name;
	}
	void move(EMove e,int count){
		switch(e){
			case Up:
				if(check(this->p,e,count))
					this->p.first-count;
				else
					throw new MoveException("Kalenin Onu Acik Degil");
			case Down:
				if(check(this->p,e,count)){
					this->p.first+count;
					break;
				}
				else
					throw new MoveException("Kalenin Onu Acik Degil");
			case Left:
				if(check(this->p,e,count)){
					this->p.second-count;
					break;
				}
				else
					throw new MoveException("Kalenin Onu Acik Degil");
			case Right:
				if(check(this->p,e,count)){
					this->p.second+count;
					break;
				}
				else
					throw new MoveException("Kalenin Onu Acik Degil");			
		}
	}
	void eat(Point p){
		if(getPiece(p)->getColor()!=this->color)
			if(check(p,getRotate(this->p,p),getFar(p,p,getRotate(this->p,p)))){
				this->p.first=p.first;
				this->p.second=p.second;
				pieces.remove(getPiece(p));				
			}
		}
	Point getPoint()const{return this->p;}
	bool getColor()const{return this->color;}
	std::string getName(){return this->name;}
private:
	Point p;
	bool color;
	std::string name;
};

class Bishop:public Piece{//nami deger fil
public:
	Bishop(int x,int y,bool color,std::string name){
		p.first=x;
		p.second=y;
		this->color=color;
		this->name=name;
	}
	void move(EMove e,int count){
		switch(e){
			case TLCorner:
				if(check(this->p,e,count)){
					this->p.first-count;
					this->p.second-count;
					break;
				}
				else
					throw new MoveException("Filin Onu Acik Degil");
			case TRCorner:
				if(check(this->p,e,count)){
					this->p.first-count;
					this->p.second+count;
					break;
				}
				else
					throw new MoveException("Kalenin Onu Acik Degil");
			case LLCorner:
				if(check(this->p,e,count)){
					this->p.first+count;
					this->p.second-count;
					break;
				}
				else
					throw new MoveException("Kalenin Onu Acik Degil");		
			case LRCorner:
				if(check(this->p,e,count)){
					this->p.first+count;
					this->p.second+count;
					
				}
		}
		
	}
	void eat(Point p){
		if(getPiece(p)->getColor()!=this->color)
			if(check(p,getRotate(this->p,p),getFar(p,p,getRotate(this->p,p)))){
				this->p.first=p.first;
				this->p.second=p.second;
				pieces.remove(getPiece(p));				
			}
	}
	Point getPoint()const{return this->p;}
	bool getColor()const{return this->color;}
	std::string getName(){return this->name;}
private:
	Point p;
	bool color;
	std::string name;
};

class Knight:public Piece{
public:
	Knight(int x,int y,bool color,std::string name){
		p.first=x;
		p.second=y;
		this->color=color;
		this->name=name;
	}
	void move(Horse h){
		switch(h){
			case LeftTop:
				if(check(this->p,h)){
					this->p.first-2;
					this->p.second-1;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");
			case RightTop:
				if(check(this->p,h)){
					this->p.first-2;
					this->p.second+1;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");
			case Left1:
				if(check(this->p,h)){
					this->p.first-1;
					this->p.second-2;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");
			case Right1:
				if(check(this->p,h)){
					this->p.first-1;
					this->p.second+2;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");
			case Left2:
				if(check(this->p,h)){
					this->p.first+1;
					this->p.second-2;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");
			case Right2:
				if(check(this->p,h)){
					this->p.first+1;
					this->p.second+2;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");
			case LowerLeft:
				if(check(this->p,h)){
					this->p.first+2;
					this->p.second-1;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");
			case LowerRight:
				if(check(this->p,h)){
					this->p.first+2;
					this->p.second+1;
					break;
				}
				else
					throw new OutOFBound("Atin Yonu Hatali");									
		}
	}
	void eat(Point p){
		if(getPiece(p)->getColor()!=this->color){
			this->p.first=p.first;
			this->p.second=p.second;
			pieces.remove(getPiece(p));
		}
	}
	Point getPoint()const{return this->p;}
	bool getColor()const{return this->color;}	
	std::string getName(){return this->name;}
private:
	Point p;
	bool color;
	std::string name;
};
//TAÞLAR BÝTÝÞ
class Chees{
public:
	Chess(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)
				map[i][j]=" ";
		}
		for(int i=0;i<32;i++){
			if(i<16)
				pieces.add(new Pawn(0,0,(i<8 ? true : false),"Pawn"));					//TAÞLARI DÝZÝLÝÞ SIRASINA GÖRE AYARLA
			else if(i<18)
				pieces.add(new King(0,0,(i<17 ? true : false),"King"));
			else if(i<20)
				pieces.add(new Queen(0,0,(i<19 ? true : false),"Queen"));
			else if(i<24)
				pieces.add(new Rook(0,0,(i<22 ? true : false),"Rook"));
			else if(i<28)
				pieces.add(new Bishop(0,0,(i<24 ? true : false),"Bishop"));
			else
				pieces.add(new Knight(0,0,(i<30 ? true : false),"Knight"));				
		}
	}
	void fillBoard(){
		int count=0;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(i==0){
					switch(j){
						case 0:
							if(pieces.at(count)->data->getName()=="Rock" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WR ";
								count++;
							}
							break;
						case 1:
							if(pieces.at(count)->data->getName()=="Knight" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WK";
								count++;
							}
							break;
						case 2:
							if(pieces.at(count)->data->getName()=="Bishop" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WB";
								count++;
							}
							break;							
						case 3:
							if(pieces.at(count)->data->getName()=="Queen" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WQ";
								count++;
							}
							break;	
						case 4:
							if(pieces.at(count)->data->getName()=="King" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WK";
								count++;
							}
							break;	
						case 5:
							if(pieces.at(count)->data->getName()=="Bishop" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WB";
								count++;
							}
							break;	
						case 6:
							if(pieces.at(count)->data->getName()=="Knight" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WK";
								count++;
							}
							break;	
						case 7:
							if(pieces.at(count)->data->getName()=="Rook" && pieces.at(count)->data->getColor()==true){
								map[i][j]="WR ";
								count++;
							}
							break;																
					}
				}
			}
		}
	}
	void printMap(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				std::cout<<map[i][j];
				
			}
			std::cout<<std::endl;
		}
	}
private:
	std::string gameMap[N][N];	
};
#endif
