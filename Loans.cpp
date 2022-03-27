// Dawid Bartosiak


#include <iostream>
#include <cmath>
#include "Loans.h"


FixedInstallmentLoan::FixedInstallmentLoan(int aAmount, const double& aInterestRate, int aRatesAmount, int aRatesInYear, const double& creditworthiness) {
	interest = aAmount * aInterestRate / (aRatesInYear * (1 - pow((aRatesInYear/(aRatesInYear + aInterestRate)),aRatesAmount)));
	if (interest > creditworthiness) throw std::out_of_range("Your creditworthiness is too low. Try more rates or lower loan.");
	interestRate = aInterestRate;
	ratesAmount = aRatesAmount;
	ratesInYear = aRatesInYear;
	loanCosts = interest * ratesAmount;
	amount = interest * ratesAmount;
	negativeCreditworthiness = interest;

}


void FixedInstallmentLoan::overpay(const double& aAmountOfOverpay) {
	amount = amount - aAmountOfOverpay;
	ratesAmount = ratesAmount - int(aAmountOfOverpay / interest);
	interest = amount / ratesAmount;
}


double FixedInstallmentLoan::get_interest() { return interest; }


double FixedInstallmentLoan::get_loan_costs_total() { return loanCosts; }


double FixedInstallmentLoan::get_amount_left() { return amount; }


int FixedInstallmentLoan::get_rates_amount() { return ratesAmount; }


void FixedInstallmentLoan::set_interest_rates(const double& aInterestRate) {
	double tempAmount = interest* (ratesInYear * (1 - pow((ratesInYear / (ratesInYear + interestRate)), ratesAmount)) / interestRate);
	interest = tempAmount * aInterestRate / (ratesInYear * (1 - pow((ratesInYear / (ratesInYear + aInterestRate)), ratesAmount)));
	interestRate = aInterestRate;
	tempAmount = amount;
	amount = interest * ratesAmount;
	loanCosts = loanCosts - tempAmount + amount;
}


DescendingInstallmentLoan::DescendingInstallmentLoan(int aAmount, const double& aInterestRate, int aRatesAmount, int aRatesInYear, const double& creditworthiness) {
	interest = (double(aAmount / aRatesAmount)) * (1 + aRatesAmount * aInterestRate / aRatesInYear);
	if (interest > creditworthiness) throw std::out_of_range("Your creditworthiness is too low. Try more rates or lower loan.");
	interestRate = aInterestRate;
	ratesAmount = aRatesAmount;
	ratesAmountTotal = ratesAmount;
	ratesInYear = aRatesInYear;
	loanCosts = 0.0;
	for (int i = 1; i <= ratesAmount; i++) {
		loanCosts += (double(aAmount / aRatesAmount))* (1 + (aRatesAmount-i+1) * aInterestRate / aRatesInYear);
	}
	amount = loanCosts;
	negativeCreditworthiness = interest;
}


void DescendingInstallmentLoan::overpay(const double& aAmountOfOverpay) {
	double overpay = aAmountOfOverpay;
	double nettoAmount = interest * ratesAmount / (1 + (ratesAmount)*interestRate / ratesInYear);
	while (overpay >= interest && ratesAmount > 0) {
		overpay -= interest;
		interest = (nettoAmount / ratesAmountTotal)* (1 + (ratesAmount) * interestRate / ratesInYear);
		ratesAmount--;
	}
	amount -= aAmountOfOverpay - overpay;

}


double DescendingInstallmentLoan::get_interest() { return interest; }


double DescendingInstallmentLoan::get_loan_costs_total() { return loanCosts; }


double DescendingInstallmentLoan::get_amount_left() { return amount; }


int DescendingInstallmentLoan::get_rates_amount() { return ratesAmount; }


void DescendingInstallmentLoan::set_interest_rates(const double& aInterestRate) {
	double nettoAmount = interest * ratesAmount / (1 + (ratesAmount)*interestRate / ratesInYear);
	interestRate = aInterestRate;
	double tempAmount = 0.0;
	for (int i = 1; i <= ratesAmount; i++) {
		tempAmount += (nettoAmount / ratesAmount) * (1 + (ratesAmount - i + 1) * interestRate / ratesInYear);
	}
	interest = (nettoAmount / ratesAmount) * (1 + ratesAmount * interestRate / ratesInYear);
	loanCosts = loanCosts + tempAmount - amount;
	amount = tempAmount;
}
