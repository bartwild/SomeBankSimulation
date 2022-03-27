#pragma once
#include <iostream>
#include <vector>
#include "Bank.h"
#include "Loans.h"



class Person{
private:
	std::vector<FixedInstallmentLoan> fixed;
	std::vector<DescendingInstallmentLoan> descending;
	Bank* bank;
	int income;
	int livingCost;
	double interest;
	double creditworthiness;
public:
	Person(Bank *bank, int income, int livingCost);
	void get_loan(std::string loanType, int amount, int ratesAmount, int ratesInYear);
	void overpay(std::string loanType, int numberOfLoan, double amount);
	int get_rates_amount(std::string loanType, int numberOfLoan);
	double get_interest_total();
	double get_amount_total_left();
	double get_loan_costs_total();
	double get_creditworthiness();
	double get_interest_single(std::string loanType, int numberOfLoan);
	double get_amount_single_left(std::string loanType, int numberOfLoan);
	double get_loan_costs_single(std::string loanType, int numberOfLoan);
	double get_negative_creditworthines(std::string loanType, int numberOfLoan);
	std::vector<FixedInstallmentLoan>& get_fixed();
	std::vector<DescendingInstallmentLoan>& get_descending();
};
