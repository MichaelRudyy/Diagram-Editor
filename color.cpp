#include "data.h"
#include "color.h"
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

void Color::setColor(int color)
{
    this->color=color;
}

int Color::getColor()
{
    return color;
}

void Color::saveColor(vector <Color> *D,ofstream &save,int n)
{
    string str;
    Color T;

    if(n==1)
    {
        str="1";
        save<<str<<endl;
    }
    if(n==2)
    {
        str="2";
        save<<str<<endl;
    }
    for(int i=0;i<D->size();i++)
    {
        T=D->at(i);

        str=(T.getName().toStdString());
        save<<str<<endl;

        str=(QString::number(T.getValue())).toStdString();
        save<<str<<endl;

        str=(QString::number(T.getColor())).toStdString();
        save<<str<<endl;
    }
}

void Color::swapColor(vector <Color> *D,int n1,int n2)
{
    swap(D[n1],D[n2]);
}

void Color::openColor(vector <Color> *D,ifstream &read)
{
    Color T;
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
        T.setColor(a);

        D->push_back(T);
    }

}


void Color::sortColor(vector <Color> *D,int n)
{
    /*
void bubble_sort(T array[], std::size_t size)
{
    for (std::size_t idx_i = 0; idx_i < size - 1; idx_i++)
    {
        for (std::size_t idx_j = 0; idx_j < size - idx_i - 1; idx_j++)
        {
            if (array[idx_j + 1] < array[idx_j])
            {
                std::swap(array[idx_j], array[idx_j + 1]);
            }
        }
    }
}*/
    QString strtemp;
    int Vtemp;
    int Ctemp;

    for(unsigned int i=0;i<((D->size())-1);i++)
    {
        for(unsigned int j=0;j<((D->size())-1);j++)
        {
            if((D->at(j).getValue())>(D->at(j+1).getValue()))
            {
                //swap(D[j],D[j+1]);
                Vtemp=D->at(j).getValue();
                Ctemp=D->at(j).getColor();
                strtemp=D->at(j).getName();

                D->at(j).setValue(D->at(j+1).getValue());
                D->at(j).setColor(D->at(j+1).getColor());
                D->at(j).setName(D->at(j+1).getName());

                D->at(j+1).setValue(Vtemp);
                D->at(j+1).setColor(Ctemp);
                D->at(j+1).setName(strtemp);
            }
        }
    }
}
