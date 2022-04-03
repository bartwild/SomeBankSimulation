﻿// Dawid Bartosiak

#include <iostream>
#include "Bank.h"
#include "Person.h"
#include "Loans.h"


using std::cout;
using std::endl;


int main() {
    Bank Bank(0.21);
    Person Dawid(&Bank, 25000, 2000);
    std::string fixed = "fixed";
    std::string descending = "descending";
    cout << "Creditworthiness: " << Dawid.get_creditworthiness() << endl;
    cout << "Taking loan.." << endl;
    Dawid.get_loan(fixed, 20000, 12, 12);
    cout << "All rates sum: " << Dawid.get_interest_total() << endl;
    cout << "Sum of loans left to pay: " << Dawid.get_amount_total_left() << endl;
    cout << "Total cost of all loans: " << Dawid.get_loan_costs_total() << endl;
    cout << "Creditworthiness: " << Dawid.get_creditworthiness() << endl;
    cout << "Rate from single loan: " << Dawid.get_interest_single(fixed, 0) << endl;
    cout << "Rates left: " << Dawid.get_rates_amount(fixed, 0) << endl;
    cout << endl;
    Dawid.overpay(fixed, 0, 10000.0);
    cout << "Creditworthiness: " << Dawid.get_creditworthiness() << endl;
    cout << "All rates sum: " << Dawid.get_interest_total() << endl;
    cout << "Sum of loans left to pay: " << Dawid.get_amount_total_left() << endl;
    cout << "Total cost of all loans: " << Dawid.get_loan_costs_total() << endl;
    cout << "Creditworthiness: " << Dawid.get_creditworthiness() << endl;
    cout << "Rate from single loan: " << Dawid.get_interest_single(fixed, 0) << endl;
    cout << "Rates left: " << Dawid.get_rates_amount(fixed, 0) << endl;
    cout << "Overpaying.." << endl;
    Dawid.overpay(fixed, 0, 15000.0);
    cout << "Creditworthiness: " << Dawid.get_creditworthiness() << endl;
    cout << endl;
    cout << "Taking loan.." << endl;
    Dawid.get_loan(fixed, 20000, 12, 12);
    cout << "Taking loan.." << endl;
    Dawid.get_loan(fixed, 400, 12, 12);
    cout << "Total costs of single loan: " << Dawid.get_loan_costs_single(fixed, 0) << endl;
    cout << "Sum of loans left to pay: " << Dawid.get_amount_total_left() << endl;
    cout << "Taking loan.." << endl;
    Dawid.get_loan(descending, 20000, 12, 12);
    cout << "Total costs of single loan: " << Dawid.get_loan_costs_single(descending, 0) << endl;
    cout << endl;
    cout << "Changing interest rate.." << endl;
    Bank.set_interest_rate(0.28);
    cout << "Total costs of single loan: " << Dawid.get_loan_costs_single(fixed, 0) << endl;
    cout << "Sum of loans left to pay: " << Dawid.get_amount_total_left() << endl;
    cout << endl;
    cout << "Total costs of single loan: " << Dawid.get_loan_costs_single(descending, 0) << endl;
    cout << "Taking loan.." << endl;
    Dawid.overpay(descending, 0, 10000.0);
    cout << "Sum of loans left to pay: " << Dawid.get_amount_single_left(descending, 0) << endl;
    cout << "Total costs of single loan: " << Dawid.get_loan_costs_single(descending, 0) << endl;
    cout << "All rates sum: " << Dawid.get_interest_total() << endl;
    cout << endl;
    return 0;
}
