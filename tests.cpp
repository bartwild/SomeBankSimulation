// Dawid Bartosiak

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "Bank.h"
#include "Loans.h"
#include "Person.h"



TEST_CASE("Testing constructors correct") {
    Bank Bank(0.21);
    Person Dawid(&Bank, 25000, 2000);
    std::string fixed = "fixed";
    std::string descending = "descending";
}