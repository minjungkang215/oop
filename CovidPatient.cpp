/* Citation and Sources...
Final Project Milestone 4
Module: CovidPatient
Filename: CovidPatient.cpp
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

#include "CovidPatient.h"
using namespace std;
namespace sdds {
	int nextCovidTicket = 1;

	CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
		nextCovidTicket++;
	}

	char CovidPatient::type() const {
		return 'C';
	}

	ostream& CovidPatient::csvWrite(ostream& ostr) const {
		return Patient::csvWrite(ostr);
	}

	istream& CovidPatient::csvRead(istream& istr) {
		Patient::csvRead(istr);
		nextCovidTicket = number() + 1;
		return istr;
	}

	ostream& CovidPatient::write(ostream& ostr) const {
		if (Patient::fileIO()) {
			csvWrite(ostr);
		}
		else {
			ostr << "COVID TEST" << endl;
			Patient::write(ostr) << endl;
		}
		return ostr;
	}	

	istream& CovidPatient::read(istream& istr) {
		Patient::fileIO() ? csvRead(istr) : Patient::read(istr);
		return istr;
	}
}