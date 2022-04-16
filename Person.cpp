// Dawid Bartosiak

#include "Person.h"


const std::string FixedInstallment = "fixed";
const std::string DescendingInstallment = "descending";


Person::Person(Bank* aBank, int aIncome, int aLivingCost){
	if (aIncome < 0 || aLivingCost <= 0)
	{ throw std::out_of_range("Income cannot be negative. Living cost can't be negative or equal 0."); }
	bank = aBank;
	income = aIncome;
	livingCost = aLivingCost;
	creditworthiness = (income - livingCost) / 2;
}


int Person::get_income() { return income; }


int Person::get_living_cost() { return livingCost; }


void Person::set_income(const int& aIncome) {
	if (aIncome < 0)
	{ throw std::out_of_range("Income cannot be negative."); }
	else { income = aIncome; }
}


void Person::set_living_cost(const int& aLivingCost) {
	if (aLivingCost <= 0)
	{ throw std::out_of_range("Living cost can't be negative or equal 0."); }
	else { livingCost = aLivingCost; }
}


void Person::get_loan(std::string loanType, const double& amount, int ratesAmount, int ratesInYear) {
	if (amount <= 0 || ratesAmount <= 0 || ratesInYear <= 0)
	{ throw std::out_of_range("Any of loan parameter cannot be negative."); }
	else {
		if (loanType == FixedInstallment) {
			FixedInstallmentLoan loan = bank->give_loan_fixed(this, amount, ratesAmount, ratesInYear, creditworthiness);
			fixed.push_back(loan);
			creditworthiness -= loan.get_interest();
		}
		else if (loanType == DescendingInstallment) {
			DescendingInstallmentLoan loan = bank->give_loan_descending(this, amount, ratesAmount, ratesInYear, creditworthiness);
			descending.push_back(loan);
			creditworthiness -= loan.get_interest();
		}
		else throw std::out_of_range("Incorrect loan type.");
	}
}


void Person::overpay(std::string loanType, unsigned int numberOfLoan, const double& amount) {
	if (amount <= 0)
	{ throw std::out_of_range("You can't overpay negative amount of money."); }
	else {
		if (loanType == FixedInstallment) {
			if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
			else {
				bank->overpay_fixed(fixed.at(numberOfLoan), amount);
				if (fixed.at(numberOfLoan).get_amount_left() <= 0 || fixed.at(numberOfLoan).get_rates_amount() == 0) {
					creditworthiness += bank->get_fixed_loan_negative_creditworthiness(fixed.at(numberOfLoan));
					fixed.erase(fixed.begin() + numberOfLoan);
				}
			}
		}
		else if (loanType == DescendingInstallment) {
			if (descending.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
			else {
				bank->overpay_descending(descending.at(numberOfLoan), amount);
				if (descending.at(numberOfLoan).get_amount_left() <= 0 || descending.at(numberOfLoan).get_rates_amount() == 0) {
					creditworthiness += bank->get_descending_loan_negative_creditworthiness(descending.at(numberOfLoan));
					descending.erase(descending.begin() + numberOfLoan);
				}
			}
		}
		else throw std::out_of_range("Incorrect loan type.");
	}
}


double Person::get_interest_total() {
	double sum_fixed = 0.0;
	if (size(fixed) != 0) {
		for (unsigned int i = 0; i <= size(fixed) - 1; ++i)
			sum_fixed = sum_fixed + fixed.at(i).get_interest();
		double sum_descending = 0.0;
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_interest();
		return sum_fixed + sum_descending;
	}
	else {
		double sum_descending = 0.0;
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_interest();
		return sum_fixed + sum_descending;
	}
}


double Person::get_loan_costs_total() {
	double sum_fixed = 0.0;
	double sum_descending = 0.0;
	if (size(fixed) != 0) {
		for (unsigned int i = 0; i <= size(fixed) - 1; ++i)
			sum_fixed = sum_fixed + fixed.at(i).get_loan_costs_total();
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_loan_costs_total();
		return sum_fixed + sum_descending;
	}
	else {
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_loan_costs_total();
		return sum_fixed + sum_descending;
	}
}


double Person::get_amount_total_left() {
	double sum_fixed = 0.0;
	double sum_descending = 0.0;
	if (size(fixed) != 0) {
		for (unsigned int i = 0; i <= size(fixed) - 1; ++i)
			sum_fixed = sum_fixed + fixed.at(i).get_amount_left();
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_amount_left();
		return sum_fixed + sum_descending;
	}
	else {
		if (size(descending) == 0) { return sum_fixed + sum_descending; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i)
			sum_fixed = sum_fixed + descending.at(i).get_amount_left();
		return sum_fixed + sum_descending;
	}
}


double Person::get_creditworthiness() {return creditworthiness;}


double Person::get_interest_single(std::string loanType, unsigned int numberOfLoan) {
	if (loanType == FixedInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return fixed.at(numberOfLoan).get_interest(); }
	}
	else if (loanType == DescendingInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return descending.at(numberOfLoan).get_interest(); }
	}
	else throw std::out_of_range("Incorrect loan type.");
}


int Person::get_rates_amount(std::string loanType, unsigned int numberOfLoan) {
	if (loanType == FixedInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return fixed.at(numberOfLoan).get_rates_amount(); }
	}
	else if (loanType == DescendingInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return descending.at(numberOfLoan).get_rates_amount(); }
	}
	else throw std::out_of_range("Incorrect loan type.");
}


double Person::get_negative_creditworthines(std::string loanType, unsigned int numberOfLoan) {
	if (loanType == FixedInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return bank->get_fixed_loan_negative_creditworthiness(fixed.at(numberOfLoan)); }
	}
	else if (loanType == DescendingInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return bank->get_descending_loan_negative_creditworthiness(descending.at(numberOfLoan)); }
	}
	else throw std::out_of_range("Incorrect loan type.");
}


double Person::get_loan_costs_single(std::string loanType, unsigned int numberOfLoan) {
	if (loanType == FixedInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return fixed.at(numberOfLoan).get_loan_costs_total(); }
	}
	else if (loanType == DescendingInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return descending.at(numberOfLoan).get_loan_costs_total(); }
	}
	else throw std::out_of_range("Incorrect loan type.");
}


double Person::get_amount_single_left(std::string loanType, unsigned int numberOfLoan) {
	if (loanType == FixedInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return fixed.at(numberOfLoan).get_amount_left(); }
	}
	else if (loanType == DescendingInstallment) {
		if (fixed.size() <= numberOfLoan) { throw std::out_of_range("Invalid vector subscript."); }
		else { return descending.at(numberOfLoan).get_amount_left(); }
	}
	else throw std::out_of_range("Incorrect loan type.");
}


std::vector<DescendingInstallmentLoan>& Person::get_descending() { return descending; }


std::vector<FixedInstallmentLoan>& Person::get_fixed() { return fixed; }


unsigned int Person::get_longest_rates() {
	unsigned int longestRates = 0;
	unsigned int rates = 0;
	if (size(fixed) != 0) {
		for (unsigned int i = 0; i <= size(fixed) - 1; ++i) {
			rates = fixed.at(i).get_rates_amount();
			if (rates > longestRates) longestRates = rates;
		}
		if (size(descending) == 0) { return longestRates; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i) {
			rates = descending.at(i).get_rates_amount();
			if (rates > longestRates) longestRates = rates;
		}
		return longestRates;
	}
	else {
		if (size(descending) == 0) { return longestRates; }
		for (unsigned int i = 0; i <= size(descending) - 1; ++i) {
			rates = descending.at(i).get_rates_amount();
			if (rates > longestRates) longestRates = rates;
		}
		return longestRates;
	}
}


void Person::operator+(FixedInstallmentLoan loan) {
	if (creditworthiness - loan.get_interest() < 0) { return; }
	creditworthiness -= loan.get_interest();
	fixed.push_back(loan);
}


void Person::operator+(DescendingInstallmentLoan loan) {
	if (creditworthiness - loan.get_interest() < 0) { return; }
	creditworthiness -= loan.get_interest();
	descending.push_back(loan);
}
