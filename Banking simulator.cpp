// Dawid Bartosiak

// funkcja main taka jak poprzednio - nie widzę sensu zmieniać gdyż kod ma te same funkcjonalności i na potrzeby implementacji tutaj nazwałem je tak samo.
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
    std::unique_ptr<Bank> bankPtr = std::make_unique<Bank>(0.21);
    std::unique_ptr<Person>dawidPtr = std::make_unique<Person>(&*bankPtr, 25000, 2000);
    std::string fixed = "fixed";
    std::string descending = "descending";
    cout << "Creditworthiness: " << dawidPtr->get_creditworthiness() << endl;
    cout << "Taking loan.." << endl;
    dawidPtr->get_loan(fixed, 20000, 12, 12);
    cout << "All rates sum: " << dawidPtr->get_interest_total() << endl;
    cout << "Sum of loans left to pay: " << dawidPtr->get_amount_total_left() << endl;
    cout << "Total cost of all loans: " << dawidPtr->get_loan_costs_total() << endl;
    cout << "Creditworthiness: " << dawidPtr->get_creditworthiness() << endl;
    cout << "Rate from single loan: " << dawidPtr->get_interest_single(fixed, 0) << endl;
    cout << "Rates left: " << dawidPtr->get_rates_amount(fixed, 0) << endl;
    cout << endl;
    dawidPtr->overpay(fixed, 0, 10000.0);
    cout << "Creditworthiness: " << dawidPtr->get_creditworthiness() << endl;
    cout << "All rates sum: " << dawidPtr->get_interest_total() << endl;
    cout << "Sum of loans left to pay: " << dawidPtr->get_amount_total_left() << endl;
    cout << "Total cost of all loans: " << dawidPtr->get_loan_costs_total() << endl;
    cout << "Creditworthiness: " << dawidPtr->get_creditworthiness() << endl;
    cout << "Rate from single loan: " << dawidPtr->get_interest_single(fixed, 0) << endl;
    cout << "Rates left: " << dawidPtr->get_rates_amount(fixed, 0) << endl;
    cout << "Overpaying.." << endl;
    dawidPtr->overpay(fixed, 0, 15000.0);
    cout << "Creditworthiness: " << dawidPtr->get_creditworthiness() << endl;
    cout << endl;
    cout << "Taking loan.." << endl;
    dawidPtr->get_loan(fixed, 20000, 12, 12);
    cout << "Taking loan.." << endl;
    dawidPtr->get_loan(fixed, 400, 12, 12);
    cout << "Total costs of single loan: " << dawidPtr->get_loan_costs_single(fixed, 0) << endl;
    cout << "Sum of loans left to pay: " << dawidPtr->get_amount_total_left() << endl;
    cout << "Taking loan.." << endl;
    dawidPtr->get_loan(descending, 20000, 12, 12);
    cout << "Total costs of single loan: " << dawidPtr->get_loan_costs_single(descending, 0) << endl;
    cout << endl;
    cout << "Changing interest rate.." << endl;
    bankPtr->set_interest_rate(0.28);
    cout << "Total costs of single loan: " << dawidPtr->get_loan_costs_single(fixed, 0) << endl;
    cout << "Sum of loans left to pay: " << dawidPtr->get_amount_total_left() << endl;
    cout << endl;
    cout << "Total costs of single loan: " << dawidPtr->get_loan_costs_single(descending, 0) << endl;
    cout << "Taking loan.." << endl;
    dawidPtr->overpay(descending, 0, 10000.0);
    cout << "Sum of loans left to pay: " << dawidPtr->get_amount_total_left() << endl;
    cout << "Total costs of single loan: " << dawidPtr->get_loan_costs_single(descending, 0) << endl;
    cout << "All rates sum: " << dawidPtr->get_interest_total() << endl;
    cout << endl;
    BankIO::save_file_one_person(*bankPtr, *dawidPtr);
    BankIO::load_total_loan(*dawidPtr, 0);
    cout << "Add from file to current - making loan single and fixed, so the price is going down as for single loan:" << endl;
    cout << dawidPtr->get_amount_total_left() << endl;
    cout << "So the diff is: " << dawidPtr->get_amount_total_left() - 2* dawidPtr->get_amount_single_left(fixed, 2) << endl;
    FixedInstallmentLoan loanFixed = bankPtr->create_loan_fixed(1123, 12, 12);
    DescendingInstallmentLoan loanDescending = bankPtr->create_loan_descending(1123, 12, 12);
    cout << "Add fixed by operator +" << endl;
    *dawidPtr + loanFixed;
    cout << dawidPtr->get_amount_total_left() << endl;
    cout << "Add descending by operator +" << endl;
    *dawidPtr + loanDescending;
    cout << dawidPtr->get_amount_total_left() << endl;
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
