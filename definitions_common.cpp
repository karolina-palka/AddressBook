#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include "declarations_common.h"
using namespace std;

string substractString(string stringToSubstract, int firstCharPosition)
{
    int stringLength = stringToSubstract.length();
    string stringSubstracted = stringToSubstract.substr(firstCharPosition, stringLength);
    return stringSubstracted;
}

int convertStringToInteger(string stringToConvert)
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
char getSingleChar()
{
    string input = "";
    char singleChar  = {0};
    cin.sync();

    while (true)
    {
        getline(cin, input);

        if (input.length() == 1)
        {
            singleChar = input[0];
            break;
        }
        cout << "This is not a single character. Please enter your choice again." << endl;
    }
    return singleChar;
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
string getDataFromStdin(string dataTochange)
{
    string name;
    cout << "Enter" << dataTochange << endl;
    cin.sync();
    getline(cin, name);
    return name;
}

int getInteger()
{
    string input = "";
    int number = 0;
    cin.sync();
    while (true)
    {
        getline(cin, input);

        stringstream myStream(input);
        if (myStream >> number)
            break;
        cout << "This is not a number. Try again. " << endl;
    }
    return number;
}
