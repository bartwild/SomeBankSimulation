#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Bank.h"
#include "Person.h"
#include "Loans.h"


class BankIO{
public:
    static void save_file_one_person(Bank& bank, Person& person);
    static void save_another_person(Bank& bank, Person& person);
    static void load_bank(Bank& bank);
    static void load_total_loan(Person& person, unsigned int number_of_person);
    static void load_person(Person& person, unsigned int number_of_person);
    static void load_file_single_person(Bank& bank, Person& person);
    static void save_file_one_person(std::shared_ptr<Bank> bank, std::shared_ptr<Person> person);
    static void save_another_person(std::shared_ptr<Bank>, std::shared_ptr<Person> person);
    static void load_bank(std::shared_ptr<Bank>);
    static void load_total_loan(std::shared_ptr<Person> person, unsigned int number_of_person);
    static void load_person(std::shared_ptr<Person> person, unsigned int number_of_person);
    static void load_file_single_person(std::shared_ptr<Bank>, std::shared_ptr<Person> person);
};

