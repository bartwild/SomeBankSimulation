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
	FixedInstallmentLoan(int amount, double interestRate, int ratesAmount, int ratesInYear, double creditworthiness);
	void overpay(double amountOfOverpay);
public:
	double get_interest();
	double get_loan_costs_total();
	double get_amount_left();
	int get_rates_amount();
};


class DescendingInstallmentLoan {
friend class Bank;
private:
	int ratesAmount;
	int ratesInYear;
	double amount;
	double interestRate;
	double interest;
	double loanCosts;
	DescendingInstallmentLoan(int amount, double interestRate, int ratesAmount, int ratesInYear, double creditworthiness);
	void overpay(double amountOfOverpay);
public:
	double get_interest();
	double get_loan_costs();
	double get_amount_left();
	int get_rates_amount();
};
