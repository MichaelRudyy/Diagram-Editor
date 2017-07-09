#include "data.h"
#include "vsdata.h"
#include <fstream>
#include <ctime>

using namespace std;

/*
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
*/

void VsData::setValueOne(int value1)
{
    this->value1=value1;
}

int VsData::getValueOne()
{
    return value1;
}

void VsData::saveVsData(vector <VsData> *D,ofstream &save)
{
    string str;
    VsData T;
    str="4";
    save<<str<<endl;
    for(int i=0;i<D->size();i++)
    {
        T=D->at(i);

        str=((T.getName().toStdString()));
        save<<str<<endl;

        str=(QString::number(T.getValue())).toStdString();
        save<<str<<endl;

        str=(QString::number(T.getValueOne())).toStdString();
        save<<str<<endl;
    }

}

void VsData::swapVsData(vector <VsData> *D,int n1,int n2)
{
    swap(D[n1],D[n2]);
}

void VsData::openVsData(vector <VsData> *D,ifstream &read)
{
    VsData T;
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

        read.getline(buf,49);
        str=buf;
        std::istringstream as(str);
        as>>a;
        //a=atoi(str);
        T.setValueOne(a);


        D->push_back(T);
    }
}
