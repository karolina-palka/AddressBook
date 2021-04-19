#ifndef DECLARATIONS_COMMON_H_INCLUDED
#define DECLARATIONS_COMMON_H_INCLUDED
#include <iostream>
using namespace std;

string substractString(string stringToSubstract, int firstCharPosition);
int convertStringToInteger(string stringToConvert);
string readLinePart(string fileLine, int* start);
char getSingleChar();
bool checkFileStatus(fstream & file);
string getDataFromStdin(string dataTochange);
int getInteger();
#endif // DEFINITIONS_COMMON_H_INCLUDED
