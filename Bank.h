// Dawid Bartosiak
// Class Bank is used for perforrming actions that Person is incapable of.
// Bank stand for central bank which can edit interest rate.
// Through bank person can manage its loan. Bank also calculate creditworthiness and manage it to decide of Person capability for taking loan.


#pragma once
#include <iostream>
#include <vector>
#include "Loans.h"
#include "Person.h"


class Person;


class Bank{
private:
	double interestRate;
	std::vector<Person*> people;
public:
	Bank(const double& interestRate);
	FixedInstallmentLoan give_loan_fixed(Person* person, const int& amount, const int& ratesAmount, const int& ratedInYear, const double& creditworthiness);
	DescendingInstallmentLoan give_loan_descending(Person* person, const int& amount, const int& ratesAmount, const int& ratesInYear, const double& creditworthiness);
	void overpay_descending(DescendingInstallmentLoan& loan, const double& amount);
	void overpay_fixed(FixedInstallmentLoan& loan, const double& amount);
	void set_interest_rate(const double& interestRate);
	double get_interest_rate();
	double get_fixed_loan_negative_creditworthiness(FixedInstallmentLoan& loan);
	double get_descending_loan_negative_creditworthiness(DescendingInstallmentLoan& loan);
};
