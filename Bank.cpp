// Dawid Bartosiak


#include <iostream>
#include <algorithm>
#include "Bank.h"
const int bankCreditworthiness = 99999999;
class Bank;

Bank::Bank(const double& aInterestRate) {
	if (aInterestRate <= 0 )
	{ throw std::out_of_range("Interest rate cannot be negative."); }
	else { interestRate = aInterestRate; }
}

FixedInstallmentLoan BankBranchFixed::give_loan(Bank* bank, Person* person, const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness) {
	if (amount <= 0 || ratesAmount <= 0 || ratesInYear <= 0 )
	{ throw std::out_of_range("Any of loan parameter cannot be negative."); }
	FixedInstallmentLoan loan = FixedInstallmentLoan(Authorisation(), amount, this->interestRate, ratesAmount, ratesInYear, creditworthiness);
	if (std::find(people.begin(), people.end(), person) != people.end()) { return loan; }
	else {
		bank->add_person(Authorisation(), person);
		return loan;
	}
}



double BankBranchFixed::get_interest_rate() const noexcept{
	return interestRate;
}


FixedInstallmentLoan BankBranchFixed::create_loan_fixed(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const {
	if (amount <= 0 || ratesAmount <= 0 || ratesInYear <= 0) {
		throw std::out_of_range("Any of loan parameter cannot be negative.");
	}
	FixedInstallmentLoan loan = FixedInstallmentLoan(Authorisation(), amount, interestRate, ratesAmount, ratesInYear, bankCreditworthiness);
	return loan;
}


DescendingInstallmentLoan BankBranchDescending::give_loan(Bank* bank, Person* person, const double& amount,
	const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness) {
	if (amount <= 0 || ratesAmount <= 0 || ratesInYear <= 0)
	{ throw std::out_of_range("Any of loan parameter cannot be negative.");  }
	DescendingInstallmentLoan loan = DescendingInstallmentLoan(Authorisation(), amount, interestRate, ratesAmount, ratesInYear, creditworthiness);
	if (std::find(people.begin(), people.end(), person) != people.end()) { return loan; }
	else {
		bank->add_person(Authorisation(), person);
		return loan;
	}
}


double BankBranchDescending::get_interest_rate() const noexcept{
	return interestRate;
}


DescendingInstallmentLoan BankBranchDescending::create_loan_descending(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const {
	if (amount <= 0 || ratesAmount <= 0 || ratesInYear <= 0){
		throw std::out_of_range("Any of loan parameter cannot be negative.");
	}
	DescendingInstallmentLoan loan = DescendingInstallmentLoan(Authorisation(), amount, interestRate, ratesAmount, ratesInYear, bankCreditworthiness);
	return loan;
}


void BankBranchDescending::overpay_descending(DescendingInstallmentLoan& loan, const double& amount) {
	if (amount <= 0)
	{ throw std::out_of_range("You can't overpay negative amount of money."); }
	else{ loan.overpay(Authorisation(), amount); }
}


void BankBranchFixed::overpay_fixed(FixedInstallmentLoan& loan, const double& amount) {
	if (amount <= 0)
	{ throw std::out_of_range("You can't overpay negative amount of money."); }
	else { loan.overpay(Authorisation(), amount); }
}


double Bank::get_interest_rate() const noexcept { return interestRate; }


FixedInstallmentLoan Bank::create_loan_fixed(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const {
	BankBranchFixed fixedBranch = BankBranchFixed(interestRate);
	return fixedBranch.create_loan_fixed(amount, ratesAmount, ratesInYear);
}

FixedInstallmentLoan Bank::give_loan_fixed(Person* person, const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness){
	BankBranchFixed fixedBranch = BankBranchFixed(interestRate);
	return fixedBranch.give_loan(this, person, amount, ratesAmount, ratesInYear, creditworthiness);
}

double Bank::get_fixed_loan_negative_creditworthiness(FixedInstallmentLoan& loan) const noexcept {
	BankBranchFixed fixedBranch = BankBranchFixed(interestRate);
	return fixedBranch.get_fixed_loan_negative_creditworthiness(loan);
}

void Bank::overpay_fixed(FixedInstallmentLoan& loan, const double& amount){
	BankBranchFixed fixedBranch = BankBranchFixed(interestRate);
	fixedBranch.overpay_fixed(loan, amount);
}

DescendingInstallmentLoan Bank::create_loan_descending(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const {
	BankBranchDescending descendingBranch = BankBranchDescending(interestRate);
	return descendingBranch.create_loan_descending(amount, ratesAmount, ratesInYear);
}

DescendingInstallmentLoan Bank::give_loan_descending(Person* person, const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness){
	BankBranchDescending descendingBranch = BankBranchDescending(interestRate);
	return descendingBranch.give_loan(this, person, amount, ratesAmount, ratesInYear, creditworthiness);
}

double Bank::get_descending_loan_negative_creditworthiness(DescendingInstallmentLoan& loan) const noexcept {
	BankBranchDescending descendingBranch = BankBranchDescending(interestRate);
	return descendingBranch.get_descending_loan_negative_creditworthiness(loan);
}

void Bank::overpay_descending(DescendingInstallmentLoan& loan, const double& amount) {
	BankBranchDescending descendingBranch = BankBranchDescending(interestRate);
	descendingBranch.overpay_descending(loan, amount);
}

void Bank::add_person(Authorisation, Person* person) noexcept {
	people.push_back(person);
}

Bank::~Bank(){}


void Bank::set_interest_rate(const double& newInterestRate) {
	if (newInterestRate <= 0)
	{ throw std::out_of_range("Interest rate cannot be negative."); }
	else {
		interestRate = newInterestRate;
		for (unsigned int i = 0; i <= size(people) - 1; ++i) {
			Person person = *people.at(i);
			if (size(person.get_fixed()) != 0) {
				for (unsigned int j = 0; j <= size(person.get_fixed()) - 1; ++j) {
					(*people.at(i)).get_fixed().at(j).set_interest_rates(Authorisation(), interestRate);
				}
				if (size(person.get_descending()) != 0) {
					for (unsigned int j = 0; j <= size(person.get_descending()) - 1; ++j) {
						(*people.at(i)).get_descending().at(j).set_interest_rates(Authorisation(), interestRate);
					}
				}
			}
			else {
				if (size(person.get_descending()) != 0) {
					for (unsigned int j = 0; j <= size(person.get_descending()) - 1; ++j) {
						(*people.at(i)).get_descending().at(j).set_interest_rates(Authorisation(), interestRate);
					}
				}
			}
		}
	}
}


double BankBranchDescending::get_descending_loan_negative_creditworthiness(DescendingInstallmentLoan& loan) const noexcept {
	return loan.get_negative_creditworthiness(Authorisation());
}


double BankBranchFixed::get_fixed_loan_negative_creditworthiness(FixedInstallmentLoan& loan) const noexcept {
	return loan.get_negative_creditworthiness(Authorisation());
}