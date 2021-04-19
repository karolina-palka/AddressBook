#ifndef DECLARATIONS_LOGO_H_INCLUDED
#define DECLARATIONS_LOGO_H_INCLUDED
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <stdio.h>

using namespace std;

struct User
{
    int id;
    string username, password;
};

vector<User> loadUserData(string fileLine, vector<User> users);
vector<User> loadUsers();
void saveAllUsersToFile(vector<User> users);
void saveUserToFile(vector<User> users);
vector <User> createNewAccount(vector <User> users);
int checkPasswordUpToThreeTimes(User user, string username);
int logInToUserAccount(vector <User> users);
vector<User> passwordChange(vector <User> users, int id);
#endif // DEFINITIONS_LOGO_H_INCLUDED
