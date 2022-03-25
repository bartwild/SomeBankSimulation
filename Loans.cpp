#include <iostream>
#include "Loans.h"


FixedInstallmentLoan::FixedInstallmentLoan(int aAmount, double aInterestRate, int aRatesAmount, int aRatesInYear, double creditworthiness) {
	interest = aAmount * aInterestRate / (aRatesInYear * (1 - pow((aRatesInYear/(aRatesInYear + aInterestRate)),aRatesAmount)));
	if (interest > creditworthiness) throw std::out_of_range("Your creditworthiness is too low. Try more rates or lower loan.");
	interestRate = aInterestRate;
	ratesAmount = aRatesAmount;
	ratesInYear = aRatesInYear;
	loanCosts = interest * ratesAmount;
	amount = interest * ratesAmount;

}


void FixedInstallmentLoan::overpay(double aAmountOfOverpay) {
	double residue = aAmountOfOverpay - ratesAmount*int(aAmountOfOverpay / ratesAmount);
	amount = amount - aAmountOfOverpay;
	ratesAmount = ratesAmount - int(aAmountOfOverpay / ratesAmount);
	interest = amount / ratesAmount;
}


double FixedInstallmentLoan::get_interest() { return interest; }


double FixedInstallmentLoan::get_loan_costs_total() { return loanCosts; }


double FixedInstallmentLoan::get_amount_left() { return amount; }


int FixedInstallmentLoan::get_rates_amount() { return ratesAmount; }


DescendingInstallmentLoan::DescendingInstallmentLoan(int aAmount, double aInterestRate, int aRatesAmount, int aRatesInYear, double creditworthiness) {
	double sum = 0.0;
	for (int i = 1; i < aRatesAmount; i++) {
		sum += pow((1 + aInterestRate / aRatesInYear), i);
	}
	interest = aAmount / sum;
	if (interest > creditworthiness) throw std::out_of_range("Your creditworthiness is too low. Try more rates or lower loan.");
	interestRate = aInterestRate;
	ratesAmount = aRatesAmount;
	ratesInYear = aRatesInYear;
	loanCosts = interest * ratesAmount;
	amount = interest * ratesAmount;

}


void DescendingInstallmentLoan::overpay(double aAmountOfOverpay) {
	double residue = aAmountOfOverpay - ratesAmount * int(aAmountOfOverpay / ratesAmount);
	amount = amount - aAmountOfOverpay;
	ratesAmount = ratesAmount - int(aAmountOfOverpay / ratesAmount);
	interest = amount / ratesAmount;
}


double DescendingInstallmentLoan::get_interest() { return interest; }


double DescendingInstallmentLoan::get_loan_costs() { return loanCosts; }


double DescendingInstallmentLoan::get_amount_left() { return amount; }


int DescendingInstallmentLoan::get_rates_amount() { return ratesAmount; }
