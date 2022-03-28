// Dawid Bartosiak

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "Bank.h"
#include "Loans.h"
#include "Person.h"


std::string fixed = "fixed";
std::string descending = "descending";


TEST_CASE("Testing constructors correct.") {
    Bank Bank(0.21);
    Person Dawid(&Bank, 25000, 2000);
    Dawid.get_loan(fixed, 10000, 12, 12);

    SECTION("Check if Bank created.") {
        REQUIRE(Bank.get_interest_rate() == 0.21);
    }

    SECTION("Check if Person created.") {
        REQUIRE(Dawid.get_living_cost() == 2000);
    }

    SECTION("Check if Loan created.") {
        REQUIRE(Dawid.get_amount_single_left(fixed, 0) == Approx(11173.65));
    }
}

TEST_CASE("Testing constructors incorrect.") {

    SECTION("Bank wrong constructor.") {
        CHECK_THROWS_AS(Bank(-0.21), std::out_of_range);
    }

    SECTION("Person wrong constructors.") {
        Bank Bank(0.21);
        CHECK_THROWS_AS(Person(&Bank, -1000, 1000), std::out_of_range);
        CHECK_THROWS_AS(Person(&Bank, 10000, -1000), std::out_of_range);
        CHECK_THROWS_AS(Person(&Bank, 10000, 0), std::out_of_range);
    }

    SECTION("Loan wrong constructors.") {
        Bank Bank(0.21);
        Person Dawid(&Bank, 25000, 2000);
        CHECK_THROWS_AS(Dawid.get_loan(fixed, -10000, 12, 12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan(fixed, 10000, -12, 12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan(fixed, 10000, 12, -12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan(descending, -10000, 12, 12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan(fixed, 10000, -12, 12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan(fixed, 10000, 12, -12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan("Name", 10000, 12, 12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan(fixed, 1000000, 12, 12), std::out_of_range);
        CHECK_THROWS_AS(Dawid.get_loan(descending, 1000000, 12, 12), std::out_of_range);
    }
}


TEST_CASE("Testing methods incorrect.") {
    Bank Bank(0.21);
    Person Dawid(&Bank, 25000, 2000);
    Dawid.get_loan(fixed, 10000, 12, 12);
    Dawid.get_loan(descending, 10000, 12, 12);
    FixedInstallmentLoan loan1 = Dawid.get_fixed().at(0);
    DescendingInstallmentLoan loan2 = Dawid.get_descending().at(0);

    SECTION("Bank wrong methods") {
        REQUIRE_THROWS_WITH(Bank.set_interest_rate(-1), "Interest rate cannot be negative.");
        REQUIRE_THROWS_WITH(Bank.overpay_descending(loan2, 0.0), "You can't overpay negative amount of money.");
        REQUIRE_THROWS_WITH(Bank.overpay_fixed(loan1, 0), "You can't overpay negative amount of money.");
        REQUIRE_THROWS_WITH(Bank.give_loan_fixed(&Dawid, -1000, 12, 12, Dawid.get_creditworthiness()), "Any of loan parameter cannot be negative.");
        REQUIRE_THROWS_WITH(Bank.give_loan_fixed(&Dawid, 1000, -12, 12, Dawid.get_creditworthiness()), "Any of loan parameter cannot be negative.");
        REQUIRE_THROWS_WITH(Bank.give_loan_fixed(&Dawid, 1000, 12, -12, Dawid.get_creditworthiness()), "Any of loan parameter cannot be negative.");
        REQUIRE_THROWS_WITH(Bank.give_loan_descending(&Dawid, 1000, 12, -12, Dawid.get_creditworthiness()), "Any of loan parameter cannot be negative.");
        REQUIRE_THROWS_WITH(Bank.give_loan_descending(&Dawid, 1000, -12, 12, Dawid.get_creditworthiness()), "Any of loan parameter cannot be negative.");
        REQUIRE_THROWS_WITH(Bank.give_loan_descending(&Dawid, -1000, 12, 12, Dawid.get_creditworthiness()), "Any of loan parameter cannot be negative.");
    }

    SECTION("Person wrong methods.") {
        REQUIRE_THROWS_WITH(Dawid.set_income(-1), "Income cannot be negative.");
        REQUIRE_THROWS_WITH(Dawid.set_living_cost(-1), "Living cost can't be negative or equal 0.");
        REQUIRE_THROWS_WITH(Dawid.overpay(fixed, 0, -1), "You can't overpay negative amount of money.");
        REQUIRE_THROWS_WITH(Dawid.overpay(fixed, 1, 1), "invalid vector subscript");
        REQUIRE_THROWS_WITH(Dawid.overpay("Name", 0, 1), "Incorrect loan type.");
    }

    SECTION("Loan wrong methods.") {
        REQUIRE_THROWS_WITH(Bank.give_loan_fixed(&Dawid, 10000, 1, 1, 12.0), "Your creditworthiness is too low. Try more rates or lower loan.");
        REQUIRE_THROWS_WITH(Bank.give_loan_descending(&Dawid, 10000, 1, 1, 12.0), "Your creditworthiness is too low. Try more rates or lower loan.");
    }
}


TEST_CASE("Testing methods correct.") {
    Bank Bank(0.21);
    Person Dawid(&Bank, 25000, 2000);
    Dawid.get_loan(fixed, 10000, 12, 12);
    Dawid.get_loan(descending, 10000, 12, 12);
    FixedInstallmentLoan loan1 = Dawid.get_fixed().at(0);
    DescendingInstallmentLoan loan2 = Dawid.get_descending().at(0);

    SECTION("Bank correct methods") {
        Bank.set_interest_rate(1);
        REQUIRE(Bank.get_interest_rate() == 1);
        Bank.set_interest_rate(0.21);
        double diff1 = loan1.get_amount_left() - loan1.get_interest();
        double diff2 = loan2.get_amount_left() - loan2.get_interest();
        Bank.overpay_fixed(loan1, loan1.get_interest());
        Bank.overpay_descending(loan2, loan2.get_interest());
        REQUIRE(loan1.get_amount_left() == Approx(diff1));
        REQUIRE(loan2.get_amount_left() == Approx(diff2));
        FixedInstallmentLoan loan3 = Bank.give_loan_fixed(&Dawid, 10, 1, 1, Dawid.get_creditworthiness());
        DescendingInstallmentLoan loan4 =Bank.give_loan_descending(&Dawid, 10, 1, 1, Dawid.get_creditworthiness());
        REQUIRE(loan3.get_rates_amount() == 1);
        REQUIRE(loan4.get_rates_amount() == 1);
    }

    SECTION("Person correct methods.") {
        REQUIRE(Dawid.get_fixed().size() == 1);
        REQUIRE(Dawid.get_descending().size() == 1);
        Dawid.get_loan(fixed, 10, 1, 1);
        Dawid.get_loan(descending, 10, 1, 1);
        REQUIRE(Dawid.get_fixed().size() == 2);
        REQUIRE(Dawid.get_descending().size() == 2);
        Dawid.set_income(100000);
        Dawid.set_living_cost(1000);
        REQUIRE(Dawid.get_income() == 100000);
        REQUIRE(Dawid.get_living_cost() == 1000);
        Dawid.overpay(fixed, 1, 1000000);
        REQUIRE(Dawid.get_fixed().size() == 1);
        Dawid.overpay(fixed, 0, Dawid.get_interest_single(fixed, 0));
        REQUIRE(Dawid.get_rates_amount(fixed, 0) == 11);
        Dawid.overpay(descending, 1, 1000000);
        REQUIRE(Dawid.get_descending().size() == 1);
        Dawid.overpay(descending, 0, Dawid.get_interest_single(descending, 0));
        REQUIRE(Dawid.get_rates_amount(descending, 0) == 11);
    }

    SECTION("Loan correct methods.") {
        REQUIRE(Dawid.get_amount_single_left(fixed, 0) == Approx(11173.65));
        REQUIRE(Dawid.get_amount_single_left(descending, 0) == Approx(11133));
        Bank.set_interest_rate(0.28);
        REQUIRE(Dawid.get_amount_single_left(fixed, 0) == Approx(11580.71));
        REQUIRE(Dawid.get_amount_single_left(descending, 0) == Approx(11512.06));

    }
}
