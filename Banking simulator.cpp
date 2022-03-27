#include <iostream>
#include "Bank.h"
#include "Person.h"
#include "Loans.h"


int main() {
    Bank Bank(0.21);
    Person Dawid(&Bank, 25000, 2000);
    std::string fixed = "fixed";
    std::string descending = "descending";
    try {
        std::cout << Dawid.get_creditworthiness() << std::endl;
        Dawid.get_loan(fixed, 20000, 12, 12);
        std::cout << Dawid.get_interest_total() << std::endl;
        std::cout << Dawid.get_amount_total_left() << std::endl;
        std::cout << Dawid.get_loan_costs_total() << std::endl;
        std::cout << Dawid.get_creditworthiness() << std::endl;
        std::cout << Dawid.get_interest_single(fixed, 0) << std::endl;
        std::cout << Dawid.get_rates_amount(fixed, 0) << std::endl;
        std::cout << std::endl << std::endl << std::endl;
        Dawid.overpay(fixed, 0, 10000.0);
        std::cout << Dawid.get_creditworthiness() << std::endl;
        std::cout << Dawid.get_interest_total() << std::endl;
        std::cout << Dawid.get_amount_total_left() << std::endl;
        std::cout << Dawid.get_loan_costs_total() << std::endl;
        std::cout << Dawid.get_creditworthiness() << std::endl;
        std::cout << Dawid.get_interest_single(fixed, 0) << std::endl;
        std::cout << Dawid.get_rates_amount(fixed, 0) << std::endl;
        std::cout << std::endl << std::endl << std::endl;
        Dawid.overpay(fixed, 0, 15000.0);
        std::cout << Dawid.get_creditworthiness() << std::endl;
        Dawid.get_loan(fixed, 20000, 12, 12);
        Dawid.get_loan(fixed, 400, 12, 12);
        std::cout << Dawid.get_loan_costs_single(fixed, 0) << std::endl;
        std::cout << Dawid.get_amount_total_left() << std::endl;
        Dawid.get_loan(descending, 20000, 12, 12);
        std::cout << Dawid.get_loan_costs_single(descending, 0) << std::endl;
        Bank.set_interest_rate(0.28);
        std::cout << Dawid.get_loan_costs_single(fixed, 0) << std::endl;
        std::cout << Dawid.get_amount_total_left() << std::endl;
        std::cout << std::endl << std::endl << std::endl;
        std::cout << Dawid.get_loan_costs_single(fixed, 0) << std::endl;
        std::cout << Dawid.get_loan_costs_single(descending, 0) << std::endl;
        Dawid.overpay(descending, 0, 10000.0);
        std::cout << Dawid.get_amount_single_left(descending, 0) << std::endl;
        std::cout << Dawid.get_loan_costs_single(descending, 0) << std::endl;
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
