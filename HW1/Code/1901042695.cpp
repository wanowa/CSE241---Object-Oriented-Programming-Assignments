#include<iostream>
using namespace std;
void create_board(char board[12][12], int boardsize);
void player_move(char board[12][12], int turn,int versus,int boardsize);
int is_x_win(char board[12][12],int boardsize,int row,int column,int path[12][12]);
int is_o_win(char board[12][12],int boardsize,int row,int column,int path[12][12]);
void computer_move(char board[12][12], int boardsize);

int main(){
	int boardsize,i,j,k,x,y,end=0,turn,versus,check=1,row=0,column=0,path[12][12];
	char board[12][12];			//Oyun Tahtam
	cout<<"\n\n-->User1 (or Computer) (x) should form a connected path between left and right boundaries\n";
	cout<<"-->User2 (o) should form a connected path between upper and lower boundaries\n\n";
	while(check==1){
		check=0;
		cout<<"Enter Board Size Between 6 and 12 : ";
		cin>>boardsize;
		if(boardsize<6||boardsize>12){
			check=1;		//Yanlış giriş yapılması halinde check 1 oluyor ve döngü devam ediyor
			cout<<"You Entered Wrong, Please Try Again\n\n";
		}
	}

	cout<<"\nEnter '0' for user1 vs user2\nEnter '1' for computer vs user : ";
	cin>>versus;
	for(i=0;i<boardsize;i++){			//Board'ımı tamamen noktayla doldurdum
		for(j=0;j<boardsize;j++){
			board[i][j]='.';
			path[i][j]=0;
		}
	}
	if(versus==0){					//User vs User durumu
		for(turn=0;end==0;turn++){	//Turn değişkeninin 2 ile bölümünden kalan 0 olduğu durumlarda
			row=0;					//user1, kalan 1 olduğu durumlarda user2 oynuyor.
			column=0;				//End'in 0 dışındaki durumlarında oyun bitiyor
			create_board(board,boardsize);		//Board'ı yazdırdım
			player_move(board,turn,versus,boardsize);		//User'dan hamle aldım
			if(turn%2==0){						//Hamleyi yapan user1 ise tahtanın ilk sütununda x arıyorum
				for(row=0;row<boardsize;row++){
					if(board[row][column]=='x'){
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
					if(board[row][column]=='o'){
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
				if(board[row][column]=='x'){
					end=is_x_win(board,boardsize,row,column,path);
					if(end==1){
						create_board(board,boardsize);
						cout<<"\n\n\n User1 (x) won!!\n";
					}
				}
			}
			create_board(board,boardsize);
			player_move(board,turn,versus,boardsize);
			for(column=0;column<boardsize;column++){
				if(board[row][column]=='o'){
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

void player_move(char board[12][12], int turn,int versus,int boardsize){	//User'ların inputunu burada alyorum
	int check=1,row,column;
	char karakter;
	cout<<"Input Format : 'C 11'\n\n";
	while(check==1){
		check=0;
		if(versus==1){		
			cout<<"User's turn (o) : ";
		}
		else if(versus==0 && turn%2==0){	//turn%2==0 ise User1'in sırası
			cout<<"User1's turn (x) : ";
		}
		else if(versus==0 && turn%2==1){	//turn%2==1 ise User2'nin sırası
			cout<<"User2's turn (o) : ";
		}
		cin>>karakter>>row;		//bir char bir integer alıyorum
		column=karakter-65;		//karakteri integer'a çevirdim.
		row--;					//satır değerini 0'dan başlattım
		if(column>=boardsize||column<0||row>=boardsize||row<0){
			cout<<"Entered input is out of board\n";
			check=1;		//Oynanılmak istenen hücre tahtanın dışındaysa hata veriyor
		}
		else if(board[row][column]!='.'){
			cout<<"Cell is full\n";
			check=1;		//Oynanılmak istenen hücre doluysa hata veriyor
		}
		if(check==0&&turn%2==0){	//Üstteki durumlardan hiçbiri yoksa o hücreye
			board[row][column]='x';	//harf koyabiliriz
		}
		else if(check==0&&turn%2==1){
			board[row][column]='o';
		}
		else if(check==1){			//hatalı giriş durumunda en son tekrar deneyin uyarısı veriyorum
			cout<<"Please try again\n\n";
		}
	}
}

int is_x_win(char board[12][12],int boardsize,int row,int column,int path[12][12]){
	int i,j,k,var=0;				//Bu fonksiyonda harf aramayı soldan sağa doğru yapıyorum. 

	if(board[row][column]!='x'){	//Bakılan hücrede x yoksa 0 döndür
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

int is_o_win(char board[12][12],int boardsize,int row,int column,int path[12][12]){
	int i,j,var=0;					//is_x_win fonksiyonunun o için düzenlenmiş hali.
	if(board[row][column]!='o'){	//Mantık aynı.
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