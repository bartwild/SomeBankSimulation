// Dawid Bartosiak
// Class Bank is used for perforrming actions that Person is incapable of.
// Bank stand for central bank which can edit interest rate.
// Through bank person can manage its loan. Bank also calculate creditworthiness and manage it to decide of Person capability for taking loan.


#pragma once
#include <iostream>
#include <vector>
#include "Loans.h"
#include "Person.h"


class Person;


class Bank: public std::enable_shared_from_this<Bank> {
	std::shared_ptr<Bank> get_bank() { return shared_from_this(); }
protected:
	double interestRate;
	std::vector<std::shared_ptr<Person>> people;
public:
	Bank(const double& interestRate);
	void set_interest_rate(const double& interestRate);
	virtual double get_interest_rate() const noexcept;
	virtual FixedInstallmentLoan create_loan_fixed(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const;
	virtual FixedInstallmentLoan give_loan_fixed(std::shared_ptr<Person> person, const double& amount,
		const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness);
	virtual double get_fixed_loan_negative_creditworthiness(FixedInstallmentLoan& loan) const noexcept;
	virtual void overpay_fixed(FixedInstallmentLoan& loan, const double& amount);
	virtual DescendingInstallmentLoan create_loan_descending(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const;
	virtual DescendingInstallmentLoan give_loan_descending(std::shared_ptr<Person> person, const double& amount,
	const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness);
	virtual double get_descending_loan_negative_creditworthiness(DescendingInstallmentLoan& loan) const noexcept;
	virtual void overpay_descending(DescendingInstallmentLoan& loan, const double& amount);
	void add_person(Authorisation, std::shared_ptr<Person> person) noexcept;
	virtual ~Bank();
};


class BankBranchFixed : protected Bank {
protected:
	double interestRate;
public:
	double get_interest_rate() const noexcept;
	BankBranchFixed(const double& aInterestRate) : Bank(aInterestRate) { interestRate = aInterestRate; }
	FixedInstallmentLoan create_loan_fixed(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const override;
	FixedInstallmentLoan give_loan(std::shared_ptr<Bank> bank, std::shared_ptr<Person> person, const double& amount,
		const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness);
	double get_fixed_loan_negative_creditworthiness(FixedInstallmentLoan& loan) const noexcept override;
	void overpay_fixed(FixedInstallmentLoan& loan, const double& amount) override;
};


class BankBranchDescending : protected Bank {
protected:
	double interestRate;
public:
	double get_interest_rate() const noexcept;
	BankBranchDescending(const double& aInterestRate) : Bank(aInterestRate) { interestRate = aInterestRate; }
	DescendingInstallmentLoan create_loan_descending(const double& amount, const unsigned int& ratesAmount, const unsigned int& ratesInYear) const override;
	DescendingInstallmentLoan give_loan(std::shared_ptr<Bank> bank, std::shared_ptr<Person>, const double& amount,
		const unsigned int& ratesAmount, const unsigned int& ratesInYear, const double& creditworthiness);
	double get_descending_loan_negative_creditworthiness(DescendingInstallmentLoan& loan) const noexcept override;
	void overpay_descending(DescendingInstallmentLoan& loan, const double& amount) override;
};