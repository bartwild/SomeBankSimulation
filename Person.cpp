#include "Person.h"


std::string FixedInstallment = "fixed";
std::string DescendingInstallment = "descending";


Person::Person(Bank aBank, int aIncome, int aLivingCost) {
	bank = aBank;
	interest = 0.0;
	income = aIncome;
	livingCost = aLivingCost;
	creditworthiness = (income - livingCost) / 2;
}


void Person::get_loan(std::string loanType, int amount, int ratesAmount, int ratesInYear) {
	if (loanType == FixedInstallment) {
		FixedInstallmentLoan loan = bank.give_loan_fixed(amount, ratesAmount, ratesInYear, creditworthiness);
		fixed.push_back(loan);
		creditworthiness -= loan.get_interest();
	}
	else if (loanType == DescendingInstallment) {
		DescendingInstallmentLoan loan = bank.give_loan_descending(amount, ratesAmount, ratesInYear, creditworthiness);
		descending.push_back(loan);
		creditworthiness -= loan.get_interest();
	}
	else throw std::out_of_range("Incorrect loan type.");
}


void Person::overpay(std::string loanType, int numberOfLoan, double amount) {
	if (loanType == FixedInstallment) { bank.overpay_fixed(fixed.at(numberOfLoan), amount); }
	else if (loanType == DescendingInstallment) { bank.overpay_descending(descending.at(numberOfLoan), amount); }
	else throw std::out_of_range("Incorrect loan type.");
}


double Person::get_interest_total() {
	double sum_fixed = 0.0;
	if (size(fixed) != 0) {
		for (int i = 0; i <= size(fixed) - 1; ++i)
			sum_fixed = sum_fixed + fixed.at(i).get_interest();
		double sum_descending = 0.0;
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_interest();
		return sum_fixed + sum_descending;
	}
	else {
		double sum_descending = 0.0;
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_interest();
		return sum_fixed + sum_descending;
	}
}


double Person::get_loan_costs_total() {
	double sum_fixed = 0.0;
	double sum_descending = 0.0;
	if (size(fixed) != 0) {
		for (int i = 0; i <= size(fixed) - 1; ++i)
			sum_fixed = sum_fixed + fixed.at(i).get_loan_costs_total();
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_loan_costs();
		return sum_fixed + sum_descending;
	}
	else {
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_loan_costs();
		return sum_fixed + sum_descending;
	}
}


double Person::get_creditworthiness() {return creditworthiness;}


double Person::get_interest_single(std::string loanType, int numberOfLoan) {
	if (loanType == FixedInstallment) { return fixed.at(numberOfLoan).get_interest(); }
	else if (loanType == DescendingInstallment) { return descending.at(numberOfLoan).get_interest(); }
	else throw std::out_of_range("Incorrect loan type.");
}


int Person::get_rates_amount(std::string loanType, int numberOfLoan) {
	if (loanType == FixedInstallment) { return fixed.at(numberOfLoan).get_rates_amount(); }
	else if (loanType == DescendingInstallment) { return descending.at(numberOfLoan).get_rates_amount(); }
	else throw std::out_of_range("Incorrect loan type.");
}
