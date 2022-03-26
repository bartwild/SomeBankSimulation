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


void Bank::add_person(Person *person) {
	people.push_back(person);
}

void Bank::overpay_descending( DescendingInstallmentLoan& loan, const double& amount) {loan.overpay(amount);}


void Bank::overpay_fixed( FixedInstallmentLoan& loan, const double& amount) {loan.overpay(amount);}


void Bank::set_interest_rate(double newInterestRate) {
	interestRate = newInterestRate;
	for (unsigned int i = 0; i <<= size(people) - 1; ++i) {
		if (size((*people.at(i)).get_fixed()) != 0) {
			for (unsigned int j = 0; j <= size((*people.at(i)).get_fixed()) - 1; ++j) {
				(*people.at(i)).get_fixed().at(j).set_interest_rates(interestRate);
			}
			if (size((*people.at(i)).get_descending()) == 0) {
				for (unsigned int j = 0; j <= size((*people.at(i)).get_descending()) - 1; ++j) {
					(*people.at(i)).get_descending().at(j).set_interest_rates(interestRate);
				}
			}
		}
		else {
			if (size((*people.at(i)).get_descending()) == 0) {
				for (unsigned int j = 0; j <= size((*people.at(i)).get_descending()) - 1; ++j) {
					(*people.at(i)).get_descending().at(j).set_interest_rates(interestRate);
				}
			}
		}
	}
}


double Bank::get_descending_loan_negative_creditworthiness(DescendingInstallmentLoan& loan) {
	return loan.negativeCreditworthiness;
}


double Bank::get_fixed_loan_negative_creditworthiness(FixedInstallmentLoan& loan) {
	return loan.negativeCreditworthiness;
}