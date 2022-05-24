#include<iostream>
#include<string>
#include<fstream>
using namespace std;

enum statement{pl1 = 'x', pl2 = 'o', dot = '.'};		

void create_board(char board[12][12], int boardsize);
string player_move(char board[12][12], int turn,int versus,int boardsize,int* = 0);	//Son değişkende default argument kullandım.Default olarak 0 gönderiyorum,
int is_x_win(char board[12][12],const int &boardsize,int row,int column,int path[12][12]);	//eğer fonksiyon içinde 1 veya 2 olursa Save veya Load işleminin gerçekleştirilmesi
int is_o_win(char board[12][12],const int &boardsize,int row,int column,int path[12][12]);	//gerektiğini bildiriyor.
void computer_move(char board[12][12], int boardsize);
void save_game(char board[12][12],int boardsize,int turn,int versus,string filename);
void load_game(char board[12][12],int *boardsize,int *turn,int *versus,string filename);	//Pointer ile çağırıyorum.

//My program is have at least one function that takes a parameter by reference and a constant parameter by reference.
//My program is have at least one function that uses default arguments.
//All the errors are printed to cerr object.
//My program is have at least one auto statement and one declrtype statement.
//My cell states are be represented using C++11 Enum types.

int main(){
	int boardsize,i,j,k,x,y,end=0,turn,versus,column=0,path[12][12],kontrol=0;
	auto check=1;
	decltype(check)row=0;
	char board[12][12];			//Oyun Tahtam
	string filename;
	cout<<"\n\n-->User1 (or Computer) (x) should form a connected path between left and right boundaries\n";
	cout<<"-->User2 (o) should form a connected path between upper and lower boundaries\n\n";
	while(check==1){
		check=0;
		cout<<"Enter Board Size Between 6 and 12 : ";
		cin>>boardsize;
		if(boardsize<6||boardsize>12){
			check=1;		//Yanlış giriş yapılması halinde check 1 oluyor ve döngü devam ediyor
			cerr<<"You Entered Wrong, Please Try Again\n\n";
		}
	}

	cout<<"\nEnter '0' for user1 vs user2\nEnter '1' for computer vs user : ";
	cin>>versus;
	for(i=0;i<boardsize;i++){			//Board'ımı tamamen noktayla doldurdum
		for(j=0;j<boardsize;j++){
			board[i][j]=dot;
			path[i][j]=0;
		}
	}
	if(versus==0){					//User vs User durumu
		for(turn=0;end==0;turn++){	//Turn değişkeninin 2 ile bölümünden kalan 0 olduğu durumlarda
			row=0;					//user1, kalan 1 olduğu durumlarda user2 oynuyor.
			column=0;				//End'in 0 dışındaki durumlarında oyun bitiyor
			kontrol=0;
			create_board(board,boardsize);		//Board'ı yazdırdım
			filename=player_move(board,turn,versus,boardsize,&kontrol);		//User'dan hamle aldım
			if(kontrol==1){		//Kontrol argumanım 1 olduysa Save'liyorum
				save_game(board,boardsize,turn,versus,filename);	
				cout<<"\nSave Completed.\n";
				turn-=1;		//Turn değişkenini oyunun kaldığı yerden devam etmesi için 1 azaltıyorum
			}
			else if(kontrol==2){	//Kontrol argumanım 2 olduysa istenilen dosyayı load'lıyorum
				load_game(board,&boardsize,&turn,&versus,filename);	//Load yaparken board,boardsize,turn gibi değişkenleri return
				turn-=1;			//call by reference				//olmadan değiştirebilmek için değişkenlerin adresini gönderiyorum.
			}
			if(turn%2==0){						//Hamleyi yapan user1 ise tahtanın ilk sütununda x arıyorum
				for(row=0;row<boardsize;row++){
					if(board[row][column]==pl1){
						end=is_x_win(board,boardsize,row,column,path);	//x'in kazanıp kazanmadığını kontrol ediyor
						if(end!=0){		//eğer end 0 değilse x kazanmış demektir.
							for(x=0;x<boardsize;x++){
								for(y=0;y<boardsize;y++){
									if(path[x][y]==1){	//x'in galibiyet path'ının koordinatlarına path arrayainde 1 koydum. 
										board[x][y]-=32;//Bu sayede Galibiyet path'ındaki harfleri büyütebliliyorum
									}
								}
							}
							create_board(board,boardsize);
							cout<<"\n\n\n User1 (x) won!!\n";
						}
					}
				}
			}

			else if(turn%2==1){		//User2's turn
				for(column=0;column<boardsize;column++){		//0. satırda 'o' arıyorum
					if(board[row][column]==pl2){
						end=is_o_win(board,boardsize,row,column,path);	//'o' kazanmış mı kontrol ediyorum
						if(end!=0){		//'o' kazandıysa end'in değeri 0'dan farklıdır.
							for(x=0;x<boardsize;x++){
								for(y=0;y<boardsize;y++){
									if(path[x][y]==1){
										board[x][y]-=32;	//Galibiyet path'ının harflerini büyütüyorum
									}
								}
							}							
							create_board(board,boardsize);
							cout<<"\n\n\n User2 (o) won!!\n";
						}
					}
				}
			}
		}
	}

	else if(versus==1){
		cout<<"\n\nTHIS PART WILL BE AVAILABLE SOON...\n\n";	//Başaramadık....
		return 0;
		while(end==0){
			create_board(board,boardsize);
			computer_move(board,boardsize);
			for(row=0;row<boardsize;row++){
				if(board[row][column]==pl1){
					end=is_x_win(board,boardsize,row,column,path);
					if(end==1){
						create_board(board,boardsize);
						cout<<"\n\n\n User1 (x) won!!\n";
					}
				}
			}
			create_board(board,boardsize);
			player_move(board,turn,versus,boardsize,&kontrol);
			for(column=0;column<boardsize;column++){
				if(board[row][column]==pl2){
					end=is_o_win(board,boardsize,row,column,path);
					if(end==1){
						create_board(board,boardsize);
						cout<<"\n\n\n User2 (o) won!!\n";
					}
				}
			}			
		}
	}
}


void create_board(char board[12][12],int boardsize){	//Board'ı yazdırma fonksiyonum
	char letter[13]="abcdefghijkl";
	int i,j,k;
	cout<<"   ";
	for(i=0;i<boardsize;i++){
		cout<<letter[i]<<"  ";
	}
	cout<<"\n";
	for(i=0;i<boardsize;i++){
		cout<<i+1;
		for(k=0;k<i;k++){
			cout<<" ";
		}
		for(j=0;j<boardsize;j++){
			cout<<"  "<<board[i][j];
		}
		cout<<"\n";
	}
}

void save_game(char board[12][12],int boardsize,int turn,int versus,string filename){
	int i=0,j=0;
	ofstream output;
	output.open(filename);			//Dosyamı açtım
	output<<boardsize<<"\n";		//İlk olarak boardsize'ımı yazdırdım ve bir alt satıra indim
	for(i=0;i<boardsize;i++){	
		for(j=0;j<boardsize;j++){	//Burada tahtamı tek bir satıra yazdırıyorum
			output<<board[i][j];
		}
	}
	output<<"\n"<<turn<<"\n"<<versus;	//Ardından sıranın kimde olduğunu bildiren turn ve
	output.close();						//oyunun kime karşı oynandığını bildiren versus
}										//değişkenlerini yazdırıyorum.

void load_game(char board[12][12],int *boardsize,int *turn,int *versus,string filename){
	int i=0,j=0;
	ifstream input;
	input.open(filename);
	if(input.fail()){		//Eğer böyle bir dosya yoksa hata mesajı verip alt statement'a girmiyor.
		cerr<<"\nFile doesn't exist, Load failed.\n";
	}
	else{
		input>>*boardsize;				//İlk boardsize'ımı alıyorum ki x ve o'ları yeni tahtama
		for(i=0;i<*boardsize;i++){		//göre dizebileyim.
			for(j=0;j<*boardsize;j++){
				input>>board[i][j];
			}
		}
		input>>*turn;					//ardından turn  ve versus değişkenlerimi alıyorum
		input>>*versus;
		cout<<"\nLoading Completed\n";	
	}
	input.close();
}

string player_move(char board[12][12], int turn,int versus,int boardsize,int *kontrol){	//User'ların inputunu burada alyorum
	int check=1,row,column,length;
	string str,str2,filename,sl;
	cout<<"\n\nInput Format : 'C 11'\n";

	while(check==1){
		check=0;
		if(versus==1){
			cout<<"User's turn (o)\n ";
		}
		else if(versus==0 && turn%2==0){	//turn%2==0 ise User1'in sırası
			cout<<"User1's turn (x)\n ";
		}
		else if(versus==0 && turn%2==1){	//turn%2==1 ise User2'nin sırası
			cout<<"User2's turn (o)\n ";
		}
		cout<<"\nEnter coordinate of cell :";
		cin>>str>>str2;
		sl=str.substr(0,4);
		if(sl=="SAVE"){
			length=str2.size();		//Yüklenmek istenen oyun isminin uzunluğunu buldum ki,
			filename=str2.substr(0,length);		//filename değişkenime kaç karakter alacağımı bileyim.
			*kontrol=1;			//kontrol değişkeninin 1 olması programa kullanıcının save etmek istediğini bildiriyor.
			return filename;
		}
		else if(sl=="LOAD"){
			length=str2.size();		//Yüklenmek istenen oyun isminin uzunluğunu buldum ki,
			filename=str2.substr(0,length);		//filename değişkenime kaç karakter alacağımı bileyim.
			*kontrol=2;			//kontrol değişkeninin 2 olması programa kullanıcının load etmek istediğini bildiriyor.
			return filename;
		}
		else{
			column=str[0]-65;		//karakteri integer'a çevirdim.
			row=stoi(str2)-1;		//str2'yi integera çevirdikten sonra 1 çıkararak satır değerini 0'dan başlattım
			if(column>=boardsize||column<0||row>=boardsize||row<0){
				cerr<<"\nEntered input is out of board\n";
				check=1;		//Oynanılmak istenen hücre tahtanın dışındaysa hata veriyor
			}
			else if(board[row][column]!='.'){
				cerr<<"\nCell is full\n";
				check=1;		//Oynanılmak istenen hücre doluysa hata veriyor
			}
			if(check==0&&turn%2==0){	//Üstteki durumlardan hiçbiri yoksa o hücreye
				board[row][column]='x';	//harf koyabiliriz
			}
			else if(check==0&&turn%2==1){
				board[row][column]='o';
			}
			else if(check==1){			//hatalı giriş durumunda en son tekrar deneyin uyarısı veriyorum
				cerr<<"Please try again\n\n";
			}
		}
	}
	return filename;
}

int is_x_win(char board[12][12],const int &boardsize,int row,int column,int path[12][12]){
	int i,j,k,var=0;				//Bu fonksiyonda harf aramayı soldan sağa doğru yapıyorum. 

	if(board[row][column]!=pl1){	//Bakılan hücrede x yoksa 0 döndür
		return 0;
	}
	path[row][column]=1;		//Eğer ilk column'dan son column'a kadar gelinebilmişse
	if(column==boardsize-1){	//x doğru bir path kurmuş demektir
		return 1;				//Galibiyet durumunda 1 döndür
	}

	if(row==0&&column==0){		//Buradaki if else bloklarında tahtanın her bir ayrı köşesi, duvarı için
		var=is_x_win(board,boardsize,row,column+1,path);	//ayrı bir durumu kontrol etmem gerekti.
								//Mesela mevcut konum tahtanın sol üst köşedeki hücresiyse, bir hücre üstü veya
		if(var==0){				//bir hücre solu kontrol edemem, out of board'ı kontrol etmiş olurum.
			path[row][column]=0;//Tahtanın her spesifik köşesi/duvarı için farklı kontrol mekanizması.
		}						//Yanlış yollardan dönüp doğru yola girebilmek için recursion kullandım.
		return var;
	}
	else if(row==boardsize-1&&column==0){
		if(path[row][column+1]!=1){
			var=is_x_win(board,boardsize,row,column+1,path);
		}
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(board,boardsize,row-1,column+1,path);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==0){
		if(path[row][column+1]!=1){
			var=var+is_x_win(board,boardsize,row,column+1,path);
		}
		if(path[row+1][column]!=1){
			var=var+is_x_win(board,boardsize,row+1,column,path);
		}		
		if(path[row+1][column-1]!=1){
			var=var+is_x_win(board,boardsize,row+1,column-1,path);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(column==0){
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(board,boardsize,row-1,column+1,path);
		}		
		if(path[row][column+1]!=1){
			var=var+is_x_win(board,boardsize,row,column+1,path);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==boardsize-1){
		if(path[row-1][column]!=1){
			var=var+is_x_win(board,boardsize,row-1,column,path);
		}		
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(board,boardsize,row-1,column+1,path);
		}
		if(path[row][column+1]!=1){
			var=var+is_x_win(board,boardsize,row,column+1,path);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else{
		if(path[row-1][column+1]!=1){
			var=var+is_x_win(board,boardsize,row-1,column+1,path);
		}		
		if(path[row][column+1]!=1){
			var=var+is_x_win(board,boardsize,row,column+1,path);
		}
		if(path[row+1][column]!=1){
			var=var+is_x_win(board,boardsize,row+1,column,path);
		}
		if(path[row-1][column]!=1){
			var=var+is_x_win(board,boardsize,row-1,column,path);
		}
		if(path[row][column-1]!=1){
			var=var+is_x_win(board,boardsize,row,column-1,path);
		}
		if(path[row+1][column-1]!=1){
			var=var+is_x_win(board,boardsize,row+1,column-1,path);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
}

int is_o_win(char board[12][12],const int &boardsize,int row,int column,int path[12][12]){
	int i,j,var=0;					//is_x_win fonksiyonunun o için düzenlenmiş hali.
	if(board[row][column]!=pl2){	//Mantık aynı.
		return 0;
	}
	path[row][column]=1;
	if(row==boardsize-1){
		return 1;
	}

	if(row==0&&column==0){
		var=is_o_win(board,boardsize,row+1,column,path);
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==0&&column==boardsize-1){
		if(path[row+1][column]!=1){
			var=is_o_win(board,boardsize,row+1,column,path);
		}
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(board,boardsize,row+1,column-1,path);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(row==0){
		if(path[row+1][column]!=1){
			var=var+is_o_win(board,boardsize,row+1,column,path);
		}		
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(board,boardsize,row+1,column-1,path);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(column==0){
		if(path[row-1][column+1]!=1){
			var=var+is_o_win(board,boardsize,row-1,column+1,path);
		}		
		if(path[row][column+1]!=1){
			var=var+is_o_win(board,boardsize,row,column+1,path);
		}
		if(path[row+1][column]!=1){
			var=var+is_o_win(board,boardsize,row+1,column,path);
		}
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else if(column==boardsize-1){
		if(path[row+1][column]!=1){
			var=var+is_o_win(board,boardsize,row+1,column,path);
		}		
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(board,boardsize,row+1,column-1,path);
		}
		if(path[row][column-1]!=1){
			var=var+is_o_win(board,boardsize,row,column-1,path);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
	else{
		if(path[row-1][column+1]!=1){
			var=var+is_o_win(board,boardsize,row-1,column+1,path);
		}
		if(path[row][column+1]!=1){
			var=var+is_o_win(board,boardsize,row,column+1,path);
		}
		if(path[row+1][column]!=1){
			var=var+is_o_win(board,boardsize,row+1,column,path);
		}
		if(path[row-1][column]!=1){
			var=var+is_o_win(board,boardsize,row-1,column,path);
		}
		if(path[row][column-1]!=1){
			var=var+is_o_win(board,boardsize,row,column-1,path);
		}
		if(path[row+1][column-1]!=1){
			var=var+is_o_win(board,boardsize,row+1,column-1,path);
		}		
		
		if(var==0){
			path[row][column]=0;
		}
		return var;
	}
}

void computer_move(char board[12][12], int boardsize){ //Başaramadık....

}