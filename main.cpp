#include <iostream>

#include "declarations_login.h"
#include "declarations_addressBook.h"
#include "declarations_common.h"

using namespace std;

int main()
{
    vector<Person> persons;
    vector<User> users;
    int addresseeID = 0, foundID=0;
    int loggedUserID =0;
    string fileLine="", lineToExtractAddresseeID="";
    char choice;

    users = loadUsers();

    while (true)
    {
        if (loggedUserID <=0)
        {
            system("cls");
            cout << "1. Register" << endl;
            cout << "2. Log in" << endl;
            cout << "3. End the program" << endl;
            cout << "Your choice:" << endl;
            choice = getSingleChar();
            switch (choice)
            {
            case '1':
            {
                users = createNewAccount(users);
                break;
            }
            case '2':
            {
                loggedUserID = logInToUserAccount(users);
                if (loggedUserID == 0)
                {
                    cout << "The given username does not exist. Please try again or register." << endl;
                    Sleep(1500);
                }
                else if (loggedUserID > 0)
                {
                    cout << "Logged in user ID: " << loggedUserID << endl;
                    persons = loadPhoneBook(loggedUserID, lineToExtractAddresseeID);
                    addresseeID = setNextAddresseeIDNumber(lineToExtractAddresseeID);
                    if (persons.size()!=0)
                    {
                        system("pause");
                    }
                    Sleep(1500);
                }
                break;
            }
            case '3':
                exit(0);
            default:
                cout << "There is no such option!" << endl;
                system("pause");
                break;
            }
        }
        else
        {
            system("cls");
            cout << "1. Save new contacts" << endl;
            cout << "2. Search by name" << endl;
            cout << "3. Search by surname" << endl;
            cout << "4. Display all contacts" << endl;
            cout << "5. Delete contact" << endl;
            cout << "6. Edit contact" << endl;
            cout << "7. Change password" << endl;
            cout << "8. Log out" << endl;
            cout << "9. End the program" << endl;
            cout << "Your choice:" << endl;
            choice = getSingleChar();
            switch (choice)
            {
            case '1':
            {
                addresseeID = getAddresseIDNumberFromFile();
                persons = addNewPerson(persons, loggedUserID, addresseeID);
                break;
            }
            case '2':
            {
                foundID = findPersonIDByName(persons);
                if (foundID == 0)
                {
                    cout << "There is no person with that name." << endl;
                }
                system("pause");
                break;
            }
            case '3':
            {
                foundID = findPersonIDBySurname(persons);
                if (foundID == 0)
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
                    displayPhoneBook(persons, loggedUserID);
                    system("pause");
                }
                break;
            case '5':
            {
                persons = deletePerson(persons, loggedUserID);
                break;
            }
            case '6':
            {
                persons = editPersonData(persons, loggedUserID);
                break;
            }
            case '7':
            {
                users = passwordChange(users, loggedUserID);
                break;
            }
            case '8':
            {
                loggedUserID =0;
                Sleep(1300);
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
    }
    return 0;
}
