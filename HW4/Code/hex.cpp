#include <iostream>
#include<string>
#include<fstream>
#include "hex.h"
using namespace std;

int Hex::gameNum=0;			//Static data'larımı initialize ettim
bool Hex::end = false;

void Hex::startObject(){
	int i,j;
	hexCells=new Cell*[26];		//burada [26][26]'lık memory allocate ediyorum
	for(i=0;i<26;i++){
		hexCells[i]=new Cell[26];
	}

	for(i=0;i<26;i++){			//Burada da tüm hücrelere '.' atayıp
		for(j=0;j<26;j++){		//path'ımın tüm hücrelerini 0 ile dolduruyorum.
			hexCells[i][j].setInside(dot);
			path[i][j]=0;	//Path arrayimi skor tayini yapmada ve kazananı belirlemede kullanıyorum
		}
	}	
}

Hex::~Hex(){	
	for(int i=0;i<26;i++){		//Destructor'ımda hexCells'in allocate ettiği
		delete [] hexCells[i];	//tüm memory'i temizliyorum ve hexCells'i 
	}							//nullptr'a atıyorum.
	delete [] hexCells;
	hexCells=nullptr;
}

Hex::Hex(const Hex& other){
	int i,j;
	for(i=0;i<26;i++){		//Copy constructor'da hexCells'in tüm hücrelerini kopyaladıktan sonra
		for(j=0;j<26;j++){	//geriye kalan data'ları '=' işareti ile kolayca kopyaladım.
			hexCells[i][j].setInside(other.hexCells[i][j].getInside());
			path[i][j]=other.path[i][j];
		}
	}
	boardsize=other.boardsize;
	turn=other.turn;
	versus=other.versus;
	initialize=other.initialize;
}

bool Hex::winCheck(){
	int i,j,row=0,column=0,finish;
	if(turn%2==0){		//User1'in kazanma durumunu kontrol ediyorum
		for(row=0;row<boardsize;row++){		//Eğer sol duvardaki hücrelerden birinde 'x' varsa
			if(hexCells[row][column].getInside()==pl1){	//Kontrol etmeye başlıyor, aksi takdirde geçiyor.
				finish=is_x_win(row,column);	//is_x_win fonksiyonu 0 dışında bir değer gönderirse
				if(finish!=0){					//User1 kazanmış demektir.
					for(i=0;i<boardsize;i++){	
						for(j=0;j<boardsize;j++){	//Bütün 'x'leri büyütüyorum
							if(path[i][j]==1){	//Bunu anlamak için de programın galibiyet yolunu bulduğu path'ı kullanıyorum.
								hexCells[i][j].setInside(hexCells[i][j].getInside()-32);
							}
						}
					}
					showBoard();	//Kazananın harflerinin büyük yazıldığı board'ı bastırıyorum.
					cout<<"\n\n\nUser1 (x) Won!!\n";
					cout<<"\nUser1's last score is :"<<score[0]<<endl;		//User1'in skorunu yazdırdım.
					initialize=0;	//Oyun bittiği için initialize flag'ımı 0 yaptım.
					return true;	//Kazanan olduğunu belirtmek için true döndürüyorum.
				}
			}
		}
	}
	
	else if(turn%2==1){		//User1'in kazanma durumunu kontrol ediyorum
		for(column=0;column<boardsize;column++){	//Eğer üst duvardaki hücrelerden birinde 'o' varsa
			if(hexCells[row][column].getInside()==pl2){	//Kontrol etmeye başlıyor, aksi takdirde geçiyor.
				finish=is_o_win(row,column);	//is_o_win fonksiyonu 0 dışında bir değer gönderirse
				if(finish!=0){					//User2 kazanmış demektir.
					for(i=0;i<boardsize;i++){
						for(j=0;j<boardsize;j++){	//Bütün 'x'leri büyütüyorum
							if(path[i][j]==1){	//Bunu anlamak için de programın galibiyet yolunu bulduğu path'ı kullanıyorum.
								hexCells[i][j].setInside(hexCells[i][j].getInside()-32);
							}
						}
					}
					showBoard();	//Kazananın harflerinin büyük yazıldığı board'ı bastırıyorum.
					cout<<"\n\n\nUser2 (o) Won!!\n";
					cout<<"\nUser2's last score is :"<<score[1]<<endl;	//User2'nin skorunu yazdırdım.
					initialize=0;	//Oyun bittiği için initialize flag'ımı 0 yaptım.
					return true;	//Kazanan olduğunu belirtmek için true döndürüyorum.
				}
			}
		}
	}
	return false;	//Kazanan yoksa false döndürüyor.
}

Hex::Hex(){		//Constructor'ımda olması gereken default değerleri atadım.
	end=false;
	turn=-1;
	initialize=0;
	score[0]=0;
	score[1]=0;
}

void Hex::play(int row,int column){	//User'ın girdiği satır ve sütun değerlerini
	if(turn%2==0){					//tahtaya yerleştiriyorum.
		hexCells[row][column].setInside(pl1);	//turn%2==0 ise tahtaya pl1'i, yani 'x'i yaz. 
	}
	else if(turn%2==1){
		hexCells[row][column].setInside(pl2);	//turn%2==1 ise tahtaya pl2'i, yani 'o'yu yaz. 
	}
}

void Hex::playGame(){
	
	cin>>*this;		//Stream insertion operataor overloading ile (istream)
}					//Gerekli data'ları kullanıcıdan alıyorum.

void Hex::save_game(Hex games[5]){
	ofstream output;	//Stream Extraction operator overloading ile (ofstream)
	output<<games[gameNum];	//object'imin datalarını dosyaya kaydediyorum.
}

void Hex::load_game(Hex games[5]){
	ifstream input;	//Stream insertion operator overloading ile (ifstream)
	input>>games[gameNum];	//Gerekli data'ları dosyadan çekiyorum.
}

void Hex::player_move(Hex games[5]){
	int check=1,num,column,row;
	string str,str2,substring3,substring4,substring6,substring7;
	
	cout<<"\n\nInput Format : 'C 11'\n";
	cout<<"\nYour Options:\nEnter Cell Coordinate ('C 11')\n";
	cout<<"LOAD or SAVE the game (LOAD filename.txt)/(SAVE filename.txt)\n";
	cout<<"Switch to another game = SWITCH <game number> (SWITCH 4)\n";
	cout<<"Compare 2 game = COMPARE <game number> (COMPARE 2)\n";
	cout<<"Undo Game with prefix or postfix operators (UNDO prefix) or (UNDO postfix)\n";
	cout<<"End The Program : (END program)";
	check=0;

	if(turn%2==0){			//turn%2==0 ise User1'in sırası
		cout<<"\n\n\n\nUser1's turn (x)\nUser1's Score is :"<<score[0]<<"\n\n";
		score[0]=0;	//Her skoru bastırdıktan sonra sıfıra eşitliyorum çünkü eşitlemezsem, 
					//yeni bir connected cell girmese bile skor artıyor.
	}
	else if(turn%2==1){		//turn%2==1 ise User2'nin sırası
		cout<<"\n\n\n\nUser2's turn (o)\nUser2's Score is :"<<score[1]<<"\n\n";
		score[1]=0;	//Her skoru bastırdıktan sonra sıfıra eşitliyorum çünkü eşitlemezsem, 
	}				//yeni bir connected cell girmese bile skor artıyor.
	

	cout<<"\nEnter an input:";
	cin>>str>>str2;
	
	substring3=str.substr(0,3);//3 karakter olan END stringini kontrol etmek için
	substring4=str.substr(0,4);//4 karakter olan SAVE,LOAD ve UNDO stringlerini kontrol etmek için
	substring6=str.substr(0,6);//6 karakter olan SWITCH stringini kontrol etmek için
	substring7=str.substr(0,7);//7 karakter olan COMPARE stringini kontrol etmek için

	if(substring3=="END"){	//Girilen string END program ise program terminate ediliyor.
		if(str2=="program"){
			cout<<"Program Terminating...\n\n";
			end=true;
		}
		else{
			cout<<"Wrong entered, Terminating failed.";
		}
	}
	
	else if(substring4=="SAVE"){	//Girilen ilk string SAVE ise;
		filename=str2;		//string2'den filename'i alıyorum
		save_game(games);	//ve Save fonksiyonumu çağırıyorum.
		turn--;		//Kullanıcı hamle yapmadığından turn'ün değişmemesi için
	}				//bir eksiltiyorum.
	else if(substring4=="LOAD"){	//Girilen ilk string LOAD ise;
		filename=str2;		//string2'den filename'i alıyorum
		load_game(games);	//ve Loadfonksiyonumu çağırıyorum.
		turn--;
	}
	else if(substring4=="UNDO"){	//Girilen ilk string UNDO ise;
		if(str2=="prefix"){
			cout<<"This part will be available soon..";
		}
		else if(str2=="postfix"){
			cout<<"This part will be available soon..";
		}
		else{
			cerr<<"Wrong entered, Undo failed.";
			turn--;
		}

		
	}

	else if(substring6=="SWITCH"){	//Girilen ilk string SWITCH ise;
		turn--;
		num=stoi(str2)-1;	//Geçilmek istenen oyunun numarasını str2'den çekiyorum.
		Hex::setGameNum(num);	//str2'den çektiğim yeni oyunun numarasını gameNum'a,
	}							//yani güncel oyun data'sına atıyorum.
		
	else if(substring7=="COMPARE"){	//Girilen ilk string COMPARE ise;
		num=stoi(str2)-1;	//Compare edilmek istenen oyunun numarasını çekiyorum.
		if(games[Hex::gameNum]==games[num]){	//Overloaded '==' fonksiyonunu çağırdım.
			cout<<"\n\n\nGAMES ARE EQUAL!!!\n";	//True döndürdüyse iki oyun eşittir.
		}
		else{
			cout<<"\n\n\nGAMES ARE NOT EQUAL\n";//False döndürdüyse iki oyun eşit değildir.
		}
		turn--;
	}

	else{	//Yukarıdakilerden hiçbirini girmediyse cell'in koordinatını girmiştir.
		
		column=str[0]-65;	//row ve Column değerlerini stringlerden çekiyorum.
		row=stoi(str2)-1;
		check=1;
		
		while(check==1){	//Girilen koordinat geçerli olana kadar istemeye devam ediyorum.
			check=0;
			if(column>=boardsize||column<0||row>=boardsize||row<0){
				cerr<<"\nEntered input is out of board\n";
				check=1;		//Oynanılmak istenen hücre tahtanın dışındaysa hata veriyor
			}
			else if(hexCells[row][column].getInside()!=dot){
				cerr<<"\nCell is full\n";
				check=1;		//Oynanılmak istenen hücre doluysa hata veriyor
			}
			else if(check==0&&turn%2==0){	//Üstteki durumlardan hiçbiri yoksa o hücreye
				hexCells[row][column].setInside(pl1);	//harf koyabiliriz
			}
			else if(check==0&&turn%2==1){
				hexCells[row][column].setInside(pl2);
			}
			if(check==1){
				cout<<"\nEnter Coordinate of the Cell (C 5) :";
				cin>>str>>str2;	
				column=str[0]-65;
				row=stoi(str2)-1;
			}

		}
		play(row,column);	//Verdiğim koordinatlara sıra kimdeyse onun harfini koyuyor.
	}
}

void Hex::showBoard(){	//Stream extraction operator overloading ile (ostream)
						
	cout<<*this;					
}						//Tahtayı ekrana bastırıyorum.	


int Hex::is_x_win(int row,int column){
	int i,j,k,var=0;				//Bu fonksiyonda harf aramayı soldan sağa doğru yapıyorum. 

	if(hexCells[row][column].getInside()!=pl1){	//Bakılan hücrede x yoksa 0 döndür
		return 0;
	}
							//Bakılan hücrede x varsa gelinen yolu unutmamak için path
	path[row][column]=1;	//arrayinin aynı hücresine 1 koyuyorum.
	score[0]+=10;			
								//Eğer ilk column'dan son column'a kadar gelinebilmişse
	if(column==boardsize-1){	//x doğru bir path kurmuş demektir
		return 1;				//Galibiyet durumunda 1 döndür
	}

	if(row==0&&column==0){		//Buradaki if else bloklarında tahtanın her bir ayrı köşesi, duvarı için
		var=is_x_win(row,column+1);	//ayrı bir durumu kontrol etmem gerekti.
								//Mesela mevcut konum tahtanın sol üst köşedeki hücresiyse, bir hücre üstü veya
		if(var==0){				//bir hücre solu kontrol edemem, out of board'ı kontrol etmiş olurum.
			path[row][column]=0;//Tahtanın her spesifik köşesi/duvarı için farklı kontrol mekanizması.
		}						//Yanlış yollardan dönüp doğru yola girebilmek için recursion kullandım.
		return var;
	}
	else if(row==boardsize-1&&column==0){
		if(path[row][column+1]!=1){
			var=is_x_win(row,column+1);
		}
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(row-1,column+1);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==0){
		if(path[row][column+1]!=1){
			var=var+is_x_win(row,column+1);
		}
		if(path[row+1][column]!=1){
			var=var+is_x_win(row+1,column);
		}		
		if(path[row+1][column-1]!=1){
			var=var+is_x_win(row+1,column-1);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(column==0){
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(row-1,column+1);
		}		
		if(path[row][column+1]!=1){
			var=var+is_x_win(row,column+1);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==boardsize-1){
		if(path[row-1][column]!=1){
			var=var+is_x_win(row-1,column);
		}		
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(row-1,column+1);
		}
		if(path[row][column+1]!=1){
			var=var+is_x_win(row,column+1);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else{
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(row-1,column+1);
		}		
		if(path[row][column+1]!=1){
			var=var+is_x_win(row,column+1);
		}
		if(path[row+1][column]!=1){
			var=var+is_x_win(row+1,column);
		}
		if(path[row-1][column]!=1){
			var=var+is_x_win(row-1,column);
		}
		if(path[row][column-1]!=1){
			var=var+is_x_win(row,column-1);
		}
		if(path[row+1][column-1]!=1){
			var=var+is_x_win(row+1,column-1);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}	
}

int Hex::is_o_win(int row,int column){
	int i,j,var=0;					//is_x_win fonksiyonunun 'o' için düzenlenmiş hali.
	if(hexCells[row][column].getInside()!=pl2){	//Mantık aynı.
		return 0;
	}
	
	path[row][column]=1;
	score[1]+=10;
	
	if(row==boardsize-1){
		return 1;
	}

	if(row==0&&column==0){
		var=is_o_win(row+1,column);
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==0&&column==boardsize-1){
		if(path[row+1][column]!=1){
			var=is_o_win(row+1,column);
		}
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(row+1,column-1);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==0){
		if(path[row+1][column]!=1){
			var=var+is_o_win(row+1,column);
		}		
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(row+1,column-1);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(column==0){
		if(path[row-1][column+1]!=1){
			var=var+is_o_win(row-1,column+1);
		}		
		if(path[row][column+1]!=1){
			var=var+is_o_win(row,column+1);
		}
		if(path[row+1][column]!=1){
			var=var+is_o_win(row+1,column);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(column==boardsize-1){
		if(path[row+1][column]!=1){
			var=var+is_o_win(row+1,column);
		}		
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(row+1,column-1);
		}
		if(path[row][column-1]!=1){
			var=var+is_o_win(row,column-1);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else{
		if(path[row-1][column+1]!=1){
			var=var+is_o_win(row-1,column+1);
		}
		if(path[row][column+1]!=1){
			var=var+is_o_win(row,column+1);
		}
		if(path[row+1][column]!=1){
			var=var+is_o_win(row+1,column);
		}
		if(path[row-1][column]!=1){
			var=var+is_o_win(row-1,column);
		}
		if(path[row][column-1]!=1){
			var=var+is_o_win(row,column-1);
		}
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(row+1,column-1);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}	
}


////////////////////    OPERATOR OVERLOADS
Hex& Hex::operator =(const Hex& rightSide){
	char c;
	if(this!=&rightSide){	//Aynı objeyi birbirine eşitlemekle uğraşmaması için.
		int i,j;
		for(i=0;i<26;i++){
			for(j=0;j<26;j++){		//hexCells objesini kopyaladıktan sonra gerisini kolayca eşitleyebiliriz.
				c=rightSide.hexCells[i][j].getInside();
				hexCells[i][j].setInside(c);
				path[i][j]=rightSide.path[i][j];
			}
		}
		boardsize=rightSide.boardsize;
		turn=rightSide.turn;
		versus=rightSide.versus;
		initialize=rightSide.initialize;
	}
	return *this;	//Chain Assignment Operator'ler için return ediyorum.
}

Hex Hex::operator--(){

	return Hex();
}

Hex Hex::operator--(int i){
	
	return Hex();
}

bool Hex::operator==(const Hex& other){
	int i,j,check=0;	//Check'i default olarak 0 yaptım.
	if(boardsize==other.boardsize){		//Basit bir comparison işlemiyle sonuca göre true veya false döndürüyorum.
		for(i=0;i<boardsize;i++){
			for(j=0;j<boardsize;j++){
				if(hexCells[i][j].getInside()!=other.hexCells[i][j].getInside()){	
					check=1;	//eğer farklı tek bir hücre varsa check 1 oluyor.
				}
			}
		}
		if(check==0){	//Check 0 olarak kaldıysa tüm hücreler aynı demektir.
			return true;
		}
	}

	return false;
}

ofstream& operator <<(ofstream& output, const Hex& object){
	int i,j;
	output.open(object.filename);		//Save işlemi
	output<<object.boardsize<<"\n";		//Gerekli olan tüm data'yı belirlediğim sırada dosyaya yazdırıyorum.
	for(i=0;i<object.boardsize;i++){
		for(j=0;j<object.boardsize;j++){
			output<<object.hexCells[i][j].getInside();
		}
	}
	output<<"\n"<<object.turn<<"\n"<<object.versus;
	cout<<"Save Completed.\n";
	output.close();

	return output;
}

ifstream& operator >>(ifstream& input, Hex& object){
	int i,j;
	char c;							//Load işlemi
	input.open(object.filename);
	if(input.fail()){		//Eğer böyle bir dosya yoksa hata mesajı verip alt statement'a girmiyor.
		cerr<<"\nFile doesn't exist, Load failed.\n";
	}
	else{
		input>>object.boardsize;				//İlk boardsize'ımı alıyorum ki x ve o'ları yeni tahtama
		for(i=0;i<object.boardsize;i++){		//göre dizebileyim.
			for(j=0;j<object.boardsize;j++){
				input>>c;
				object.hexCells[i][j].setInside(c);
			}
		}
		input>>object.turn;					//ardından turn  ve versus değişkenlerimi alıyorum
		input>>object.versus;
		cout<<"\nLoading Completed\n";	
	}
	input.close();

	return input;
}

ostream& operator <<(ostream& output, const Hex& object){
	int i,j,k;
	cout<<"   ";
	for(i=0;i<object.boardsize;i++){		//Cout işlemi
		cout<<object.letter[i]<<"  ";
	}
	cout<<"\n";							//Object'imin gerekli olan data'larını
	for(i=0;i<object.boardsize;i++){	//ekrana yazdırıyorum.
		cout<<i+1;
		for(k=0;k<i;k++){
			cout<<" ";
		}
		for(j=0;j<object.boardsize;j++){
			cout<<"  "<<object.hexCells[i][j].getInside();
		}
		cout<<"\n";
	}
	return output;
}

istream& operator >>(istream& input, Hex& object){
	int check=1,size,vs;			//Cin işlemi
	while(check==1){
		cout<<"Enter the board size of the "<<Hex::gameNum+1<<". Game(5 to 26) : ";
		check=0;
		cin>>size;				//Objemin gerekli olan data'larını kullanıcıdan istiyorum
		if(size<5||size>26){
			cerr<<"\nYou entered wrong, please try again.\n\n";
			check=1;			//Validity'e de dikkat ettim.
		}
	}
	object.setBoardsize(size);
	
	check=1;
	
	while(check==1){
		cout<<"\nEnter '0' for user1 vs user2\nEnter '1' for computer vs user for"<<Hex::gameNum+1<<". Game : ";
		check=0;
		cin>>vs;
		if(vs!=1&&vs!=0){
			cerr<<"\nYou entered wrong, please try again.\n\n";
			check=1;
		}
	 	if(vs==1){
	 		cerr<<"\nvs Computer part is not available yet, please try again.\n\n";
	 		check=1;
	 	}
	}
	object.setVersus(vs);

	return input;
}