#ifndef DEFINITIONS_ADDRESSBOOK_H_INCLUDED
#define DEFINITIONS_ADDRESSBOOK_H_INCLUDED
struct Person
{
    int id, userID;
    string name, surname, email, adress, nr_tel;
};

vector<Person> loadPersonFromPhoneBook(string* fileLine, vector<Person> persons, int loggedUserID)
{
    string id="", name="", surname="", email="", nr_tel="", adress="", stringID="", loggedUserIDstr;
    int startPosition=0, intID, userID;
    int peopleNumber = persons.size();

    id = readLinePart(*fileLine, &startPosition);
    stringID = substractString(id, 0);
    intID = convertStringToInteger(stringID);

    loggedUserIDstr = readLinePart(*fileLine, &startPosition);
    stringID = substractString(loggedUserIDstr, 0);
    userID = convertStringToInteger(stringID);

    if (loggedUserID== userID)
    {
        persons.push_back(Person());
        persons[peopleNumber].id = intID;
        persons[peopleNumber].userID = userID;
        persons[peopleNumber].name = readLinePart(*fileLine, &startPosition);
        persons[peopleNumber].surname = readLinePart(*fileLine, &startPosition);
        persons[peopleNumber].nr_tel = readLinePart(*fileLine, &startPosition);
        persons[peopleNumber].email= readLinePart(*fileLine, &startPosition);
        persons[peopleNumber].adress = readLinePart(*fileLine, &startPosition);

        cout << persons[peopleNumber].id << ". " << persons[peopleNumber].name;
        cout << " " << persons[peopleNumber].surname  << " " << endl;
        cout << "phone number: " << persons[peopleNumber].nr_tel << endl;
        cout << "e-mail address: " << persons[peopleNumber].email << endl;
        cout << "address: " << persons[peopleNumber].adress<< endl;
    }
    return persons;
}

int setNextAddresseeIDNumber(string line)
{
    int position=0;
    string stringID = readLinePart(line, &position);
    stringID = substractString(stringID, 0);
    int ID = convertStringToInteger(stringID);
    int addresseID = ID +1;
    return addresseID;
}

vector<Person> loadPhoneBook(int loggedUserID, string* lineToExtractAddresseeID)
{
    fstream file;
    string fileName="AddressBook.txt", fileLine="";
    vector<Person> persons;
    file.open(fileName, ios::in);

    bool fileStatus = checkFileStatus(file);
    cin.sync();
    if (fileStatus == true)
    {
        while(getline(file, fileLine))
        {
            *lineToExtractAddresseeID = fileLine;
            persons = loadPersonFromPhoneBook(&fileLine, persons, loggedUserID);
        }
        file.close();
    }

    return persons;
}

void savePersonDataToFile(fstream & file, Person person)
{
    file << person.id << "|" << person.userID << "|" << person.name << "|" << person.surname << "|" << person.nr_tel;
    file << "|" << person.email << "|" << person.adress<< "|" << endl;
}

void savePersonToFile(vector<Person> persons, string fileName, int ID)
{
    fstream file;
    int peopleNumber=0;

    peopleNumber = persons.size() -1;

    file.open(fileName, ios_base::app );

    savePersonDataToFile(file, persons[peopleNumber]);
    file.close();

    cout << "Changes saved.." << endl;
    system("pause");
}

void saveEditedPhoneBookToFile(Person person, int addresseeID)
{
    fstream file, fileTmp;
    char fileName[]="AddressBook.txt", fileNameTmp[] ="temp.txt";
    int IDFromFile;
    string fileLine="", idStr, idUser="", stringID="";

    file.open(fileName, ios_base::in );
    fileTmp.open(fileNameTmp, ios_base::out );
    cin.sync();

    while(getline(file, fileLine))
    {
        int startPosition=0;
        idStr = readLinePart(fileLine, &startPosition);
        stringID = substractString(idStr, 0);
        IDFromFile = convertStringToInteger(stringID);
        stringID="";

        if (IDFromFile == addresseeID)
        {
            savePersonDataToFile(fileTmp, person);

        }
        else
        {
            fileTmp << fileLine << endl;
        }
    }
    file.close();
    fileTmp.close();
    remove(fileName);
    rename(fileNameTmp, fileName);

    cout << "Changes saved." << endl;
    system("pause");
}

void saveDeletedPersonToFile(int addresseeID)
{
    fstream file, fileTmp;
    char fileName[]="AddressBook.txt", fileNameTmp[] ="temp.txt";
    int IDFromFile;
    string fileLine="", idStr, idUser="", stringID="";

    file.open(fileName, ios_base::in );
    fileTmp.open(fileNameTmp, ios_base::out );
    cin.sync();

    while(getline(file, fileLine))
    {
        int startPosition=0;
        idStr = readLinePart(fileLine, &startPosition);
        stringID = substractString(idStr, 0);
        IDFromFile = convertStringToInteger(stringID);
        stringID="";

        if (IDFromFile != addresseeID)
        {
            fileTmp << fileLine << endl;

        }
    }
    file.close();
    fileTmp.close();
    remove(fileName);
    rename(fileNameTmp, fileName);

    cout << "Changes saved." << endl;
    system("pause");
}

vector<Person> addNewPerson(vector<Person> persons, int loggedUserID, int* addresseeID)
{
    string name, surname, adress, email, nr_tel, fileName="AddressBook.txt";
    int personNumber = persons.size();
    cout << "personNumber: " << personNumber << endl;

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
    persons[personNumber].userID = loggedUserID;

    if (*addresseeID==0)
    {
        *addresseeID = 1;
        persons[personNumber].id = *addresseeID;
    }
    else
    {
        persons[personNumber].id = *addresseeID;
        *addresseeID= *addresseeID +1;
    }
    savePersonToFile(persons, fileName, loggedUserID);

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

void displayPhoneBook(vector<Person> persons, int loggedUserID)
{
    int personSize = persons.size();
    for (int i=0; i< personSize; i++)
    {
        if (loggedUserID == persons[i].userID)
        {
             displayPersonData(persons[i]);
        }
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

vector<Person> editPersonData(vector<Person> persons, int loggedUserID)
{
    int id;
    char choice;
    string name, surname, nr_tel, email, adress;
    cout << "Enter the ID number of Addressee whose data you want to change:" << endl;

    id = getInteger();
    string fileName="temp.txt";

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
            displayPersonData( persons[i]);
            choice = getSingleChar();
            switch(choice)
            {
            case '1':
            {
                name = getDataFromStdin(" new name:");
                persons[i].name = name;
                saveEditedPhoneBookToFile(persons[i], id);
                break;
            }
            case '2':
            {
                surname = getDataFromStdin(" new surname:");
                persons[i].surname = surname;
                saveEditedPhoneBookToFile(persons[i], id);
                break;
            }
            case '3':
            {
                nr_tel = getDataFromStdin(" new phone number:");
                persons[i].nr_tel = nr_tel;
                saveEditedPhoneBookToFile(persons[i], id);
                break;
            }
            case '4':
            {
                email = getDataFromStdin(" new e-mail:");
                persons[i].email = email;
                saveEditedPhoneBookToFile(persons[i], id);
                break;
            }
            case '5':
            {
                adress = getDataFromStdin(" new address:");
                persons[i].adress = adress;
                saveEditedPhoneBookToFile(persons[i], id);
                break;
            }
            case '6':
                break;
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

vector<Person> deletePerson(vector<Person> persons, int loggedUserID)
{
    int id;
    cout << "Enter the ID number of Addressee whose data you want to delete:" << endl;

    id = getInteger();

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
            if (answear == 'y')
            {
                persons.erase(persons.begin()+i);
                saveDeletedPersonToFile(id);
                cout << "Deleted." << endl;
            }
            return persons;
        }
    }
    cout << "There is no such ID number!" << endl;
    Sleep(1500);
    return persons;
}

#endif // DEFINITIONS_ADDRESSBOOK_H_INCLUDED
