// Dawid Bartosiak


#include <iostream>
#include <algorithm>
#include "Bank.h"

Bank::Bank(const double& aInterestRate) {
	if (aInterestRate < 0 )
	{ throw std::out_of_range("Interest rate cannot be negative."); }
	else { interestRate = aInterestRate; }
}


FixedInstallmentLoan Bank::give_loan_fixed(Person* person, const int& amount, const int& ratesAmount, const int& ratesInYear, const double& creditworthiness){
	if (amount <= 0 || ratesAmount <= 0 || ratesInYear <= 0 )
	{ throw std::out_of_range("Any of loan parameter cannot be negative."); }
	FixedInstallmentLoan loan = FixedInstallmentLoan(amount, interestRate, ratesAmount, ratesInYear, creditworthiness);
	if (std::find(people.begin(), people.end(), person) != people.end()) { return loan; }
	else {
		people.push_back(person);
		return loan;
	}
}


DescendingInstallmentLoan Bank::give_loan_descending(Person* person, const int& amount, const int& ratesAmount, const int& ratesInYear, const double& creditworthiness) {
	if (amount <= 0 || ratesAmount <= 0 || ratesInYear <= 0)
	{ throw std::out_of_range("Any of loan parameter cannot be negative.");  }
	DescendingInstallmentLoan loan = DescendingInstallmentLoan(amount, interestRate, ratesAmount, ratesInYear, creditworthiness);
	if (std::find(people.begin(), people.end(), person) != people.end()) { return loan; }
	else {
		people.push_back(person);
		return loan;
	}
}

void Bank::overpay_descending( DescendingInstallmentLoan& loan, const double& amount) {
	if (amount <= 0)
	{ throw std::out_of_range("You can't overpay negative amount of money."); }
	else{ loan.overpay(amount); }
}


void Bank::overpay_fixed( FixedInstallmentLoan& loan, const double& amount) {
	if (amount <= 0)
	{ throw std::out_of_range("You can't overpay negative amount of money."); }
	else { loan.overpay(amount); }
}


double Bank::get_interest_rate() { return interestRate; }


void Bank::set_interest_rate(const double& newInterestRate) {
	if (newInterestRate < 0)
	{ throw std::out_of_range("Interest rate cannot be negative."); }
	else {
		interestRate = newInterestRate;
		for (unsigned int i = 0; i <= size(people) - 1; ++i) {
			if (size((*people.at(i)).get_fixed()) != 0) {
				for (unsigned int j = 0; j <= size((*people.at(i)).get_fixed()) - 1; ++j) {
					(*people.at(i)).get_fixed().at(j).set_interest_rates(interestRate);
				}
				if (size((*people.at(i)).get_descending()) != 0) {
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
}


double Bank::get_descending_loan_negative_creditworthiness(DescendingInstallmentLoan& loan) {
	return loan.negativeCreditworthiness;
}


double Bank::get_fixed_loan_negative_creditworthiness(FixedInstallmentLoan& loan) {
	return loan.negativeCreditworthiness;
}