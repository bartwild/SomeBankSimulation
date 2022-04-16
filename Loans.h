// Dawid Bartosiak
// This file include classes Loans which stand for 2 types of loan in Bank.
// Those classes have friend class - Bank, which is the only way to access some methods in them as kind of safeguard
// Both classes provide methods that help us dealing with problems connected with loans such as overpaying, setting rates.
#pragma once


class Authorisation {
	friend class Bank;
	Authorisation() {};
};


class DescendingInstallmentLoan;


class FixedInstallmentLoan{
private:
	int ratesAmount;
	int ratesInYear;
	double amount;
	double interestRate;
	double interest;
	double loanCosts;
	double negativeCreditworthiness;
public:
	FixedInstallmentLoan(Authorisation, const double& amount, const double& interestRate, int ratesAmount, int ratesInYear, const double& creditworthiness);
	void overpay(Authorisation, const double& amountOfOverpay);
	void set_interest_rates(Authorisation, const double& interestRate);
	bool operator>(FixedInstallmentLoan loan);
	bool operator<(FixedInstallmentLoan loan);
	bool operator>(DescendingInstallmentLoan loan);
	bool operator<(DescendingInstallmentLoan loan);
	double get_negative_creditworthiness(Authorisation);
	double get_interest();
	double get_loan_costs_total();
	double get_amount_left();
	int get_rates_amount();
	friend std::ostream& operator<<(std::ostream& os, FixedInstallmentLoan& loan);
};


class DescendingInstallmentLoan {
private:
	int ratesAmountTotal;
	int ratesAmount;
	int ratesInYear;
	double amount;
	double interestRate;
	double interest;
	double loanCosts;
	double negativeCreditworthiness;
public:
	DescendingInstallmentLoan(Authorisation, const double& amount, const double& interestRate, int ratesAmount, int ratesInYear, const double& creditworthiness);
	void overpay(Authorisation, const double& amountOfOverpay);
	void set_interest_rates(Authorisation, const double& interestRate);
	bool operator>(DescendingInstallmentLoan loan);
	bool operator>(FixedInstallmentLoan loan);
	bool operator<(DescendingInstallmentLoan loan);
	bool operator<(FixedInstallmentLoan loan);
	double get_negative_creditworthiness(Authorisation);
	double get_interest();
	double get_loan_costs_total();
	double get_amount_left();
	int get_rates_amount();
	friend std::ostream& operator<<(std::ostream& os, DescendingInstallmentLoan& loan);
};
