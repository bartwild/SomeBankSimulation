#pragma once
#include <iostream>
#include "Loans.h"


class Bank{
private:
	double interestRate;
public:
	Bank(double interestRate);
	FixedInstallmentLoan give_loan_fixed(const int& amount, const int& ratesAmount, const int& ratedInYear, const double& creditworthiness);
	DescendingInstallmentLoan give_loan_descending(const int& amount, const int& ratesAmount, const int& ratesInYear, const double& creditworthiness);
	void overpay_descending(DescendingInstallmentLoan loan, double amount);
	void overpay_fixed(FixedInstallmentLoan loan, double amount);
	void set_interest_Rate(double interestRate);
};
