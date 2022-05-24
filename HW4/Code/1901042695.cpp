#include <iostream>
#include <string>
#include <fstream>
#include "hex.h"
using namespace std;

int main(){

	Hex games[5];
	int i,j,num,check=1,sira,row=0,column=0,size,var,turnVar=0;
	bool win;


	while(!Hex::getEnd()){		//End flag'ı false iken devam et
		
		num=Hex::getGameNum();	//Güncel oyunun numarasını alıyorum. Default olarak 0.

		if(games[num].getInit()==0){	//Oyun initialize edilmemişse initialize ediyorum
			games[num].startObject();
			games[num].playGame();
			games[num].setInit(1);		//ve initialize flag'ımı 1 yapıyorum

		}

		games[num].setTurn(games[num].getTurn()+1);	//while'ın her döngüsünde turn değişkeni bir artacak
		games[num].showBoard();						//Böylelikle her seferinde sıra değişecek.
													//turn%2==0 ise sıra user1'de, turn%2==1 ise sıra user2'de
		games[num].player_move(games);		//Kullanıcıdan input aldım
		win=games[num].winCheck();			//galibiyet durumunu kontrol ettim

		if(win){		//eğer biri kazandı ise kullanıcıya hangi oyuna devam etmek
			while(check==1){	//istediğini soruyorum.
				check=0;
				cout<<"Which Game do you want to continue?(1 to 5) :";
				cin>>var;
				if(var<1||var>5){
					cerr<<"\nWrong entered, please try again.";
					check=1;
				}
				else{
					var--;
					Hex::setGameNum(var);	//Yeni oyunun numarasını güncel oyun numarasına atıyorum.
				}
			}

		}	

	}

}