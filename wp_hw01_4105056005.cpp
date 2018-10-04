/******
4105056005	鄭筠庭	第一次作業10/9
******/

/*
	操作說明:
*/

// wp_hw01_4105056005.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstring>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::fstream;
using std::string;

//設定初始值。playerName是玩家名稱；pmoney是玩家金錢數量；plocations是地圖上各地點名稱 : pdice是骰子點數。
char* playerName = new char[40];
int* pmoney = new int;
const char** plocations = new const char*[28];
int* pdice = new int;

//設定各地地名
void initialLocation() {
	*(plocations) = "Start ->";
	*(plocations + 1) = "01台北";
	*(plocations + 2) = "NewTaipei";
	*(plocations + 3) = "Taoyuan";
	*(plocations + 4) = "Hsinchu";
	*(plocations + 5) = "Miaoli";
	*(plocations + 6) = "CHANCE";
	*(plocations + 7) = "Taichung";
	*(plocations + 8) = "Changhua";
	*(plocations + 9) = "Nantou";
	*(plocations + 10) = "JAIL:(";
	*(plocations + 11) = "Yunlin";
	*(plocations + 12) = "Chiayi";
	*(plocations + 13) = "Tainan";
	*(plocations + 14) = "Kaohsiung";
	*(plocations + 15) = "PARKING";
	*(plocations + 16) = "Pingtung";
	*(plocations + 17) = "COMMUNITY";
	*(plocations + 18) = "Taitung";
	*(plocations + 19) = "Hualien";
	*(plocations + 20) = "Yilan";
	*(plocations + 21) = "Keelung";
	*(plocations + 22) = "Penghu";
	*(plocations + 23) = "23";
	*(plocations + 24) = "24";
	*(plocations + 25) = "JAIL:(";
	*(plocations + 26) = "26";
	*(plocations + 27) = "27";
	*(plocations + 28) = "CHANCE";
	*(plocations + 29) = "29";
	return;
}

//輸入玩家名稱
void startNewGame() {
	cout << "Welcome to the Mini Monopoly Game.\n" << endl;
	cout << "遊戲說明:\n    此遊戲開始金額為1500元，每次經過起點將獲得300元。" << endl;
	cout << "    每次行動可選擇擲骰子(d)或是重新開始整個遊戲(r)。" << endl;
	cout << "    踩上地名方塊時，可以決定是否購買第一棟房子，或是繼續加蓋房屋。若方塊已經有該玩家蓋的房子，" <<
			"則可獲得房價1.5倍的錢。" << endl;
	cout << "    踩到機會及命運方塊，系統將自動抽牌，並執行牌上的指令。" << endl;
	cout << "\nPlease input player's name: ";
	cin.get(playerName, 39);
	cout << "Hello, " << playerName << ". Now you have $1500 in your bank. Enjoy the game:)"<< endl << endl;
	*pmoney = 1500;
	return;
}

//印出大富翁地圖
void printMap() {
	int* pi = new int;
	int* pj = new int;
	int* pfront = new int;
	int* pback = new int;
	*pfront = 1;
	*pback = 29;
	//橫線
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//共9個9x5小格子，左右2個13x5大格子
	for (*pj = 0; *pj < 5; (*pj)++) {
		//印出地名
		if (*pj == 2) {
			cout << "|   Start ->  ";
			for (*pi = 0; *pi < 9; (*pi)++) {
				cout << "|" << setw(9) << *(plocations+(*pfront));
				(*pfront)++;
			}
			cout << "|    JAIL:(   | ";
			(*pfront)++;
		}
		else {
			cout << "|             ";
			for (*pi = 0; *pi < 9; (*pi)++) {
				cout << "|         ";
			}
			cout << "|             | ";
		}
	}
	//橫線
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//左右2個13x4大格子，三排
	for (*pi = 0; *pi < 3; (*pi)++) {
		for (*pj = 0; *pj < 3; (*pj)++) {
			//印出地名
			if (*pj == 1) {
				cout << "|" << setw(13) << *(plocations + (*pback)) << "|                                             ";
				cout << "                                            |" << setw(13) << *(plocations + (*pfront)) <<"| ";
				(*pfront)++;
				(*pback)--;
			}
			else {
				cout << "|             |                                             ";
				cout << "                                            |             | ";
			}
		}
		cout << "--------------                                                  ";
		cout << "                                        --------------- ";
	}
	for (*pj = 0; *pj < 3; (*pj)++) {
		//印出地名
		if (*pj == 1) {
			cout << "|" << setw(13) << *(plocations + (*pback)) << "|                                             ";
			cout << "                                            |" << setw(13) << *(plocations + (*pfront)) << "| ";
			(*pfront)++;
			(*pback)--;
		}
		else {
			cout << "|             |                                             ";
			cout << "                                            |             | ";
		}
	}
	//橫線
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//共9個9x5小格子，左右2個13x5大格子
	for (*pj = 0; *pj < 5; (*pj)++) {
		//印出地名
		if (*pj == 2) {
			cout << "|    JAIL:(   ";
			(*pback)--;
			for (*pi = 0; *pi < 9; (*pi)++) {
				cout << "|" << setw(9) << *(plocations + (*pback));
				(*pback)--;
			}
			cout << "|   PARKING   | ";
			(*pfront)++;
		}
		else {
			cout << "|             ";
			for (*pi = 0; *pi < 9; (*pi)++) {
				cout << "|         ";
			}
			cout << "|             | ";
		}
	}
	//橫線
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	delete pi, pj;
	return;
}

//儲存或載入遊戲文字檔案
void saveNload() {
	cout << "Do you want to save or load your game file?(s/l) ";
	char* saveload = new char[20];
	cin >> *saveload;
	if (*saveload == 'l') {
		fstream loadFile;
		loadFile.open("Save.txt", fstream::in);
		cout << "Your previous game play file: " << endl << endl;
		while (loadFile.good()) {
			cout << (char)loadFile.get();
		}
		cout << "" << endl;
		loadFile.close();
	}
	/*
	if (*saveload == 's') {
		string textToSave;
		cout << "Enter the string you want saved: " << endl;
		getline(cin, textToSave);
		ofstream saveFile("Save.txt");
		saveFile << textToSave;
		saveFile.close();
	}
	*/
	delete [] saveload;
	return;
}

//亂數骰骰子，從2到12點
void rollDice() {
	char* ptemp = new char[20];
	do {
		cout << "Press d to roll the dice / Press r to restart the whole game. ";
		cin >> *ptemp;
		if (*ptemp == 'd') {
			srand(time(NULL));
			*pdice = (rand() % 11)+2;
			cout << "You get: " << *pdice;
			delete ptemp;
			return;
		}
		else if (*ptemp == 'r') {
			//delete [] playerName;
			//playerName = nullptr;
			//startNewGame();
		}
		else {
			cout << "Wrong input.";
		}
	} while (true);
}

int main()
{	
	initialLocation();
	//saveNload();
	startNewGame();
	//printMap();
	rollDice();
    return 0;
}

