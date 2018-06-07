#include "Amiral.h"
void Log::Kaydet(string isim,bool kazandimi,int sure){
	fstream dosya;
	dosya.open("Logs.txt",ios::app);
	string sonuc=kazandimi ? "WIN" : "LOSE";
	dosya<<setw(5)<<"Isim---->"<<isim<<setw(10)<<"Sonuc---->"<<sonuc<<setw(10)<<"Saniye---->"<<sure<<endl;
	dosya.close();
}
void Amiral::sifirla(){
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++){
			if(i==0){
				Pmap[i][j]=to_string(j)+"    ";
				Umap[i][j]=to_string(j)+"    ";
				PUser[i][j]=to_string(j)+"    ";
				PC[i][j]=to_string(j)+"    ";
			}
			else if(j==0){
				if(i==9){
					Umap[i][j]=to_string(i)+"  ";
					Pmap[i][j]=to_string(i)+"  ";
					PUser[i][j]=to_string(i)+"  ";
					PC[i][j]=to_string(i)+"  ";
				}
				else{
					Umap[i][j]=to_string(i)+"  ";
					Pmap[i][j]=to_string(i)+"  ";
					PUser[i][j]=to_string(i)+"  ";
					PC[i][j]=to_string(i)+"  ";
				}
			}
			else{
				Umap[i][j]="  *  ";
				Pmap[i][j]="  *  ";
				PUser[i][j]="  *  ";
				PC[i][j]="  *  ";				
			}
		}	
}
void Amiral::ShowMap(bool x){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
		if(x)
			cout<<Umap[i][j];
		else
			cout<<Pmap[i][j];
		}
		cout<<endl<<endl;
	}
}
void Amiral::UserShips(){
	int sayac=0;
	string temp[]={"1-UcakGemisi   ","2-Kruvazor   ","3-Denizalti   ","4-Firkateyn    ","5-Mayin Gemisi"};
	while(true){
		system("cls");
		ShowMap(true);
		if(++sayac==6)
			break;
		cout<<"\n-----------------------------------------------------\nGemilerinizi Yerlestirmek Istediginiz" 
		"Kordinatlari Veriniz\n\n"+temp[0]+temp[1]+temp[2]+temp[3]+temp[4]<<endl;
		int s,x,y;
		char c;
		cout<<"Gemi Secimi	:";
		cin>>s;
		temp[s-1]="";
		cout<<"Kordinatlar	:";
		cin>>x>>y;
		cout<<"Yon	(W/A/S/D):";
		c=getch();
		GemiYerlestir(s,x,y,c);
	}
}
void Amiral::GemiYerlestir(int ship,int x,int y,char yon){
		if(yon=='a'){
			for(int i=y,j=0;j<ships[ship-1].length();i--,j++)
				Umap[x][i]="  0  ";	
			}
		else if(yon=='d'){
			for(int i=y,j=0;j<ships[ship-1].length();j++,i++)
				Umap[x][i]="  0  ";
			}
		else if(yon=='w'){
			for(int i=x,j=0;j<ships[ship-1].length();j++,i--)
				Umap[i][y]="  0  ";
		}
		else if(yon=='s'){
			for(int i=x,j=0;i<ships[ship-1].length();j++,i++)
				Umap[i][y]="  0  ";	
	}
}
void Amiral::PGemi(int x){
	srand(time(0));
	bool flag=false;
	int count=0;
	while(count==0){
		int r=rand()%10;
		int r1=rand()%10;
		int r2=rand()%2;
		if(r2==0){	
			for(int i=0;i<ships[x].length();i++){		
				if(Pmap[r][r1+i]=="  *  ")
					 flag=true;
				else{
					flag=false;
					break;
				}
			}
			if(flag){
				for(int i=0;i<ships[x].length();i++){
					Pmap[r][r1+i]="  0  ";
				}
				count++;
			}
		}
		else if(r2==1){
			for(int i=0;i<ships[x].length();i++){
				if(Pmap[r+i][r1]=="  *  ")
					flag=true;
				else{
					flag=false;
					break;
				}
			}
			if(flag){
				for(int i=0;i<ships[x].length();i++)
					Pmap[r+i][r1]="  0  ";
				count++;
			}
		}
	}
}
int Amiral::kazandimi(){
	int Psayac=0,Usayac=0;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++){
			if(PC[i][j]=="  0  "){
				Psayac++;
			if(PUser[i][j]=="  0  ")
				Usayac++;
			if(Usayac==17 || Psayac==17){
				if(Usayac==17)
					return 1;
				return 2;
			}
		}
	}
	return 0;
}
void Amiral::EkranaBas(){
	system("cls");
	cout<<endl<<"\t\t\tYOU"<<"\t\t\t\t\t\t\t"<<"COMPUTER"<<endl<<endl;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			cout<<PUser[i][j];
		}
		cout<<"\t";
		for(int j=0;j<10;j++){
			cout<<PC[i][j];
		}
		cout<<endl;
	}
}
void Amiral::Oyun(){
	int k1,k2;
	cout<<"Oyun Basiyor Lutfen Bekleyininiz";
	for(int i=0;i<5;i++){
		cout<<".";
		Sleep(150);
	}
	clock_t time;
	time=clock();
	int past=0,past1=0,count=-1,r,r1,sira=1,first=0,first1=0;
	while(true){
		if(sira==1){
			EkranaBas();
			cout<<"Kordinatlari Giriniz: ";
			cin>>k1>>k2;
			if(PC[k1][k2]=="  X  " || PC[k1][k2]=="  0  ")
				cout<<"Daha Once Bu Kordinatlari Girdiniz\n";
			else if(Pmap[k1][k2]=="  *  " || Pmap[k1][k2]=="  0  "){
				if(Pmap[k1][k2]=="  0  "){
					cout<<"BOOOOM!!!";
					PC[k1][k2]="  0  ";
				}
				else{
					cout<<"Iskaladin\n";
					PC[k1][k2]="  X  ";
					sira=2;
				}
			}
			else{
			cout<<"Hatali Giris"<<endl;
			Sleep(1000);
			}
		}
		else if(sira==2){
			cout<<"\nBilgisayar Atis Yapiyor";
			Sleep(1000);
			while(true){
				if(past!=0 || past1!=0){
					if(count==0){
						r=past++;
						r1=past1;	
					}
					else if(count==1){
						r=past--;
						r1=past1;
					}
					else if(count==2){
						r=past;
						r1=past1++;
					}
					else if(count==3){
						r=past;
						r1=past1--;
					}
				}
				else{
					r=rand()%10;
					r1=rand()%10;
				}
				if(Umap[r][r1]=="  *  " || Umap[r][r1]=="  0  " && PUser[r][r1]=="  *  "){
					if(Umap[r][r1]=="  0  "){
						cout<<"   BOOOOM!!!";
						PUser[r][r1]="  0  ";
						past=r;
						past1=r1;
						if(count==-1){
							count=0;
							first=r;
							first1=r1;
						}
						break;
					}
					else{
						cout<<"   Iskaladi\n";
						PUser[r][r1]="  X  ";
						if(count==0){
							count=1;
							past=first;
							past1=first1;
						}
						else if(count==1){
							count=2;
							past=first;
							past1=first1;
						}
						else if(count==2){
							count=3;
							past=first;
							past1=first1;							
						}
						else if(count==3){
							count=4;
							past=first;
							past1=first1;									
						}
						else if(count==4){
							count=-1;
							past=past1=0;
						}
						sira=1;
						break;
					}
				}
			}
		}
		if(kazandimi()!=0){
			if(kazandimi()==2){
				cout<<"KAZANDINIZ TEBRIKLER\n";
				string isim;
				cout<<"Isminizi Giriniz	:";
				cin>>isim;
				Log::Kaydet(isim,true,(clock()-time)/CLOCKS_PER_SEC);
				exit(1);
			}
			else{
				cout<<"KAYBETTINIZ\n";
				string isim;
				cout<<"Isminizi Giriniz	:";
				cin>>isim;
				Log::Kaydet(isim,true,(clock()-time)/CLOCKS_PER_SEC);
				exit(0);
			}
		}
		Sleep(500);
	}	
}
void Amiral::Menu(){
	cout<<"Amiral Batti Oyununa Hosgelziniz\nGemi Yerlestirmeye Baslamak Icin Bir Tusa Basiniz"<<endl;
	while(!kbhit());
	UserShips();
	cout<<endl<<"Bilgisayarin Gemileri Yerlestiriliyor Lutfen Bekleyiniz";
	for(int i=0;i<5;i++){
		cout<<".";
		Sleep(200);
	}
	cout<<endl;	
	for(int i=1;i<6;i++)
		PGemi(i);
	Oyun();
}
