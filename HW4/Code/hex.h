#ifndef hex
#define hex


using namespace std;



enum statement{pl1 = 'x', pl2 = 'o', dot = '.'};	//enum tipim

class Hex{

//////////////////// PUBLIC PART
public:
	
	class Cell{		//İçinde birer setter/getter bulunan Cell class'ım
		public:
			void setInside(char c){	inside=c;	}
			char getInside(){	return inside;	}

		private:
			char inside;	//verilen değere göre '.' 'x','o' olabiliyor. 

	};

	//Big Three is Needed
	~Hex();//Destructor
	Hex(const Hex& other);// Copy Constructor
	Hex& operator =(const Hex& rightSide);//Overloaded Assigment Operator
	
	
	explicit Hex();		//Constructor


//////////////// OPERATOR OVERLOADS

	Hex operator--();		//Prefix Version
	Hex operator--(int i);	//Postfix Version
	bool operator==(const Hex& other);
	friend ostream& operator <<(ostream& output, const Hex& object);
	friend istream& operator >>(istream& input, Hex& object);
	friend ofstream& operator <<(ofstream& output, const Hex& object);
	friend ifstream& operator >>(ifstream& input, Hex& object);	


	Cell play();		//Computer'a bir adım oyun oynatan fonksiyon
	void play(int row,int column);		//User'a bir adım oyun oynatan fonksiyon
	void showBoard();		//Tahtayı ekrana bastıran fonksiyon
	void player_move(Hex games[5]);		//Kullanıcıdan input alan fonksiyon
	int is_x_win(int row,int column);	//X'in kazanma durumunu kontrol eden fonksiyon
	int is_o_win(int row,int column);	//O'nun kazanma durumunu kontrol eden fonksiyon
	void computer_move();				//Computer'ın yapay zekası
	void save_game(Hex games[5]);		//Oyunu kaydetme fonksiyonu
	void load_game(Hex games[5]);		//Kaydedilmiş oyunu yükleme fonksiyonu
	void playGame();		//Kullanıcıdan boardsize ve versus data'larını alan fonksiyon
	bool winCheck();		//Kazanma durumlarını kontrol eden fonksiyon
	void startObject();		//Board'ı default olarak '.' ile dolduran ve gerektiği kadar memory allocate eden fonksiyon
	
////////////////   SETTERS				Inline setter fonksiyonlarım
	void setBoardsize(int var){	boardsize=var;}

	void setTurn(int var){	turn=var;	}

	void setVersus(int var){	versus=var;	}

	void setInit(int var){	initialize=var;	}

	void setScore(int var){	score[turn%2]=var;	}

	void setFilename(string var){	filename=var;	}

	static void setGameNum(int var){	Hex::gameNum=var;	}

////////////////	GETTERS				Inline getter fonksiyonlarım
	int getBoardsize(){	return boardsize;	}

	int getTurn(){		return turn;	}

	int getVersus(){	return versus;	}

	int getInit(){	return initialize;	}

	int getScore(){	return score[turn%2];	}

	string getFilename(){	return filename;	}

	static bool getEnd(){	return end;	}
	
	static int getGameNum(){	return Hex::gameNum;	}


////////////////    PRIVATE PART
private:
	Cell **hexCells;
	int boardsize,turn=-1,versus,path[26][26],initialize=0,score[2]={0,0};
	char letter[27]="abcdefghijklmnopqrstuvwxyz";
	string filename;
	static int gameNum;		//Oynanılan güncel oyun numarasını tutan static data
	static bool end;		//Kullanıcı programı sonlandırırsa true olan flag

};

#endif