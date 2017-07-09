#ifndef DATA
#define DATA

#include <string>
//#include "vs_data.h"
//#include "color.h"
#include <iostream>
#include <QString>
#include <stdlib.h>
#include<string>
#include<sstream>
#include <vector>

using namespace std;



class Data
{
public:

    QString name;
    int value;

public:

    void setName(QString name);
    void setValue(int value);
//    void changeName(QString);
//    void changeValue(int value);

    QString getName();
    int getValue();

    static void saveData(vector <Data> *D,ofstream &save);
    static void swapData(vector <Data> *D,int n1,int n2);
    static void openData(vector <Data> *D,ifstream &read);

};


#endif // DATA

