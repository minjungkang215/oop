/* Citation and Sources...
Final Project Milestone 4
Module: TriagePatient
Filename: TriagePatient.cpp
Version 1.0
Author	Minjung Kang
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/27  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "TriagePatient.h"
using namespace std;
namespace sdds {
	int nextTriageTicket = 1;

	TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
		nextTriageTicket++;
	}

	TriagePatient::~TriagePatient() {
		delete[] m_symptoms;
	}

	char TriagePatient::type() const {
		return 'T';
	}

	ostream& TriagePatient::csvWrite(ostream& ostr) const {
		return Patient::csvWrite(ostr) << ',' << m_symptoms;
	}

	istream& TriagePatient::csvRead(istream& istr) {
		delete[] m_symptoms;
		Patient::csvRead(istr);
		istr.ignore(2000, ',');
		char cstr[511];
		istr.get(cstr, 511, '\n');
		m_symptoms = new char[strlen(cstr) + 1];
		strcpy(m_symptoms, cstr);
		nextTriageTicket = number() + 1;
		return istr;
	}

	ostream& TriagePatient::write(ostream& ostr) const {
		if (fileIO()) {
			csvWrite(ostr);
		}
		else {
			ostr << "TRIAGE" << endl;
			Patient::write(ostr) << endl;
			ostr << "Symptoms: " << m_symptoms << endl;
		}
		return ostr;
	}

	istream& TriagePatient::read(istream& istr) {
		if (fileIO()) {
			csvRead(istr);
		}
		else {
			delete[] m_symptoms;
			Patient::read(istr);
			cout << "Symptoms: ";
			char cstr[511];
			istr.get(cstr, 511, '\n');
			m_symptoms = new char[strlen(cstr) + 1];
			strcpy(m_symptoms, cstr);
			istr.ignore(2000, '\n');
		}
		return istr;
	}
}