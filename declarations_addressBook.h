#ifndef DECLARATIONS_ADDRESSBOOK_H_INCLUDED
#define DECLARATIONS_ADDRESSBOOK_H_INCLUDED
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <stdio.h>

using namespace std;

struct Person
{
    int id, userID;
    string name, surname, email, adress, nr_tel;
};

vector<Person> loadPersonFromPhoneBook(string &fileLine, vector<Person> persons, int loggedUserID);
int setNextAddresseeIDNumber(string line);
int getAddresseIDNumberFromFile();
vector<Person> loadPhoneBook(int loggedUserID, string &lineToExtractAddresseeID);
void savePersonDataToFile(fstream & file, Person person);
void savePersonToFile(vector<Person> persons, string fileName, int ID);
void saveEditedPhoneBookToFile(Person person, int addresseeID);
void saveDeletedPersonToFile(int addresseeID);
vector<Person> addNewPerson(vector<Person> persons, int loggedUserID, int &addresseeID);
void displayPersonData(Person person);
void displayPhoneBook(vector<Person> persons, int loggedUserID);
int findPersonIDByName(vector<Person> persons);
int findPersonIDBySurname(vector<Person> persons);
vector<Person> editPersonData(vector<Person> persons, int loggedUserID);
vector<Person> deletePerson(vector<Person> persons, int loggedUserID);

#endif // DEFINITIONS_ADDRESSBOOK_H_INCLUDED
