#ifndef VSDATA
#define VSDATA

#include <string>
#include "data.h"
#include "vsdata.h"
#include <iostream>
#include <QString>
#include <QIcon>
#include <QWidget>


#include <vector>

using namespace std;

class VsData : public Data
{
public:

//    QString name;
//    int value;
    int value1;

public:

//    void setName(QString name);
//    void setValue(int value);
//    void changeName(QString);
//    void changeValue(int value);
      void setValueOne(int value1);

//    QString getName();
//    int getValue();
      int getValueOne();

      static void saveVsData(vector <VsData> *D,ofstream &save);
      static void swapVsData(vector <VsData> *D,int n1,int n2);
      static void openVsData(vector <VsData> *D,ifstream &read);

};

#endif // VSDATA
