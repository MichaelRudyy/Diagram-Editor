#include "diagrameditor.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QtPlugin>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    DiagramEditor w;
    w.show();

    return a.exec();
}
