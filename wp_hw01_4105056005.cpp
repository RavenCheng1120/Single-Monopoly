/******
4105056005	�G�a�x	�Ĥ@���@�~10/9
******/

/*
	�ާ@����:
*/

// wp_hw01_4105056005.cpp : �w�q�D���x���ε{�����i�J�I�C
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

//�]�w��l�ȡCplayerName�O���a�W�١Fpmoney�O���a�����ƶq�Fplocations�O�a�ϤW�U�a�I�W�� : pdice�O��l�I�ơC
char* playerName = new char[40];
int* pmoney = new int;
const char** plocations = new const char*[28];
int* pdice = new int;

//�]�w�U�a�a�W
void initialLocation() {
	*(plocations) = "Start ->";
	*(plocations + 1) = "01�x�_";
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

//��J���a�W��
void startNewGame() {
	cout << "Welcome to the Mini Monopoly Game.\n" << endl;
	cout << "�C������:\n    ���C���}�l���B��1500���A�C���g�L�_�I�N��o300���C" << endl;
	cout << "    �C����ʥi����Y��l(d)�άO���s�}�l��ӹC��(r)�C" << endl;
	cout << "    ��W�a�W����ɡA�i�H�M�w�O�_�ʶR�Ĥ@�ɩФl�A�άO�~��[�\�ЫΡC�Y����w�g���Ӫ��a�\���Фl�A" <<
			"�h�i��o�л�1.5�������C" << endl;
	cout << "    �����|�ΩR�B����A�t�αN�۰ʩ�P�A�ð���P�W�����O�C" << endl;
	cout << "\nPlease input player's name: ";
	cin.get(playerName, 39);
	cout << "Hello, " << playerName << ". Now you have $1500 in your bank. Enjoy the game:)"<< endl << endl;
	*pmoney = 1500;
	return;
}

//�L�X�j�I�Φa��
void printMap() {
	int* pi = new int;
	int* pj = new int;
	int* pfront = new int;
	int* pback = new int;
	*pfront = 1;
	*pback = 29;
	//��u
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//�@9��9x5�p��l�A���k2��13x5�j��l
	for (*pj = 0; *pj < 5; (*pj)++) {
		//�L�X�a�W
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
	//��u
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//���k2��13x4�j��l�A�T��
	for (*pi = 0; *pi < 3; (*pi)++) {
		for (*pj = 0; *pj < 3; (*pj)++) {
			//�L�X�a�W
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
		//�L�X�a�W
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
	//��u
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	//�@9��9x5�p��l�A���k2��13x5�j��l
	for (*pj = 0; *pj < 5; (*pj)++) {
		//�L�X�a�W
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
	//��u
	for (*pi = 0; *pi < 120; (*pi)++) {
		cout << '-';
	}
	delete pi, pj;
	return;
}

//�x�s�θ��J�C����r�ɮ�
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

//�üƻ��l�A�q2��12�I
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

