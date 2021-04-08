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
    int id;
    string name, surname, email, adress, nr_tel;
};

string substractString(string stringToSubstract, int firstCharPosition)
{
    int stringLength = stringToSubstract.length();
    string stringSubstracted = stringToSubstract.substr(firstCharPosition, stringLength);
    return stringSubstracted;
}

int convertStringToIntiger(string stringToConvert)
{
    int number;
    stringstream ss(stringToConvert);
    ss >> number;
    return number;
}

string readLinePart(string fileLine, int* start)
{
    string id;
    int i = *start;
    while (fileLine[i] != '|')
    {
        id = id + fileLine[i];
        i++;
    }
    i++;
    *start=i;

    return id;
}

vector<Person> loadPersonFromPhoneBook(string fileLine, vector<Person> persons)
{
    int intID;

    string id="", name="", surname="", email="", nr_tel="", adress="", stringID="";
    int startPosition=0;
    int peopleNumber = persons.size();
    persons.push_back(Person());

    id = readLinePart(fileLine, &startPosition);
    stringID = substractString(id, 0);
    intID = convertStringToIntiger(stringID);
    persons[peopleNumber].id = intID;

    persons[peopleNumber].name = readLinePart(fileLine, &startPosition);
    persons[peopleNumber].surname = readLinePart(fileLine, &startPosition);
    persons[peopleNumber].email = readLinePart(fileLine, &startPosition);
    persons[peopleNumber].nr_tel= readLinePart(fileLine, &startPosition);
    persons[peopleNumber].adress = readLinePart(fileLine, &startPosition);

    cout << persons[peopleNumber].id << ". " << persons[peopleNumber].name;
    cout << " " << persons[peopleNumber].surname  << " " << endl;
    cout << "phone number: " << persons[peopleNumber].nr_tel << endl;
    cout << "e-mail address: " << persons[peopleNumber].email << endl;
    cout << "address: " << persons[peopleNumber].adress<< endl;

    return persons;
}

bool checkFileStatus(fstream & file)
{
    bool fileStatus = false;
    if (file.good() == true)
    {
        fileStatus = true;
    }
    return fileStatus;
}

vector<Person> loadPhoneBook()
{
    fstream file;
    string fileName="AddressBook.txt", fileLine;
    vector<Person> persons;
    file.open(fileName, ios::in);

    int peopleNumbers = 0;
    bool fileStatus = checkFileStatus(file);
    if (fileStatus == true)
    {
        while(getline(file, fileLine))
        {
            persons = loadPersonFromPhoneBook(fileLine, persons);
            peopleNumbers++;
        }
    }
    file.close();
//    system("pause");
    return persons;
}

void savePersonDataToFile(fstream & file, Person person)
{
    file << person.id << "|" << person.name << "|" << person.surname << "|" << person.nr_tel;
    file << "|" << person.email << "|" << person.adress<< "|" << endl;
}

void savePersonToFile(vector<Person> persons)
{
    fstream file;
    string fileName="AddressBook.txt";
    bool fileStatus = checkFileStatus(file);
    int peopleNumber = persons.size() -1;

    if (fileStatus == true)
    {
        file.open(fileName, ios_base::app );
    }
    else
    {
        file.open(fileName, ios_base::out );
    }
    savePersonDataToFile(file, persons[peopleNumber]);

	file.close();

    cout << "Changes saved.." << endl;
    system("pause");
}

void savePhoneBookToFile(vector<Person> persons)
{
    fstream file;
    bool fileStatus;
    char fileName[]="AddressBook.txt";
    fileStatus = checkFileStatus(file);
    if (fileStatus == true)
    {
        remove(fileName);
    }
    file.open(fileName, ios_base::out );
    int personSize = persons.size();
    for (int i=0; i<personSize; i++)
    {
        savePersonDataToFile(file, persons[i]);
    }

    file.close();

    cout << "Changes saved.." << endl;
    system("pause");
}

vector<Person> addNewPerson(vector<Person> persons)
{
    int id = 0;
    string name, surname, adress, email, nr_tel, fileName="AddressBook.txt";
    int personNumber = persons.size();

    persons.push_back(Person());

    cout << "Enter the name: " << endl;
    cin.sync();
    getline(cin, name);
    persons[personNumber].name = name;

    cout << "Enter the surname: " << endl;
    getline(cin, surname);
    persons[personNumber].surname = surname;

    cout << "Enter phone number: " << endl;
    getline(cin, nr_tel);
    persons[personNumber].nr_tel = nr_tel;

    cout << "Enter the e-mail: " << endl;
    getline(cin, email);
    persons[personNumber].email = email;

    cout << "Enter the address: " << endl;
    getline(cin, adress);
    persons[personNumber].adress = adress;

    if (personNumber==0)
    {
        id = 1;
        persons[personNumber].id = id;
    }
    else
    {
        id = persons[personNumber-1].id + 1;
        persons[personNumber].id= id;
    }
    savePersonToFile(persons);

   return persons;
}

void displayPersonData(Person person)
{
    string fileLine, id, name, surname, email, nr_tel, adress;

    cout << person.id << ". " << person.name << " " << person.surname << " " << endl;
    cout << "phone number: " << person.nr_tel << endl;
    cout << "e-mail: " << person.email << endl;
    cout << "address: " << person.adress << endl;
}

void displayPhoneBook(vector<Person> persons)
{
    int personSize = persons.size();
    for (int i=0; i< personSize; i++)
    {
        displayPersonData(persons[i]);
    }
}

int findPersonIDByName(vector<Person> persons)
{
    int idNumber =0;
    string name;
    cout << "Enter the name: " << endl;
    cin.sync();
    getline(cin, name);

    int peopleNumber = persons.size();
    for (int i=0; i< peopleNumber; i++)
    {
        if (persons[i].name == name)
        {
            displayPersonData(persons[i]);
            idNumber = persons[i].id;
        }
    }
    return idNumber;
}

int findPersonIDBySurname(vector<Person> persons)
{
    int idNumber =0;
    string surname;
    cout << "Enter the surname: " << endl;
    cin.sync();
    getline(cin, surname);

    int peopleNumber = persons.size();
    for (int i=0; i< peopleNumber; i++)
    {
        if (persons[i].surname == surname)
        {
            displayPersonData(persons[i]);
            idNumber = persons[i].id;
        }
    }
    return idNumber;
}

string getDataFromStdin(string dataTochange)
{
    string name;
    cout << "Enter" << dataTochange << endl;
    cin.sync();
    getline(cin, name);
    return name;
}

vector<Person> editPersonData(vector<Person> persons)
{
    int id;
    char choice;
    string name, surname, nr_tel, email, adress;
    cout << "Enter the ID number of Addressee whose data you want to change:" << endl;
    cin >> id;

    int personSize = persons.size();
    for (int i=0; i<personSize; i++)
    {
        if (persons[i].id == id)
        {
            system("cls");
            cout << "1. name" << endl;
            cout << "2. surname" << endl;
            cout << "3. phone number" << endl;
            cout << "4. e-mail" << endl;
            cout << "5. address" << endl;
            cout << "6. back to the menu" << endl;
            cin >> choice;
            switch(choice)
            {
            case '1':
                {
                    name = getDataFromStdin(" new name:");
                    persons[i].name = name;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '2':
                {
                    surname = getDataFromStdin(" new surname:");
                    persons[i].surname = surname;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '3':
                {
                    nr_tel = getDataFromStdin(" new phone number:");
                    persons[i].nr_tel = nr_tel;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '4':
                {
                    email = getDataFromStdin(" new e-mail:");
                    persons[i].email = email;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '5':
                {
                    adress = getDataFromStdin(" new address:");
                    persons[i].adress = adress;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '6':
                exit(0);
            default:
            cout << "There is no such option!" << endl;
            Sleep(1000);
            }
            return persons;
        }
    }
    cout << "There is no such ID number!" << endl;
    Sleep(1000);
    return persons;
}

vector<Person> deletePerson(vector<Person> persons)
{
    int id;
    cout << "Enter the ID number of Addressee whose data you want to delete:" << endl;
    cin >> id;

    int peopleNumber = persons.size();
    for (int i=0; i<peopleNumber; i++)
    {
        if (persons[i].id ==id)
        {
            cout << "Are you sure you want to delete the contact data:" << endl;
            displayPersonData(persons[i]);
            cout << "Yes - press 'y', no - press 'n'" << endl;
            cin.sync();
            char answear = getch();
            if (answear == 't')
            {
                persons.erase(persons.begin()+i);
                savePhoneBookToFile(persons);
            }
            return persons;
        }
    }
    cout << "There is no such ID number!" << endl;
    Sleep(1500);
    return persons;
}

int main()
{
    vector<Person> persons;
    int peopleNumber =0;
    int id = 0;
    string fileLine;
    char choice;

    persons = loadPhoneBook();
    if (persons.size()!=0)
    {
        system("pause");
    }

    while (true)
    {
        system("cls");
        cout << "1. Save new contacts" << endl;
        cout << "2. Search by name" << endl;
        cout << "3. Search by surname" << endl;
        cout << "4. Display all contacts" << endl;
        cout << "5. Delete contact" << endl;
        cout << "6. Edit contact" << endl;
        cout << "9. End the program" << endl;
        cout << "Your choice:" << endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            {
                persons = addNewPerson(persons);
                break;
            }
        case '2':
            {
                id = findPersonIDByName(persons);
                if (id == 0)
                {
                    cout << "There is no person with that name." << endl;
                }
                system("pause");
                break;
            }
        case '3':
            {
                id = findPersonIDBySurname(persons);
                if (id == 0)
                {
                    cout << "There is no person with that surname." << endl;
                }
                system("pause");
                break;
            }
        case '4':
            if (persons.size()==0)
            {
                cout << "There are no saved contacts yet!" << endl;
                Sleep(1500);
            }
            else
            {
                displayPhoneBook(persons);
                system("pause");
            }
            break;
        case '5':
            {
                persons = deletePerson(persons);
                break;
            }
        case '6':
            {
                persons = editPersonData(persons);
                break;
            }
        case '9':
            exit(0);

        default:
            cout << "There is no such option!" << endl;
            system("pause");
            break;
        }
    }
     return 0;
}
