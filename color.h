#ifndef COLOR
#define COLOR

#include <string>
//#include "vs_data.h"
#include "data.h"
#include "color.h"
#include <iostream>
#include <QString>
#include <QIcon>
#include <QWidget>


#include <vector>

using namespace std;

class Color : public Data
{
public:

//    QString name;
//    int value;
    int color;

public:

//    void setName(QString name);
//    void setValue(int value);
//    void changeName(QString);
//    void changeValue(int value);
      void setColor(int color);

//    QString getName();
//    int getValue();
      int getColor();

      static void saveColor(vector <Color> *D,ofstream &save,int n);
      static void swapColor(vector <Color> *D,int n1,int n2);
      static void openColor(vector <Color> *D,ifstream &read);
      static void sortColor(vector <Color> *D,int n);

};

#endif // COLOR

