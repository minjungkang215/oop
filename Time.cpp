/* Citation and Sources...
Final Project Milestone 1
Module: Time
Filename: Time.cpp
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
#include "Time.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
using namespace std;
namespace sdds {
	Time& Time::reset() {
		m_min = getTime();
		return *this;
	}
	Time::Time(unsigned int min) :m_min(min) {
	}

	ostream& Time::write(ostream& ostr) const {
		int hours = m_min / 60;
		int min = m_min % 60;
		ostr << setw(2) << setfill('0') << hours << ":" << setw(2) << min;
		return ostr;
	}
	istream& Time::read(istream& istr) {
		int hours;
		int min;
		istr >> hours;
		if (istr.get() == ':') {
			istr >> min;
			m_min = hours * 60 + min;
		}
		else {
			istr.setstate(ios::failbit);
		}
		return istr;
	}

	Time::operator int() const {
		return m_min;
	}
	Time& Time::operator*=(int val) {
		m_min *= val;
		return *this;
	}
	Time& Time::operator-=(const Time& D) {
		if (m_min < D.m_min) {
			m_min += 1440;
		}
		m_min -= D.m_min;
		return *this;
	}

	Time Time::operator-(const Time& ROperand) {
		Time LOperand = *this;
		LOperand -= ROperand;
		return LOperand;
	}

	ostream& operator<<(ostream& ostr, const Time& T) {
		T.write(ostr);
		return ostr;
	}
	istream& operator>>(istream& istr, Time& T) {
		T.read(istr);
		return istr;
	}
}