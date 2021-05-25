/* Citation and Sources...
Final Project Milestone 3
Module: Patient
Filename: Patient.h
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
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
namespace sdds {
	class Patient :public IOAble {
		char* m_patientName{};
		int m_ohipNum{};
		Ticket m_ticket;
		bool m_ioFlag;
	public:
		Patient(int ticketNum = 0, bool ioFlag = false);
		Patient(const Patient& P) = delete;
		Patient& operator=(const Patient& P) = delete;
		~Patient();
		virtual char type()const = 0;
		bool fileIO()const;
		bool fileIO(bool ioFlag);
		bool operator==(const char c)const;
		bool operator==(const Patient& P)const;
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}
#endif // !SDDS_PATIENT_H_


