/* Citation and Sources...
Final Project Milestone 3
Module: Patient
Filename: Patient.cpp
Version 1.0
Author	Minjung Kang
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/20  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "Ticket.h"
#include "utils.h"
using namespace std;
namespace sdds {
	Patient::Patient(int ticketNum, bool ioFlag)
		: m_ticket(ticketNum), m_ioFlag(ioFlag) {
	}
	Patient::~Patient() {
		delete[] m_patientName;
	}
	bool Patient::fileIO() const {
		return m_ioFlag;
	}
	bool Patient::fileIO(bool ioFlag) {
		m_ioFlag = ioFlag;
		return m_ioFlag;
	}
	bool Patient::operator==(const char ch) const {
		return type() == ch;
	}
	bool Patient::operator==(const Patient& P) const {
		return type() == P.type();
	}
	void Patient::setArrivalTime() {
		m_ticket.resetTime();
	}
	Patient::operator Time() const {
		return Time(m_ticket);
	}
	int Patient::number() const {
		return m_ticket.number();
	}
	ostream& Patient::csvWrite(ostream& ostr) const {
		ostr << type() << "," << m_patientName << "," << m_ohipNum << ",";
		m_ticket.csvWrite(ostr);
		return ostr;
	}
	istream& Patient::csvRead(istream& istr) {
		delete[] m_patientName;
		char cstr[51];
		istr.get(cstr, 51, ',');
		m_patientName = new char[strlen(cstr) + 1];
		strcpy(m_patientName, cstr);
		istr.ignore(2000, ',');
		istr >> m_ohipNum;
		istr.ignore(2000, ',');
		m_ticket.csvRead(istr);
		return istr;
	}
	ostream& Patient::write(ostream& ostr) const {
		return ostr << m_ticket << endl << m_patientName << ", OHIP: " << m_ohipNum;
	}
	istream& Patient::read(istream& istr) {
		delete[] m_patientName;
		char cstr[51];
		cout << "Name: ";
		istr.get(cstr, 51, '\n');
		m_patientName = new char[strlen(cstr) + 1];
		strcpy(m_patientName, cstr);
		istr.ignore(2000, '\n');
		cout << "OHIP: ";
		istr >> m_ohipNum;
		bool keepGoing = true;
		while (keepGoing) {
			if (m_ohipNum > 100000000 && m_ohipNum < 999999999) {
				istr.clear();
				istr.ignore(2000, '\n');
				keepGoing = false;
			}
			else if (istr.fail()) {
				istr.clear();
				istr.ignore(2000, '\n');
				cout << "Bad integer value, try again: ";
				istr >> m_ohipNum;
			}
			else {
				istr.clear();
				istr.ignore(2000, '\n');
				cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
				istr >> m_ohipNum;
			}
		}
		return istr;
	}
}