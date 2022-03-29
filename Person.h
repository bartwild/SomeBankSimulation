// Dawid Bartosiak
// This file include class Person which stand for person that want to get loan in Bank.
// Person have methods that helps him dealing with loan such as getting informations or making some operations on loan.
// All operations must be controlled by bank because it is crual to make financial system safe.
// Person by its own can only get some basic informations about itself or about loan, but can't modify anything in it by its own.


#pragma once
#include <iostream>
#include <vector>
#include "Bank.h"
#include "Loans.h"


class Bank;


class Person{
private:
	std::vector<FixedInstallmentLoan> fixed;
	std::vector<DescendingInstallmentLoan> descending;
	Bank* bank;
	int income;
	int livingCost;
	double creditworthiness;
public:
	Person(Bank *bank, int income, int livingCost);
	int get_income();
	int get_living_cost();
	void set_income(const int& income);
	void set_living_cost(const int& living_cost);
	void get_loan(std::string loanType, int amount, int ratesAmount, int ratesInYear);
	void overpay(std::string loanType, unsigned int numberOfLoan, double amount);
	int get_rates_amount(std::string loanType, unsigned int numberOfLoan);
	double get_interest_total();
	double get_amount_total_left();
	double get_loan_costs_total();
	double get_creditworthiness();
	double get_interest_single(std::string loanType, unsigned int numberOfLoan);
	double get_amount_single_left(std::string loanType, unsigned int numberOfLoan);
	double get_loan_costs_single(std::string loanType, unsigned  int numberOfLoan);
	double get_negative_creditworthines(std::string loanType, unsigned int numberOfLoan);
	std::vector<FixedInstallmentLoan>& get_fixed();
	std::vector<DescendingInstallmentLoan>& get_descending();
};
