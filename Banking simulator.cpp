#include <iostream>
#include "Bank.h"
#include "Person.h"
#include "Loans.h"


int main() {
    Bank Bank(0.21);
    Person Dawid(Bank, 5000, 200);
    std::string fixed = "fixed";
    try {
        std::cout << Dawid.get_creditworthiness() << std::endl;
        Dawid.get_loan(fixed, 20000, 12, 12);
        std::cout << Dawid.get_interest_total() << std::endl;
        std::cout << Dawid.get_loan_costs_total() << std::endl;
        std::cout << Dawid.get_creditworthiness() << std::endl;
        std::cout << Dawid.get_interest_single(fixed, 0) << std::endl;
        std::cout << Dawid.get_rates_amount(fixed, 0) << std::endl;
        Dawid.overpay(fixed, 0, 10000);
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
