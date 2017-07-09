#ifndef DIAGRAMEDITOR_H
#define DIAGRAMEDITOR_H

#include <QMainWindow>
#include <vector>
#include <data.h>
#include <color.h>
#include <vsdata.h>
#include <QIcon>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QColor>
#include <math.h>
#include <QFont>
#include <vector>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <cstring>
#include <stdlib.h>


namespace Ui {
class DiagramEditor;
}

class DiagramEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiagramEditor(QWidget *parent = 0);
    ~DiagramEditor();
    vector <Color> Columnar_diag;
    vector <Data> Linear_diag;
    vector <Color> Circle_diag;
    vector <VsData> Linear_vs_diag;
    int open_numb_diagram=0;

private slots:

    void DrowColumnar();

    void DrowCircle();

    void DrowLinear();

    void DrowLinearVs();

    void TableColumnar();

    void TableCircle();

    void TableLinear();

    void TableLinearVs();

    void on_Edit_tab_destroyed();

    void on_Columnar_b_clicked();

    void on_Circle_b_clicked();

    void on_Linear_b_clicked();

    void on_Linear_vs_b_clicked();

    void on_Edit_b_clicked();

    void on_Table_Columnar_activated(const QModelIndex &index);

    void on_OK_1_b_clicked();

    void on_OK_1_b_3_clicked();

    void on_OK_1_b_5_clicked();

    void on_OK_1_b_6_clicked();

    void on_Add_Columnar_clicked();

    void on_Columnar_color_clicked();

    void on_Back_b_1_clicked();

    void on_Columnar_delete_clicked();

    void on_Back_b_4_clicked();

    void on_Circle_color_clicked();

    void on_Add_Circle_clicked();

    void on_Circle_delete_clicked();

    void on_Add_Linear_clicked();

    void on_Linear_delete_clicked();

    void on_Add_Linear_vs_clicked();

    void on_Linear_vs_delete_clicked();

    void on_Delete_b_clicked();

    void on_Save_b_clicked();

    void on_Linear_vs_color_clicked();

    void on_Columnar_Swap_b_clicked();

    void on_Circle_Swap_b_2_clicked();

    void on_Linear_Swap_b_clicked();

    void on_Linear_vs_Swap_b_clicked();

    void on_Open_b_clicked();

    void on_Columnar_Table_activated(const QModelIndex &index);

    void on_Columnar_sort_b_clicked();

    void on_pushButton_clicked();

    void on_Columnar_sort1_b_clicked();

    void on_Columnar_value_editingFinished();

    void on_ALERT_Columnar_1_linkActivated(const QString &link);

private:
    Ui::DiagramEditor *ui;
};

#endif // DIAGRAMEDITOR_H
