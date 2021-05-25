/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Minjung Kang
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/11  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "utils.h"
#include "Menu.h"
using namespace std;
namespace sdds {
	Menu::Menu(const char* text, int NoOfSelections) {		
		m_text = new char[strlen(text) + 1];
		strcpy(m_text, text);
		m_noOfSel = NoOfSelections;
	}

	Menu::~Menu() {
		delete[] m_text;
	}

	ostream& Menu::display(ostream& ostr) const {
		ostr << m_text << endl << "0- Exit" << endl << "> ";
		return ostr;
	}

	int& Menu::operator>>(int& Selection) {
		int userSelection = -1;
		bool keepGoing = true;
		display();
		cin >> userSelection;
		while (keepGoing) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(2000, '\n');
				cout << "Bad integer value, try again: ";
				cin >> userSelection;
			}
			else if (userSelection < 0 || userSelection > m_noOfSel) {
				cin.clear();
				cin.ignore(2000, '\n');
				cout << "Invalid value enterd, retry[0 <= value <= " << m_noOfSel << "]: ";
				cin >> userSelection;
			}
			else {
				cin.clear();
				cin.ignore(2000, '\n');
				Selection = userSelection;
				keepGoing = false;
			}
		}
		return Selection;
	}

}