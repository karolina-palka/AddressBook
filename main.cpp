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
    cout << "nr tel: " << persons[peopleNumber].nr_tel << endl;
    cout << "adress e-mail: " << persons[peopleNumber].email << endl;
    cout << "adres zamieszkania: " << persons[peopleNumber].adress<< endl;

    return persons;
}

bool CheckFileStatus(fstream & file)
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
    string fileName="ksiazka_adresowa.txt", fileLine;
    vector<Person> persons;
    file.open(fileName, ios::in);

    int peopleNumbers = 0;
    bool fileStatus = CheckFileStatus(file);
    if (fileStatus == true)
    {
        while(getline(file, fileLine))
        {
            persons = loadPersonFromPhoneBook(fileLine, persons);
            peopleNumbers++;
        }
    }
    file.close();
    system("pause");
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
    string fileName="ksiazka_adresowa.txt";
    bool fileStatus = CheckFileStatus(file);
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

    cout << "Zapisano." << endl;
    system("pause");
}

void savePhoneBookToFile(vector<Person> persons)
{
    fstream file;
    bool fileStatus;
    char fileName[]="ksiazka_adresowa.txt";
    fileStatus = CheckFileStatus(file);
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

    cout << "Zapisano." << endl;
    system("pause");
}

vector<Person> addNewPerson(vector<Person> persons)
{
    int id = 0;
    string name, surname, adress, email, nr_tel, fileName="ksiazka_adresowa.txt";
    int personNumber = persons.size();

    persons.push_back(Person());

    cout << "Podaj imie: " << endl;
    cin.sync();
    getline(cin, name);
    persons[personNumber].name = name;

    cout << "Podaj nazwisko: " << endl;
    getline(cin, surname);
    persons[personNumber].surname = surname;

    cout << "Podaj numer telefonu: " << endl;
    getline(cin, nr_tel);
    persons[personNumber].nr_tel = nr_tel;

    cout << "Podaj adres e-mail: " << endl;
    getline(cin, email);
    persons[personNumber].email = email;

    cout << "Podaj adres zamieszkania: " << endl;
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
    cout << "nr tel: " << person.nr_tel << endl;
    cout << "adres e-mail: " << person.email << endl;
    cout << "adres zamieszkania: " << person.adress << endl;
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
    cout << "Podaj imie: " << endl;
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
    cout << "Podaj nazwisko: " << endl;
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
    cout << "Wprowadz" << dataTochange << endl;
    cin.sync();
    getline(cin, name);
    return name;
}

vector<Person> editPersonData(vector<Person> persons)
{
    int id;
    char choice;
    string name, surname, nr_tel, email, adress;
    cout << "Wpisz numer ID Adresata, ktorego dane chcesz zmienic:" << endl;
    cin >> id;

    int personSize = persons.size();
    for (int i=0; i<personSize; i++)
    {
        if (persons[i].id == id)
        {
            system("cls");
            cout << "1. imie" << endl;
            cout << "2. nazwisko" << endl;
            cout << "3. numer telefonu" << endl;
            cout << "4. email" << endl;
            cout << "5. adres" << endl;
            cout << "6. powrot do menu" << endl;
            cin >> choice;
            switch(choice)
            {
            case '1':
                {
                    name = getDataFromStdin(" nowe imie:");
                    persons[i].name = name;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '2':
                {
                    surname = getDataFromStdin(" nowe nazwisko:");
                    persons[i].surname = surname;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '3':
                {
                    nr_tel = getDataFromStdin(" nowy numer telefonu:");
                    persons[i].nr_tel = nr_tel;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '4':
                {
                    email = getDataFromStdin(" nowy adres e-mail:");
                    persons[i].email = email;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '5':
                {
                    adress = getDataFromStdin(" nowy adres zamieszkania:");
                    persons[i].adress = adress;
                    savePhoneBookToFile(persons);
                    break;
                }
            case '6':
                exit(0);
            default:
            cout << "Nie ma takiej opcji w menu!" << endl;
            Sleep(1000);
            }
            return persons;
        }
    }
    cout << "Nie ma takiego numeru ID!" << endl;
    Sleep(1000);
    return persons;
}

vector<Person> deletePerson(vector<Person> persons)
{
    int id;
    cout << "Wpisz numer ID Adresata, ktorego chcesz usunac:" << endl;
    cin >> id;

    int peopleNumber = persons.size();
    for (int i=0; i<peopleNumber; i++)
    {
        if (persons[i].id ==id)
        {
            cout << "Jestes pewien, ze chcesz usunac kontakt:" << endl;
            displayPersonData(persons[i]);
            cout << "Tak - wcisnij 't', nie - wcisnij 'n'" << endl;
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
    cout << "Nie ma takiego numeru ID!" << endl;
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

    while (true)
    {
        system("cls");
        cout << "1. Zapisz nowe kontakty" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "6. Edytuj kontakt" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor:" << endl;
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
                    cout << "Nie ma osoby o takim imieniu." << endl;
                }
                system("pause");
                break;
            }
        case '3':
            {
                id = findPersonIDBySurname(persons);
                if (id == 0)
                {
                    cout << "Nie ma osoby o takim nazwisku." << endl;
                }
                system("pause");
                break;
            }
        case '4':
            if (persons.size()==0)
            {
                cout << "Nie masz jeszcze zapisanych kontaktow!" << endl;
                Sleep(1500);
            }
            displayPhoneBook(persons);
            system("pause");
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
            cout << "Nie ma takiej opcji w menu!" << endl;
            Sleep(1500);
        }
    }
     return 0;
}
