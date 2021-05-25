/* Citation and Sources...
Final Project Milestone 5
Module: PreTriage
Filename: PreTriage.cpp
Version 1.0
Author	Minjung Kang
Revision History
-----------------------------------------------------------
Date      Reason
2020/12/04  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "PreTriage.h"
#include "Time.h"
#include "utils.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
using namespace std;
namespace sdds {

	PreTriage::PreTriage(const char* dataFilename) :
		m_averCovidWait(15), m_averTriageWait(5),
		m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
		m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage() {
		ofstream fout;
		fout.open(m_dataFilename);
		fout << m_averCovidWait << "," << m_averTriageWait << endl;
		cout << "Saving Average Wait Times," << endl
			<< "   COVID Test: " << m_averCovidWait << endl
			<< "   Triage: " << m_averTriageWait << endl
			<< "Saving m_lineup..." << endl;
		for (int i = 0; i < m_lineupSize; i++) {
			m_lineup[i]->fileIO(true);
			fout << *m_lineup[i] << endl;
			cout << i + 1 << "- ";
			cout << *m_lineup[i] << endl;			
		}
		for (int i = 0; i < m_lineupSize; i++) {
			delete m_lineup[i];
		}
		delete[] m_dataFilename;
		cout << "done!" << endl;
	}

	const Time PreTriage::getWaitTime(const Patient& p) const {
		int count = 0;
		Time t;
		for (int i = 0; i < m_lineupSize; i++) {
			if (*m_lineup[i] == p) {
				count++;
			}
		}
		if (p == 'C') {
			t = m_averCovidWait * count;
		}
		else if (p == 'T') {
			t = m_averTriageWait * count;
		}
		return t;
	}

	void PreTriage::setAverageWaitTime(const Patient& p) {
		Time t;
		if (p == 'C') {
			m_averCovidWait = ((t.reset() - Time(p)) + (m_averCovidWait * (p.number() - 1))) / p.number();
		}
		else if (p == 'T') {
			m_averTriageWait = ((t.reset() - Time(p)) + (m_averTriageWait * (p.number() - 1))) / p.number();
		}
	}

	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const {
		int found = -1;
		for (int i = 0; i < m_lineupSize && found == -1; i++) {
			if (m_lineup[i]->operator==(type)) {
				found = i;
			}
		}
		return found;
	}

	void PreTriage::load() {
		ifstream fin;
		Patient* P{};
		cout << "Loading data..." << endl;
		fin.open(m_dataFilename);
		fin >> m_averCovidWait;
		fin.ignore(2000, ',');
		fin >> m_averTriageWait;
		fin.ignore(2000, '\n');
		for (int i = 0; i < maxNoOfPatients; i++) {
			char ch;
			fin >> ch;
			fin.ignore(2000, ',');
			if (!fin.fail()) {				
				if (ch == 'T') {
					P = new TriagePatient();					
				}
				else if (ch == 'C') {
					P = new CovidPatient();
				}
				if (P) {
					P->fileIO(true);
					fin >> *P;
					P->fileIO(false);
					m_lineup[i] = P;
					m_lineupSize++;
				}
			}
		}
		if (!fin.fail()) {
			cout << "Warning: number of records exceeded 100" << endl;
		}
		if (m_lineupSize) {
			cout << m_lineupSize << " Records imported..." << endl << endl;
		}
		else {
			cout << "No data or bad data file!" << endl << endl;
		}
	}

	void PreTriage::reg() {
		if (m_lineupSize == maxNoOfPatients) {
			cout << "Line up full!" << endl;
		}
		else {
			int selection;
			m_pMenu >> selection;
			if (selection == 1 || selection == 2) {
				if (selection == 1) {
					m_lineup[m_lineupSize] = new CovidPatient();
				}
				else {
					m_lineup[m_lineupSize] = new TriagePatient();
				}
				m_lineup[m_lineupSize]->setArrivalTime();
				cout << "Please enter patient information: " << endl;
				m_lineup[m_lineupSize]->fileIO(false);
				cin >> *m_lineup[m_lineupSize];
				cout << endl << "******************************************" << endl;
				cout << *m_lineup[m_lineupSize];
				cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]);
				cout << endl << "******************************************" << endl << endl;
				m_lineupSize++;
			}
		}
	}

	void PreTriage::admit() {
		int index{};
		int selection;
		m_pMenu >> selection;
		if (selection == 1) {
			index = indexOfFirstInLine('C');
		}
		else if (selection == 2) {
			index = indexOfFirstInLine('T');
		}
		if (index != -1) {
			cout << endl << "******************************************" << endl;
			m_lineup[index]->fileIO(false);
			cout << "Calling for " << *m_lineup[index];
			cout << "******************************************" << endl << endl;
			setAverageWaitTime(*m_lineup[index]);
			removePatientFromLineup(index);
		}
	}

	void PreTriage::run(void) {
		bool terminate = false;
		int selection;
		while (!terminate) {
			m_appMenu >> selection;
			if (selection == 1) {
				reg();
			}
			else if (selection == 2) {
				admit();
			}
			else if (selection == 0) {
				terminate = true;
			}
		}
	}
}