/******
4105056005	鄭筠庭	第一次作業10/9
******/

// wp_hw01_4105056005.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <iomanip>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::ios;
using std::ofstream;
using std::fstream;
using std::ifstream;
using std::string;
using std::istringstream;

//設定初始值。pplayerName是玩家名稱；pmoney是玩家金錢數量；plocations是地圖上各地點名稱 : pdice是骰子點數 ; plocaMon是地點價格；
//phouses是紀錄購買房子；pposition是紀錄玩家目前位置;preturn是重新開始時使用的變數;pnoTax是一張機會卡;pround是記錄第幾回合。
string* pplayerName = new string;
int* pmoney = new int;
const char** plocations = new const char*[30];
int* pdice = new int;
int* plocaMon = new int[30];
int* phouses = new int[30];
int* pposition = new int;
int* preturn = new int;
int* pnoTax = new int;
int* pround = new int;

//設定各地地名和價錢，各地設為0棟房子
void initialLocation() {
	plocations = new const char*[30];
	plocaMon = new int[30];
	phouses = new int[30];
	*(plocations) = "Start ->";
	*(plocations + 1) = "01中二丼";
	*(plocations + 2) = "02日新";
	*(plocations + 3) = "03玩麵";
	*(plocations + 4) = "04聞香";
	*(plocations + 5) = "05小慢慢";
	*(plocations + 6) = "-機會-";
	*(plocations + 7) = "07珍餚";
	*(plocations + 8) = "08老虎麵";
	*(plocations + 9) = "09五十嵐";
	*(plocations + 10) = "$抽稅";
	*(plocations + 11) = "11中興炒飯";
	*(plocations + 12) = "12八方雲集";
	*(plocations + 13) = "13Subway";
	*(plocations + 14) = "14烤肉飯";
	*(plocations + 15) = "15屋馬";
	*(plocations + 16) = "16餃佼者";
	*(plocations + 17) = "-命運-";
	*(plocations + 18) = "18小木屋";
	*(plocations + 19) = "19麥當勞";
	*(plocations + 20) = "20弘爺";
	*(plocations + 21) = "21昌平";
	*(plocations + 22) = "22櫻木";
	*(plocations + 23) = "23全家";
	*(plocations + 24) = "24蛋包飯";
	*(plocations + 25) = "$抽稅";
	*(plocations + 26) = "26清一色";
	*(plocations + 27) = "27御燒";
	*(plocations + 28) = "28青";
	*(plocations + 29) = "29香草藍舍";

	*(plocaMon) = 0;
	*(plocaMon + 1) = 100;
	*(plocaMon + 2) = 60;
	*(plocaMon + 3) = 140;
	*(plocaMon + 4) = 80;
	*(plocaMon + 5) = 110;
	*(plocaMon + 6) = 0;
	*(plocaMon + 7) = 100;
	*(plocaMon + 8) = 150;
	*(plocaMon + 9) = 160;
	*(plocaMon + 10) = 200;
	*(plocaMon + 11) = 200;
	*(plocaMon + 12) = 150;
	*(plocaMon + 13) = 250;
	*(plocaMon + 14) = 180;
	*(plocaMon + 15) = 420;
	*(plocaMon + 16) = 170;
	*(plocaMon + 17) = 0;
	*(plocaMon + 18) = 220;
	*(plocaMon + 19) = 250;
	*(plocaMon + 20) = 160;
	*(plocaMon + 21) = 200;
	*(plocaMon + 22) = 180;
	*(plocaMon + 23) = 230;
	*(plocaMon + 24) = 300;
	*(plocaMon + 25) = 200;
	*(plocaMon + 26) = 350;
	*(plocaMon + 27) = 320;
	*(plocaMon + 28) = 160;
	*(plocaMon + 29) = 380;

	int* pi = new int;
	for (*pi = 0; *pi < 30; (*pi)++) 
		*(phouses + (*pi)) = 0;
	delete pi;

	pposition = new int;
	*pposition = 0;

	pnoTax = new int;
	*pnoTax = 0;

	pround = new int;
	*pround = 0;

	return;
}

//儲存遊戲
void storetxt() {
	int* pi = new int;
	fstream saveFile;
	saveFile.open("Save.txt", ios::out | ios::app);
	if (saveFile.is_open()) {
		saveFile << "\n\n-Save file NO." << *pround << "-" << endl;
		saveFile << "Player's name:" << *pplayerName << endl;
		saveFile << "Player's money:" << *pmoney << endl;
		saveFile << "Cost of each place from 00 to 29:";
		for (*pi = 0; *pi < 30; (*pi)++)
			saveFile << *(plocaMon + (*pi)) << "/";
		saveFile << endl;
		saveFile << "Number of houses on each place from 00 to 29:";
		for (*pi = 0; *pi < 30; (*pi)++)
			saveFile << *(phouses + (*pi)) << "/";
		saveFile << endl;
		saveFile << "Player location:" << *pposition << endl;
		saveFile << "Number of NoTax card:" << *pnoTax;
		(*pround)++;
		saveFile.close();
		cout << "儲存成功。" << endl;
	}
	delete pi;
	return;
}

//載入遊戲文字檔案
void loadtxt() {
	int* pi = new int;
	ifstream loadFile;
	loadFile.open("Save.txt", ifstream::in);
	if (loadFile.is_open()) {
		//取得最後六行的字串，是最新的存檔紀錄
		loadFile.seekg(-1, ios::end);
		int* pkeepLooping = new int;
		*pkeepLooping = 1;
		for (*pi = 0; *pi < 6; (*pi)++) {
			*pkeepLooping = 1;
			while (*pkeepLooping) {
				char* ch = new char;
				loadFile.get(*ch);

				if ((int)loadFile.tellg() <= 1) {             // If the data was at or before the 0th byte
					loadFile.seekg(0);                       // The first line is the last line
					*pkeepLooping = 0;
				}
				else if (*ch == '\n') {
					*pkeepLooping = 0;
				}
				else {
					loadFile.seekg(-2, ios::cur);        // Move to the front of that data, then to the front of the data before it
				}
			}
			string* lastLine = new string;
			getline(loadFile, *lastLine);

			//取得冒號後面的數據
			int* len = new int;
			*len = (*lastLine).find(":");
			int* pcount = new int;
			*pcount	= (int)(*lastLine).length();
			(*lastLine) = (*lastLine).erase(0, *len + 1);
			//cout << "Result: " << *lastLine << '\n';

			//最後一行是noTax卡牌
			if (*pi == 0) {
				istringstream is(*lastLine);
				is >> *pnoTax;
			}
			//倒數第二行是玩家位置
			if (*pi == 1) {
				istringstream is(*lastLine);
				is >> *pposition;
			}
			//倒數第三行是各區房屋數
			if (*pi == 2) {
				string* first = new string;
				int* pk = new int;
				for (*pk = 0; *pk < 30; (*pk)++) {
					*len = (*lastLine).find("/");
					*first = (*lastLine).substr(0, *len);
					(*lastLine) = (*lastLine).erase(0, *len + 1);
					istringstream is(*first);
					is >> *(phouses+(*pk));
				}
				delete first, pk;
			}
			//倒數第四行是各區價錢
			if (*pi == 3) {
				string* first = new string;
				int* pk = new int;
				for (*pk = 0; *pk < 30; (*pk)++) {
					*len = (*lastLine).find("/");
					*first = (*lastLine).substr(0, *len);
					(*lastLine) = (*lastLine).erase(0, *len + 1);
					istringstream is(*first);
					is >> *(plocaMon + (*pk));
				}
				delete first, pk;
			}
			//倒數第五行是玩家金錢
			if (*pi == 4) {
				istringstream is(*lastLine);
				is >> *pmoney;
			}
			//倒數第六行是玩家名稱
			if (*pi == 5) {
				*pplayerName = *lastLine;
			}

			loadFile.seekg(-((*pcount)+5), ios::cur);
			delete lastLine, len, pcount;
		}
		cout << "讀檔成功" << endl << endl;
		loadFile.close();
	}
	delete pi;
	return;
}

//輸入玩家名稱
void startNewGame() {
	initialLocation();
	cout << setw(70) << "-Welcome to the Mini Monopoly Game-" << endl << endl;
	cout << "遊戲說明:\n    此遊戲開始金額建議為1000元，每次經過起點將獲得300元。" << endl;
	cout << "    每次行動可選擇擲骰子(d)或是重新開始整個遊戲(r)。地圖上@代表玩家位置。" << endl;
	cout << "    踩上地名方塊時，可以決定是否購買房子，或是繼續升級房屋，一塊土地最多升到5級房子。若方塊已經有該玩家蓋的房子，" <<
			"則可獲得房價1.5倍的錢。" << endl;
	cout << "    踩到機會及命運方塊，系統將自動抽牌，並執行牌上的指令。" << endl;
	cout << "    踩到抽稅方塊，玩家將減少200元。若擁有逃稅卡牌將會自動使用。" << endl << endl;

	cout << "你想要載入上一次的遊玩紀錄嗎? 打入load即可載入，若不要請按 n :";
	char* ptemp = new char[20];
	cin.getline(ptemp, 20);
	if (*ptemp == 'l' && *(ptemp + 1) == 'o' && *(ptemp + 2) == 'a' && *(ptemp + 3) == 'd' && *(ptemp + 4) == '\0') {
		loadtxt();
		delete ptemp;
		return;
	}

	cout << "\n請輸入玩家英文名字: ";
	//playerName = new char[40];
	pplayerName = new string;
	getline(cin, *pplayerName);
	//cin.getline(playerName, 39);
	cout << "你好, " << *pplayerName << "，祝福你遊玩愉快。請輸入起始金額(建議1000元):";
	pmoney = new int;
	do {
		cin >> *pmoney;
		cin.get();
		if (*pmoney <= 1000000 && *pmoney > 0)
			break;
		else
			cout << "不要輸入負數或是超過一百萬，請重新輸入:";
	} while (1);
	
	return;
}

//印出大富翁地圖
void printMap() {
	int* pi = new int;
	int* pj = new int;
	int* pfront = new int;
	int* pback = new int;
	*pfront = 0;
	*pback = 29;
	//橫線
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//共9個9x5小格子，左右2個13x5大格子
	for (*pj = 0; *pj < 5; (*pj)++) {
		//印出房子
		if (*pj == 1) {
			if(*(phouses + (*pfront)) > 0)
				cout << "|    " << "[@:" << *(phouses + (*pfront)) << "級屋]";
			else
				cout << "|             ";
			(*pfront)++;
			for (*pi = 0; *pi < 9; (*pi)++) {
				if (*(phouses + (*pfront)) > 0)
					cout << "|[@:" << *(phouses + (*pfront)) << "級屋]";
				else
					cout << "|         ";
				(*pfront)++;
			}
			if (*(phouses + (*pfront)) > 0)
				cout << "|    " << "[@:" << *(phouses + (*pfront)) << "級屋]| ";
			else
				cout << "|             | ";
			(*pfront)++;
		}
		//印出地名
		else if (*pj == 2) {
			*pfront = 0;
			cout << "|" << setw(13) << *(plocations + (*pfront));
			(*pfront)++;
			for (*pi = 0; *pi < 9; (*pi)++) {
				cout << "|" << setw(9) << *(plocations+(*pfront));
				(*pfront)++;
			}
			cout << "|" << setw(13) << *(plocations + (*pfront)) << "| ";
			(*pfront)++;
		}
		//印出價錢和玩家位置
		else if (*pj == 3) {
			*pfront = 1;
			if (*pposition == (*pfront)-1)
				cout << "|@            ";
			else
				cout << "|             ";
			for (*pi = 0; *pi < 9; (*pi)++) {
				if (*pi == 5) {
					if(*pposition == *pfront)
						cout << "|@        ";
					else
						cout << "|         ";
				}
				else {
					if (*pposition == *pfront)
						cout << "|" << setw(1) << '@' << setw(8) << *(plocaMon + (*pfront));
					else
						cout << "|" << setw(9) << *(plocaMon + (*pfront));
				}
				(*pfront)++;
			}
			if (*pposition == *pfront)
				cout << "|@            | ";
			else
				cout << "|             | ";
			(*pfront)++;
		}
		//沒有文字的行
		else {
			cout << "|             ";
			for (*pi = 0; *pi < 9; (*pi)++) 
				cout << "|         ";
			cout << "|             | ";
		}
	}
	//橫線
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//左右2個13x4大格子，三排
	for (*pi = 0; *pi < 4; (*pi)++) {
		for (*pj = 0; *pj < 3; (*pj)++) {
			//印出房屋
			if (*pj == 0) {
				if(*(phouses + (*pback)) > 0)
					cout << "|" << setw(7) << "[@:" << *(phouses + (*pback)) << "級屋]" << "|                                             ";
				else
					cout << "|             |                                             ";
				if (*(phouses + (*pfront)) > 0)
					cout << "                                            |" << setw(7) << "[@:" << *(phouses + (*pfront)) << "級屋]" << "| ";
				else
					cout << "                                            |             | ";
			}
			//印出地名
			else if (*pj == 1) {
				cout << "|" << setw(13) << *(plocations + (*pback)) << "|                                             ";
				cout << "                                            |" << setw(13) << *(plocations + (*pfront)) <<"| ";
			}
			//印出價錢和玩家位置
			else if (*pj == 2) {
				if (*pposition == *pback)
					cout << "|" << setw(1) << '@' << setw(12) << *(plocaMon + (*pback)) << "|                                             ";
				else
					cout << "|" << setw(13) << *(plocaMon + (*pback)) << "|                                             ";
				if (*pposition == *pfront)
					cout << "                                            |" << setw(1) << '@' << setw(12) << *(plocaMon + (*pfront)) << "| ";
				else
					cout << "                                            |" << setw(13) << *(plocaMon + (*pfront)) << "| ";
				(*pfront)++;
				(*pback)--;
			}
			else {
				cout << "|             |                                             ";
				cout << "                                            |             | ";
			}
		}
		//印出一行玩家手上金錢數
		if (*pi == 3) {
			cout << "|             |             " << setw(22) << *pplayerName << setw(10) << "的金錢數: " << setw(9) << *pmoney;
			cout << "                                   |             | ";
		}
		else {
			cout << "--------------                                                  ";
			cout << "                                        --------------- ";
		}
	}
	//橫線
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//共9個9x5小格子，左右2個13x5大格子
	for (*pj = 0; *pj < 5; (*pj)++) {
		//印出房子
		if (*pj == 1) {
			if(*(phouses + (*pback)) > 0)
				cout << "|    " << "[@:" << *(phouses + (*pback)) << "級屋]";
			else
				cout << "|             ";
			(*pback)--;
			for (*pi = 0; *pi < 9; (*pi)++) {
				if (*(phouses + (*pback)) > 0)
					cout << "|[@:" << *(phouses + (*pback)) << "級屋]";
				else
					cout << "|         ";
				(*pback)--;
			}
			if (*(phouses + (*pback)) > 0)
				cout << "|    " << "[@:" << *(phouses + (*pback)) << "級屋]| ";
			else
				cout << "|             | ";
		}
		//印出地名
		else if (*pj == 2) {
			*pback = 25;
			cout << "|" << setw(13) << *(plocations + (*pback));
			(*pback)--;
			for (*pi = 0; *pi < 9; (*pi)++) {
				cout << "|" << setw(9) << *(plocations + (*pback));
				(*pback)--;
			}
			cout << "|" << setw(13) << *(plocations + (*pback)) << "| ";
			(*pback)--;
		}
		//印出價錢和玩家位置
		else if (*pj == 3) {
			*pback = 25;
			if(*pposition == *pback)
				cout << "|@            ";
			else
				cout << "|             ";
			(*pback)--;
			for (*pi = 0; *pi < 9; (*pi)++) {
				if (*pi == 7) {
					if (*pposition == *pback)
						cout << "|@        ";
					else
						cout << "|         ";
				}
				else {
					if (*pposition == *pback)
						cout << "|" << setw(1) << '@' << setw(8) << *(plocaMon + (*pback));
					else
						cout << "|" << setw(9) << *(plocaMon + (*pback));
				}
				(*pback)--;
			}
			if (*pposition == *pback)
				cout << "|@" << setw(12) << *(plocaMon + (*pback)) << "| ";
			else
				cout << "|" << setw(13) << *(plocaMon + (*pback)) << "| ";
			(*pback)--;
		}
		//沒有文字的行
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

//亂數骰骰子，從2到12點；重新進行遊戲；load或是store檔案
int* rollDice() {
	char* ptemp = new char[20];
	preturn = new int;
	do {
		cout << "按下 d 擲骰子，按下 r 將重新開始遊戲，打入load可載入舊遊戲檔，打入store可存檔: ";
		cin.getline(ptemp, 20);
		if (*ptemp == 'd' && *(ptemp + 1) == '\0') {
			srand(time(NULL));
			pdice = new int;
			*pdice = (rand() % 11) + 2;
			cout << "登登愣~你共擲出了 " << *pdice << " 點。 " << endl;
			delete[] ptemp;
			*preturn = 0;
			return preturn;
		}
		else if (*ptemp == 'r' &&  *(ptemp + 1) == '\0') {
			delete pplayerName;
			delete pposition;
			delete pmoney;
			delete plocations;
			delete[] plocaMon;
			delete[] phouses;
			delete pnoTax;
			delete pround;
			*preturn = 1;
			return preturn;
		}
		else if (*ptemp == 'l' && *(ptemp + 1) == 'o' && *(ptemp + 2) == 'a' && *(ptemp + 3) == 'd' && *(ptemp + 4) == '\0') {
			loadtxt();
			printMap();
		}
		else if (*ptemp == 's' && *(ptemp + 1) == 't' && *(ptemp + 2) == 'o' && *(ptemp + 3) == 'r' && *(ptemp + 4) == 'e' && *(ptemp + 5) == '\0')
			storetxt();
		else {
			cout << "輸入錯誤。" << endl;
		}
	} while (true);
}

//機會命運
void chance() {
	int* ptemp = new int;
	srand(time(NULL));
	*ptemp = rand() % 5;
	switch (*ptemp) {
		case 0:
			cout << "掉進水溝，身上的200塊被沖走了。" << endl;
			*pmoney -= 200;
			break;
		case 1:
			cout << "被捲進黑幫鬥毆，重傷住院，花700元治療費。" << endl;
			*pmoney -= 700;
			break;
		case 2:
			cout << "得到逃稅大師的親自指點，獲得一本逃稅密籍。(可以少繳一次稅)" << endl;
			(*pnoTax)++;
			break;
		case 3:
			cout << "在衣櫃找到阿罵的大衣，口袋裡有500元，偷偷把錢抽走吧。" << endl;
			*pmoney += 500;
			break;
		case 4:
			cout << "把珍藏的美國隊長海報拿去賣掉，賺了350元。" << endl;
			*pmoney += 350;
			break;
		default:
			cout << "Error." << endl;
	}
	delete ptemp;
	return;
}

//遊戲主要架構
void gameLoop() {
	while (true) {
		char* pYN = new char[20];
		char* pbroke = new char[20];
		printMap();
		if (*rollDice() == 1)
			break;
		delete preturn;
		*pposition += *pdice;
		delete pdice;
		if (*pposition >= 30) {
			*pposition -= 30;
			cout << "經過起點，很高興你能活著回來，送你300元獎勵。" << endl;
			*pmoney += 300;
		}
		cout << "前往[ " << *(plocations + (*pposition)) << " ]方塊。" << endl;
		//到達機會方塊
		if (*pposition == 6) {
			cout << "危機就是轉機! 親愛的玩家，抽取一張機會牌...(按下ENTER)";
			cin.get();
			chance();
		}
		//到達命運方塊
		else if (*pposition == 17) {
			cout << "你到達了命運女神的殿堂，她將賜予你一張命運牌...(按下ENTER)";
			cin.get();
			chance();
		}
		//到達抽稅方塊
		else if (*pposition == 10 || *pposition == 25) {
			cout << "真倒楣，是收稅時間!!! 請上繳200塊給系統。(按下ENTER)";
			cin.get();
			if (*pnoTax > 0) {
				cout << "使用逃稅密籍!!!我就是死不繳稅三十六式!" << endl;
				(*pnoTax)--;
			}
			else
				*pmoney -= 200;
		}
		//到達起點
		else if (*pposition == 0) {
			continue;
		}
		//到達可購買的方塊
		else {
			//土地到達五級房子
			if (*(phouses + (*pposition)) >= 5) {
				*(plocaMon + (*pposition)) = (int)*(plocaMon + (*pposition)) / 2;
				cout << "此地點已是五級房子，到達土地上限，無法再蓋房子。收取租金，獲得" << (int)*(plocaMon + (*pposition))*1.5 << "元。" << endl;
				*pmoney += (int)*(plocaMon + (*pposition))*1.5;
			}
			//如果還未買過房子
			else if (*(phouses + (*pposition)) == 0) {	
				cout << "請問要購買[ " << *(plocations + (*pposition)) << " ]的房子嗎? ";
				cout << "此地房子要" << *(plocaMon + (*pposition)) << "元。(y/n) ";
				do{	
					cin.getline(pYN, 20);
					if (*pYN == 'y' && *(pYN+1) == '\0') {
						*pmoney -= *(plocaMon + (*pposition));
						*(phouses + (*pposition)) = 1;
						*(plocaMon + (*pposition)) = *(plocaMon + (*pposition)) * 2;
						cout << "購買了[" << *(plocations + (*pposition)) << "]的房子。 此地點蓋上 1 級房屋。" << endl;
						delete pYN;
						break;
					}
					else if (*pYN == 'n' && *(pYN + 1) == '\0') {
						cout << "拒絕購買房子，遊戲繼續。" << endl;
						delete pYN;
						break;
					}
					else 
						cout << "輸入錯誤，請重新輸入(y/n):";
				}while (true);
				
			}
			//買過房子
			else {
				cout << "你在此地已經有" << *(phouses + (*pposition)) << "級房子。收取租金，獲得" << (int)*(plocaMon + (*pposition))/2*1.5 << "元。" << endl;
				*pmoney += (int)*(plocaMon + (*pposition))/2*1.5;
				cout << "請問要升級[ " << *(plocations + (*pposition)) << " ]的房子嗎? ";
				cout << "升級房子要" << *(plocaMon + (*pposition)) << "元。(y/n) ";
				do {
					cin.getline(pYN, 20);
					if (*pYN == 'y' && *(pYN + 1) == '\0') {
						*pmoney -= *(plocaMon + (*pposition));
						*(phouses + (*pposition)) += 1;
						cout << "升級[" << *(plocations + (*pposition)) << "]的房子。 此地點已是" << *(phouses + (*pposition)) << "級房子。" << endl;
						delete pYN;
						break;
					}
					else if(*pYN == 'n' && *(pYN + 1) == '\0'){
						cout << "拒絕升級房子，遊戲繼續。" << endl;
						delete pYN;
						break;
					}
					else
						cout << "輸入錯誤，請重新輸入(y/n):";
				} while (true);
			}
		}
		//破產
		if (*pmoney <= 0) {
			cout << "\n你破產了!!!!!!!!!送你一把人生重來槍，要重新開始遊戲嗎?(按r重新開始)";
			do {
				cin.get(pbroke, 20);
				cin.get();
				if (*pbroke == 'r' && (*pbroke+1) == '\0') {
					delete pplayerName;
					delete pposition;
					delete pmoney;
					delete plocations;
					delete[] plocaMon;
					delete[] phouses;
					delete pnoTax;
					delete pbroke;
					return;
				}
				else 
					cout << "輸入錯誤。" << endl;
			} while (1);
		}
		//自動存檔
		//storetxt();
	}
	return;
}

int main()
{	
	while (true) {
		startNewGame();
		// storetxt();
		gameLoop();
	}
    return 0;
}

