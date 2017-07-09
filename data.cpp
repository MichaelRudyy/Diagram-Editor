#include "data.h"
#include <fstream>
#include <ctime>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
//#include "color.h"

using namespace std;

void Data::setName(QString name)
{
    this->name=name;
}

void Data::setValue(int value)
{
    this->value=value;
}

QString Data::getName()
{
    return name;
}

int Data::getValue()
{
    return value;
}

void Data::saveData(vector <Data> *D,ofstream &f)
{
    string str;
    Data T;
    str="3";
    f<<str<<endl;
    for(int i=0;i<D->size();i++)
    {
        T=D->at(i);

        str=(T.getName().toStdString());
        f<<str<<endl;

        str=((QString::number(T.getValue())).toStdString());
        f<<str<<endl;
    }

}
void Data::swapData(vector <Data> *D,int n1,int n2)
{
    swap(D[n1],D[n2]);
}

void Data::openData(vector <Data> *D,ifstream &read)
{
    Data T;
    char *buf=new char[50];
    string str;
    int a;
    read.getline(buf,49);


    while(!read.eof())
    {
        read.getline(buf,49);
        str=buf;
        T.setName(QString::fromStdString(str));

        read.getline(buf,49);
        str=buf;
        std::istringstream ss(str);
        ss>>a;
        //a=atoi(str);
        T.setValue(a);

        D->push_back(T);
    }
}
