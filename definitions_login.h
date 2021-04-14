#ifndef DEFINITIONS_LOGO_H_INCLUDED
#define DEFINITIONS_LOGO_H_INCLUDED

struct User
{
    int id;
    string username, password;
};

vector<User> loadUserData(string fileLine, vector<User> users)
{
    int intID;

    string id="", username="", password="", stringID="";
    int startPosition=0;
    int userNumber = users.size();
    users.push_back(User());

    id = readLinePart(fileLine, &startPosition);
    stringID = substractString(id, 0);
    intID = convertStringToInteger(stringID);
    users[userNumber].id = intID;

    users[userNumber].username = readLinePart(fileLine, &startPosition);
    users[userNumber].password = readLinePart(fileLine, &startPosition);

    return users;
}

vector<User> loadUsers()
{
    fstream file;
    string fileName="users.txt", fileLine;
    vector<User> users;
    file.open(fileName, ios::in);

    int usersNumber = 0;
    bool fileStatus = checkFileStatus(file);
    if (fileStatus == true)
    {
        while(getline(file, fileLine))
        {
            users = loadUserData(fileLine, users);
            usersNumber++;
        }
    }
    file.close();
    return users;
}

void saveAllUsersToFile(vector<User> users)
{
    fstream file;
    bool fileStatus;
    char fileName[]="users.txt";
    fileStatus = checkFileStatus(file);
    if (fileStatus == true)
    {
        remove(fileName);
    }
    file.open(fileName, ios_base::out );
    int userNumber = users.size();
    for (int i=0; i<userNumber; i++)
    {
        file << users[i].id << "|" << users[i].username << "|";
        file << users[i].password << "|" << endl;
    }

    file.close();

    cout << "Changes saved." << endl;
    system("pause");
}

void saveUserToFile(vector<User> users)
{
    fstream file;
    string fileName="users.txt";
    int userNumber = users.size() -1;

    file.open(fileName, ios_base::app );
    file << users[userNumber].id << "|" << users[userNumber].username << "|";
    file << users[userNumber].password << "|" << endl;

    file.close();

    cout << "Changes saved." << endl;
    system("pause");
}

vector <User> createNewAccount(vector <User> users)
{
    string username, password;
    cout << "Enter the username" << endl;
    cin >> username;
    int usersNumber = users.size();
    int i =0;
    while (i < usersNumber)
    {
        if ( users[i].username == username)
        {
            cout << "The given username already exists. Please enter a different name." << endl;
            cin >> username;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Enter password: " << endl;
    cin >> password;
    users.push_back(User());

    users[usersNumber].username = username;
    users[usersNumber].password = password;
    users[usersNumber].id = usersNumber + 1;
    cout << "User account created:" << endl;
    cout << users[usersNumber].username << endl;
    saveUserToFile(users);
    Sleep(1000);
    return users;
}

int checkPasswordUpToThreeTimes(User user, string username)
{
    int id=0;
    string password="";
    if (user.username == username)
    {
        for (int j=0; j<3; j++)
        {
            cout << "Enter password. It's your " << j+1 << " trial." << endl;
            cin >> password;
            if (password == user.password)
            {
                id = user.id;
                cout << "You are logged in." << endl;
                return id;
            }
        }
        cout << "You entered an incorrect password 3 times. The program will stop for 3 seconds." <<endl;
        id = -1;
        Sleep(3000);
    }
    return id;
}

int logInToUserAccount(vector <User> users)
{
    int i =0, id =0;
    string username, password;
    cout << "Enter the username: " << endl;
    cin >> username;
    int usersNumber = users.size();
    while (i < usersNumber)
    {
        id = checkPasswordUpToThreeTimes(users[i], username);
        if (id ==-1)
        {
            return id;
        }
        else if (id> 0)
        {
            break;
        }
        i++;
    }
    Sleep(1500);
    return id;
}

vector<User> passwordChange(vector <User> users, int id)
{
    string password;
    int usersNumber = users.size();
    for (int i=0; i<usersNumber; i++)
    {
        if (id == users[i].id)
        {
            cout << "Enter new password: " << endl;
            cin >> password;
            users[i].password = password;
            cout << "The password has been changed." << endl;
            Sleep(1500);
        }
    }
    saveAllUsersToFile(users);
    return users;
}

#endif // DEFINITIONS_LOGO_H_INCLUDED
