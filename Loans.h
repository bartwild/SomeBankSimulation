// Dawid Bartosiak
// This file include classes Loans which stand for 2 types of loan in Bank.
// Those classes have friend class - Bank, which is the only way to access some methods in them as kind of safeguard
// Both classes provide methods that help us dealing with problems connected with loans such as overpaying, setting rates.


#pragma once


class FixedInstallmentLoan{
friend class Bank;
private:
	int ratesAmount;
	int ratesInYear;
	double amount;
	double interestRate;
	double interest;
	double loanCosts;
	double negativeCreditworthiness;
	FixedInstallmentLoan(int amount, const double& interestRate, int ratesAmount, int ratesInYear, const double& creditworthiness);
	void overpay(const double& amountOfOverpay);
	void set_interest_rates(const double& interestRate);
public:
	double get_interest();
	double get_loan_costs_total();
	double get_amount_left();
	int get_rates_amount();
};


class DescendingInstallmentLoan {
friend class Bank;
private:
	int ratesAmountTotal;
	int ratesAmount;
	int ratesInYear;
	double amount;
	double interestRate;
	double interest;
	double loanCosts;
	double negativeCreditworthiness;
	DescendingInstallmentLoan(int amount, const double& interestRate, int ratesAmount, int ratesInYear, const double& creditworthiness);
	void overpay(double& amountOfOverpay);
	void set_interest_rates(const double& interestRate);
public:
	double get_interest();
	double get_loan_costs_total();
	double get_amount_left();
	int get_rates_amount();
};
