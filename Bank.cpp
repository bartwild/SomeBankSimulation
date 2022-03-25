#include <iostream>
#include "Bank.h"


Bank::Bank(double aInterestRate) {
	interestRate = aInterestRate;
}


FixedInstallmentLoan Bank::give_loan_fixed(const int& amount, const int& ratesAmount, const int& ratesInYear, const double& creditworthiness){
	FixedInstallmentLoan loan = FixedInstallmentLoan(amount, interestRate, ratesAmount, ratesInYear, creditworthiness);
	return loan;
}


DescendingInstallmentLoan Bank::give_loan_descending(const int& amount, const int& ratesAmount, const int& ratesInYear, const double& creditworthiness) {
	DescendingInstallmentLoan loan = DescendingInstallmentLoan(amount, interestRate, ratesAmount, ratesInYear, creditworthiness);
	return loan;
}


void Bank::overpay_descending(DescendingInstallmentLoan loan, double amount) {loan.overpay(amount);}


void Bank::overpay_fixed(FixedInstallmentLoan loan, double amount) {loan.overpay(amount);}


void Bank::set_interest_Rate(double newInterestRate) { interestRate = newInterestRate; }
