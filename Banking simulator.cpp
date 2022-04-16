// Dawid Bartosiak


#define  _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include "Bank.h"
#include "Person.h"
#include "Loans.h"
#include "BankIO.h"


using std::cout;
using std::endl;



int main() {
    auto start = std::chrono::system_clock::now();
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
    cout << "Sum of loans left to pay: " << Dawid.get_amount_total_left() << endl;
    cout << "Total costs of single loan: " << Dawid.get_loan_costs_single(descending, 0) << endl;
    cout << "All rates sum: " << Dawid.get_interest_total() << endl;
    cout << endl;
    BankIO::save_file_one_person(Bank, Dawid);
    BankIO::load_total_loan(Dawid, 0);
    cout << "Add from file to current - making loan single and fixed, so the price is going down as for single loan:" << endl;
    cout << Dawid.get_amount_total_left() << endl;
    cout << "So the diff is: " << Dawid.get_amount_total_left() - 2*Dawid.get_amount_single_left(fixed, 2) << endl;
    FixedInstallmentLoan loanFixed = Bank.create_loan_fixed(1123, 12, 12);
    DescendingInstallmentLoan loanDescending = Bank.create_loan_descending(1123, 12, 12);
    cout << "Add fixed by operator +" << endl;
    Dawid + loanFixed;
    cout << Dawid.get_amount_total_left() << endl;
    cout << "Add descending by operator +" << endl;
    Dawid + loanDescending;
    cout << Dawid.get_amount_total_left() << endl;
    cout << "Is fixed cheaper than descending?: ";
    cout << (loanFixed < loanDescending) << endl;
    cout << "Is descending cheaper than fixed?: ";
    cout << (loanDescending < loanFixed) << endl;
    cout << "Information about fixed: ";
    cout << loanFixed;
    cout << "Information about descending: ";
    cout << loanDescending;
    cout << endl << endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time);
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
