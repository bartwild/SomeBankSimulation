#include "BankIO.h"
const std::string filename = "bank_info.txt";


void BankIO::save_file_one_person(std::shared_ptr<Bank> bank, std::shared_ptr<Person> person){
    std::ofstream bankInfo(filename, std::ios::trunc);
    bankInfo << bank->get_interest_rate() << "\n";
    bankInfo << person->get_income() << "\n";
    bankInfo << person->get_living_cost() << "\n";
    bankInfo << (1 / (1 + (person->get_longest_rates()) * bank->get_interest_rate() / 12)) * person->get_amount_total_left() << "\n";
    bankInfo << person->get_longest_rates() << "\n";
}


void BankIO::save_another_person(std::shared_ptr<Bank> bank, std::shared_ptr<Person> person){
    std::ofstream bankInfo(filename, std::ios::ate);
    bankInfo << person->get_income() << "\n";
    bankInfo << person->get_living_cost() << "\n";
    bankInfo << (1 / (1 + (person->get_longest_rates()) * bank->get_interest_rate() / 12)) * person->get_amount_total_left() << "\n";
    bankInfo << person->get_longest_rates() << "\n";
}


void BankIO::load_bank(std::shared_ptr<Bank> bank){
    std::ifstream bankInfo(filename);
    double interestRates;
    bankInfo >> interestRates;
    bank->set_interest_rate(interestRates);
}


void BankIO::load_total_loan(std::shared_ptr<Person> person, unsigned int number_of_person){
    std::ifstream bankInfo(filename);
    std::string trashCan;
    double amount;
    unsigned int rates;
    bankInfo >> trashCan;
    bankInfo >> trashCan;
    bankInfo >> trashCan;
    while (number_of_person * 4 > 1) {
        bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan;
        number_of_person -= 1;
    }
    bankInfo >> amount;
    bankInfo >> rates;
    person->get_loan("fixed", amount, rates, 12);
}


void BankIO::load_person(std::shared_ptr<Person> person, unsigned int number_of_person){
    std::ifstream bankInfo(filename);
    std::string trashCan;
    unsigned int livingCost;
    unsigned int income;
    bankInfo >> trashCan;
    while (number_of_person * 4 > 1) {
        bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan;
        number_of_person -= 1;
    }
    bankInfo >> income;
    bankInfo >> livingCost;
    person->set_income(income);
    person->set_living_cost(livingCost);
}


void BankIO::load_file_single_person(std::shared_ptr<Bank> bank, std::shared_ptr<Person> person){
    load_bank(bank);
    load_person(person, 0);
    load_total_loan(person, 0);
}


void BankIO::save_file_one_person(Bank& bank, Person& person) {
    std::ofstream bankInfo(filename, std::ios::trunc);
    bankInfo << bank.get_interest_rate() << "\n";
    bankInfo << person.get_income() << "\n";
    bankInfo << person.get_living_cost() << "\n";
    bankInfo << (1 / (1 + (person.get_longest_rates()) * bank.get_interest_rate() / 12)) * person.get_amount_total_left() << "\n";
    bankInfo << person.get_longest_rates() << "\n";
}


void BankIO::save_another_person(Bank& bank, Person& person) {
    std::ofstream bankInfo(filename, std::ios::ate);
    bankInfo << person.get_income() << "\n";
    bankInfo << person.get_living_cost() << "\n";
    bankInfo << (1 / (1 + (person.get_longest_rates()) * bank.get_interest_rate() / 12)) * person.get_amount_total_left() << "\n";
    bankInfo << person.get_longest_rates() << "\n";
}


void BankIO::load_bank(Bank& bank) {
    std::ifstream bankInfo(filename);
    double interestRates;
    bankInfo >> interestRates;
    bank.set_interest_rate(interestRates);
}


void BankIO::load_total_loan(Person& person, unsigned int number_of_person) {
    std::ifstream bankInfo(filename);
    std::string trashCan;
    double amount;
    unsigned int rates;
    bankInfo >> trashCan;
    bankInfo >> trashCan;
    bankInfo >> trashCan;
    while (number_of_person * 4 > 1) {
        bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan;
        number_of_person -= 1;
    }
    bankInfo >> amount;
    bankInfo >> rates;
    person.get_loan("fixed", amount, rates, 12);
}


void BankIO::load_person(Person& person, unsigned int number_of_person) {
    std::ifstream bankInfo(filename);
    std::string trashCan;
    unsigned int livingCost;
    unsigned int income;
    bankInfo >> trashCan;
    while (number_of_person * 4 > 1) {
        bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan; bankInfo >> trashCan;
        number_of_person -= 1;
    }
    bankInfo >> income;
    bankInfo >> livingCost;
    person.set_income(income);
    person.set_living_cost(livingCost);
}


void BankIO::load_file_single_person(Bank& bank, Person& person) {
    load_bank(bank);
    load_person(person, 0);
    load_total_loan(person, 0);
}
