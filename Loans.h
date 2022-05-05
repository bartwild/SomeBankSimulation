// Dawid Bartosiak
// This file include classes Loans which stand for 2 types of loan in Bank.
// Those classes have friend class - Authorisation, which is the only way to access some methods in them as kind of safeguard
// Both classes provide methods that help us dealing with problems connected with loans such as overpaying, setting rates.
// Both heritages from Loan.
#pragma once


class FixedInstallmentLoan;
class DescendingInstallmentLoan;


class Authorisation {
	friend class Bank;
	friend class BankBranchFixed;
	friend class BankBranchDescending;
	Authorisation() {};
};


class Loan {
protected:
	int ratesAmountTotal;
	int ratesAmount;
	int ratesInYear;
	double amount;
	double interestRate;
	double interest;
	double loanCosts;
	double negativeCreditworthiness;
public:
	bool operator>(FixedInstallmentLoan loan);
	bool operator<(FixedInstallmentLoan loan);
	bool operator>(DescendingInstallmentLoan loan);
	bool operator<(DescendingInstallmentLoan loan);
	double get_negative_creditworthiness(Authorisation) const noexcept;
	double get_interest() const noexcept;
	double get_loan_costs_total() const noexcept;
	double get_amount_left() const noexcept;
	int get_rates_amount() const noexcept;
	friend std::ostream& operator<<(std::ostream& os, Loan& loan) noexcept;
};


class FixedInstallmentLoan: public Loan {
public:
	FixedInstallmentLoan(Authorisation, const double& amount, const double& interestRate, int ratesAmount, int ratesInYear, const double& creditworthiness);
	void overpay(Authorisation, const double& amountOfOverpay);
	void set_interest_rates(Authorisation, const double& interestRate);
};


class DescendingInstallmentLoan: public Loan {
public:
	DescendingInstallmentLoan(Authorisation, const double& amount, const double& interestRate, int ratesAmount, int ratesInYear, const double& creditworthiness);
	void overpay(Authorisation, const double& amountOfOverpay);
	void set_interest_rates(Authorisation, const double& interestRate);
};
