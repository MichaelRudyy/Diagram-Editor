#include "diagrameditor.h"
#include "ui_diagrameditor.h"
#include <QtCore>
#include <QtGui>
#include <QIcon>
#include <QWidget>
#include <fstream>
#include <vector>


DiagramEditor::DiagramEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiagramEditor)
{
    ui->setupUi(this);
    ui->Grey_color_Columnar->setChecked(true);
    ui->Grey_color_Circle->setChecked(true);
    //QPixmap column("column.ico");
    ui->Delete_b->setStyleSheet("color:red;");
    //ui->Save_b->setStyleSheet("color:grey;");
    //ui->Open_b->setStyleSheet("color:grey;");
    //ui->Save_b->setStyleSheet("background-image: url(001.jpg);");
    //ui->Diag_View->setRenderHint(QPainter::Antialiasing,true);
    //ui->Save_b->setIcon(QIcon("save.ico"));
    //ui->Open_b->setIcon(QIcon("open.ico"));

}

DiagramEditor::~DiagramEditor()
{
    delete ui;
}


void DiagramEditor::DrowColumnar()
{
    QGraphicsScene *scene =new QGraphicsScene(ui->Diag_View);
    ui->Diag_View->setRenderHint(QPainter::Antialiasing,false);

    scene->setBackgroundBrush(QBrush(QColor(250,250,250,125), Qt::Dense7Pattern));


    QPen mainPen(QColor(255,255,255,0));
    mainPen.setWidth(0);
    QPen linePen(Qt::lightGray);
    linePen.setWidth(1);

    //scene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::Dense7Pattern));

    QFont* font= new QFont("Calibri");

    int x,y,w,h;

    for(int i=0;i<Columnar_diag.size();i++)
    {
        x=-250+40*i;
        y=150-20*(Columnar_diag.at(i).getValue());
        w=40;
        h=20*(Columnar_diag.at(i).getValue())-1;
        QLinearGradient grad(x,y,x,y+h);


        scene->addLine(-270,152,-180+40*i,152,linePen);
        scene->addLine(-270,152,-270,-160,linePen);
        //scene->addLine(-272,-159,-270,-162,linePen);
        //scene->addLine(-268,-159,-270,-162,linePen);
        for(int z=0;z<3;z++)
        {
            scene->addLine(-272,50-100*z,-268,50-100*z,linePen);

            QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(5*z+5));
            font->setItalic(true);
            font->setPixelSize(10);
            text->setFont(*font);
            text->setPos(-290,45-100*z);
            text->setDefaultTextColor(Qt::gray);
            scene->addItem(text);

        }
        QGraphicsTextItem *text = new QGraphicsTextItem(Columnar_diag.at(i).getName());

        if(Columnar_diag.at(i).getColor()==0)
        {
            //qstr2="Сірий";
            grad.setColorAt(0.0,QColor(153,153,153,255));
            grad.setColorAt(1.0,QColor(255,255,255,0));
            text->setDefaultTextColor(QColor(153,153,153,255));
        }else
        if(Columnar_diag.at(i).getColor()==1)
        {
            //qstr2="Синій";
            grad.setColorAt(0.0,QColor(51,153,255,255));
            grad.setColorAt(1.0,QColor(0,0,0,0));
            text->setDefaultTextColor(QColor(51,153,255,255));
        }else
        if(Columnar_diag.at(i).getColor()==2)
        {
            //qstr2="Червоний";
            grad.setColorAt(0.0,QColor(204,0,12,255));
            grad.setColorAt(1.0,QColor(0,0,0,0));
            text->setDefaultTextColor(QColor(204,0,102,255));
        }else
        if(Columnar_diag.at(i).getColor()==3)
        {
            //qstr2="Зелений";
            grad.setColorAt(0.0,QColor(204,255,51,255));
            grad.setColorAt(1.0,QColor(0,0,0,0));
            text->setDefaultTextColor(QColor(204,255,51,255));
        }

        scene->addRect(x,y,w,h,mainPen,grad);


        font->setItalic(true);
        font->setPixelSize(14);
        text->setFont(*font);
        text->setPos(x+10,y+h+5);

        text->setRotation(45);
        scene->addItem(text);
    }


    ui->Diag_View->setScene(scene);

}

void DiagramEditor::DrowCircle()
{
    QGraphicsScene *scene =new QGraphicsScene(ui->Diag_View);
    ui->Diag_View->setRenderHint(QPainter::Antialiasing,true);

    scene->setBackgroundBrush(QBrush(QColor(250,250,250,125), Qt::Dense7Pattern));

    QPen CirclePen(Qt::red);
    QPen CirclePen1(Qt::red);
    QPen penWhite(QColor(230,230,230,125));
    penWhite.setWidth(4);
    //scene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::Dense7Pattern));
    int sum=0;
    for(int i=0;i<Circle_diag.size();i++)
    {
        sum=sum+Circle_diag.at(i).getValue();
    }

    double *X = new double[Circle_diag.size()+1];
    X[0]=0.0;
    for(int a=1;a<Circle_diag.size()+1;a++)
    {
      X[a]=(1.0*Circle_diag.at(a-1).getValue()/sum)*360.0;
      X[a]=X[a-1]+X[a];
    }

    float xt,yt,x,y,c;
    c=100;
    xt=c;
    yt=0.0;
    for(float i=0;i<360.0;i=i+0.2)
    {
        y=c*sin(i*3.14/180.0);
        x=sqrt(c*c-y*y);
        y=((-2)*y)/5;
        if((i>90)&&(i<270)){
                x=(-1)*x;
        }
        for(int z=1;z<Circle_diag.size()+1;z++)
        {
            if((i>=X[z-1])&&(i<=X[z]))
            {

                if(Circle_diag.at(z-1).getColor()==0)
                {
                    //qstr2="Сірий";
                    CirclePen.setBrush(QColor(153,153,153,255));
                    CirclePen1.setBrush(QColor(123,123,123,255));
                }else
                if(Circle_diag.at(z-1).getColor()==1)
                {
                    //qstr2="Синій";
                    CirclePen.setBrush(QColor(51,153,255,255));
                    CirclePen1.setBrush(QColor(0,112,223,255));
                }else
                if(Circle_diag.at(z-1).getColor()==2)
                {
                    //qstr2="Червоний";
                    CirclePen.setBrush(QColor(204,0,12,255));
                    CirclePen1.setBrush(QColor(151,0,7,255));
                }else
                if(Circle_diag.at(z-1).getColor()==3)
                {
                    //qstr2="Зелений";
                    CirclePen.setBrush(QColor(204,255,51,255));
                    CirclePen1.setBrush(QColor(102,173,31,255));
                }
            }
        }

        if((i>=180)&&(i<=360)){
                scene->addLine(x,y,x,y+20,CirclePen1);
        }

        scene->addLine(0,0,x,y,CirclePen);
        scene->addLine(xt,yt,x,y,CirclePen);
        xt=x;
        yt=y;

    }

     QRadialGradient grad1(0,0,100);

    grad1.setColorAt(0.3,QColor(255,255,255,255));
   // grad1.setColorAt(0.8,QColor(0,0,0,150));
   // grad1.setColorAt(0.9,QColor(0,0,0,50));
    grad1.setColorAt(1.0,QColor(255,255,255,0));
    //grad1.setColorAt(0.5,Qt::green);


    //grad1.setColorAt(1.0,QColor(237,199,39,0));

    QBrush Bwhite(QColor(255,255,255,125));
    //scene->addEllipse(-50,-50,100,100,penWhite,grad1);

    ui->Diag_View->setScene(scene);

}

void DiagramEditor::DrowLinear()
{
    QGraphicsScene *scene =new QGraphicsScene(ui->Diag_View);
    ui->Diag_View->setRenderHint(QPainter::Antialiasing,true);

    //Lines
    QPen mainPen(QColor(255,102,0,255));
    mainPen.setWidth(2);
    mainPen.setStyle(Qt::SolidLine);
    mainPen.setCapStyle(Qt::RoundCap);
    mainPen.setJoinStyle(Qt::RoundJoin);

    QPen dashPen(QColor(255,102,0,255));
    dashPen.setWidth(1);
    dashPen.setStyle(Qt::DotLine);
    dashPen.setCapStyle(Qt::RoundCap);
    dashPen.setJoinStyle(Qt::RoundJoin);

    QPen linePen(Qt::lightGray);
    linePen.setWidth(1);

    scene->setBackgroundBrush(QBrush(QColor(250,250,250,125), Qt::Dense7Pattern));

    QFont* font= new QFont("Calibri");





    for(int i=0;i<Linear_diag.size();i++)
    {
        QGraphicsTextItem *text = new QGraphicsTextItem(Linear_diag.at(i).getName());

        scene->addLine(-270,150,-180+40*i,150,linePen);
        scene->addLine(-270,150,-270,-160,linePen);
        for(int z=0;z<3;z++)
        {
            scene->addLine(-272,50-100*z,-268,50-100*z,linePen);

            QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(5*z+5));
            font->setItalic(true);
            font->setPixelSize(10);
            text->setFont(*font);
            text->setPos(-290,45-100*z);
            text->setDefaultTextColor(Qt::gray);
            scene->addItem(text);
        }
        scene->addLine(-250+40*i,150-20*Linear_diag.at(i).getValue(),-250+40*i,150,dashPen);
        scene->addEllipse(-250+40*i-2,150-20*Linear_diag.at(i).getValue()-2,4,4,mainPen);

        font->setItalic(true);
        font->setPixelSize(15);
        text->setDefaultTextColor(QColor(255,102,0,255));
        text->setFont(*font);
        text->setPos(-250+40*i,154);
        text->setRotation(45);
        scene->addItem(text);
    }
    for(int i=1;i<Linear_diag.size();i++)
    {

        scene->addLine(-250+40*(i-1),150-20*Linear_diag.at(i-1).getValue(),-250+40*(i),150-20*Linear_diag.at(i).getValue(),mainPen);

    }
    //Lines!!
    ui->Diag_View->setScene(scene);


}

void DiagramEditor::DrowLinearVs()
{
    QGraphicsScene *scene =new QGraphicsScene(ui->Diag_View);
    ui->Diag_View->setRenderHint(QPainter::Antialiasing,true);

    scene->setBackgroundBrush(QBrush(QColor(250,250,250,125), Qt::Dense7Pattern));

    //Lines
    QPen BluePen(QColor(21,204,255,255));
    BluePen.setWidth(2);
    BluePen.setStyle(Qt::SolidLine);
    BluePen.setCapStyle(Qt::RoundCap);
    BluePen.setJoinStyle(Qt::RoundJoin);

    QPen RedPen(QColor(255,51,0,255));
    RedPen.setWidth(2);
    RedPen.setStyle(Qt::SolidLine);
    RedPen.setCapStyle(Qt::RoundCap);
    RedPen.setJoinStyle(Qt::RoundJoin);

    QPen dashPen(QColor(255,102,0,255));
    dashPen.setWidth(1);
    dashPen.setStyle(Qt::DotLine);
    dashPen.setCapStyle(Qt::RoundCap);
    dashPen.setJoinStyle(Qt::RoundJoin);

    QPen linePen(Qt::lightGray);
    linePen.setWidth(1);

    QFont* font= new QFont("Calibri");

    for(int i=0;i<Linear_vs_diag.size();i++)
    {

        QGraphicsTextItem *text = new QGraphicsTextItem(Linear_vs_diag.at(i).getName());

        scene->addLine(-270,150,-180+40*i,150,linePen);
        scene->addLine(-270,150,-270,-160,linePen);
        for(int z=0;z<3;z++)
        {

            scene->addLine(-272,50-100*z,-268,50-100*z,linePen);

            QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(5*z+5));
            font->setItalic(true);
            font->setPixelSize(10);
            text->setFont(*font);
            text->setPos(-290,45-100*z);
            text->setDefaultTextColor(Qt::gray);
            scene->addItem(text);
        }
        scene->addEllipse(-250+40*i-2,150-20*Linear_vs_diag.at(i).getValue()-2,4,4,BluePen);

        scene->addEllipse(-250+40*i-2,150-20*Linear_vs_diag.at(i).getValueOne()-2,4,4,RedPen);

        font->setItalic(true);
        font->setPixelSize(15);
        text->setDefaultTextColor(QColor(230,230,230,255));
        text->setFont(*font);
        text->setPos(-250+40*i,154);
        text->setRotation(45);
        scene->addItem(text);
    }
        //Lines!!

    for(int i=1;i<Linear_vs_diag.size();i++)
    {

        scene->addLine(-250+40*(i-1),150-20*Linear_vs_diag.at(i-1).getValue(),-250+40*(i),150-20*Linear_vs_diag.at(i).getValue(),BluePen);
        scene->addLine(-250+40*(i-1),150-20*Linear_vs_diag.at(i-1).getValueOne(),-250+40*(i),150-20*Linear_vs_diag.at(i).getValueOne(),RedPen);

    }
    ui->Diag_View->setScene(scene);






}

void DiagramEditor::TableColumnar()
{
    QString qstr2;
    ui->Columnar_Table->setRowCount(Columnar_diag.size());
    for(int i=0;i<Columnar_diag.size();i++)
    {
        QString qstr=Columnar_diag.at(i).getName();
        QTableWidgetItem *t_item_1=new QTableWidgetItem(qstr);
        ui->Columnar_Table->setItem(i,0,t_item_1);

        QString qstr1=QString::number(Columnar_diag.at(i).getValue());
        QTableWidgetItem *t_item_2=new QTableWidgetItem(qstr1);
        ui->Columnar_Table->setItem(i,1,t_item_2);

        if(Columnar_diag.at(i).getColor()==0)
        {
            qstr2="Сірий";
            ui->Columnar_Table->item(i,1)->setBackgroundColor(QColor(153,153,153,125));
        }else
        if(Columnar_diag.at(i).getColor()==1)
        {
            qstr2="Синій";
            ui->Columnar_Table->item(i,1)->setBackgroundColor(QColor(51,153,255,125));
        }else
        if(Columnar_diag.at(i).getColor()==2)
        {
            qstr2="Червоний";
            ui->Columnar_Table->item(i,1)->setBackgroundColor(QColor(204,0,12,125));
        }else
        if(Columnar_diag.at(i).getColor()==3)
        {
            qstr2="Зелений";
            ui->Columnar_Table->item(i,1)->setBackgroundColor(QColor(204,255,51,125));
        }
        QTableWidgetItem *t_item_3=new QTableWidgetItem(qstr2);
        ui->Columnar_Table->setItem(i,2,t_item_3);

    }
}

void DiagramEditor::TableCircle()
{
    QString qstr2;

    ui->Circle_Table->setRowCount(Circle_diag.size());
    for(int i=0;i<Circle_diag.size();i++)
    {
        QString qstr=Circle_diag.at(i).getName();
        QTableWidgetItem *t_item_1=new QTableWidgetItem(qstr);
        ui->Circle_Table->setItem(i,0,t_item_1);

        QString qstr1=QString::number(Circle_diag.at(i).getValue());
        QTableWidgetItem *t_item_2=new QTableWidgetItem(qstr1);
        ui->Circle_Table->setItem(i,1,t_item_2);

        if(Circle_diag.at(i).getColor()==0)
        {
            qstr2="Сірий";
            ui->Circle_Table->item(i,1)->setBackgroundColor(QColor(153,153,153,125));
        }else
        if(Circle_diag.at(i).getColor()==1)
        {
            qstr2="Синій";
            ui->Circle_Table->item(i,1)->setBackgroundColor(QColor(51,153,255,125));
        }else
        if(Circle_diag.at(i).getColor()==2)
        {
            qstr2="Червоний";
            ui->Circle_Table->item(i,1)->setBackgroundColor(QColor(204,0,12,125));
        }else
        if(Circle_diag.at(i).getColor()==3)
        {
            qstr2="Зелений";
            ui->Circle_Table->item(i,1)->setBackgroundColor(QColor(204,255,51,125));
        }
        QTableWidgetItem *t_item_3=new QTableWidgetItem(qstr2);
        ui->Circle_Table->setItem(i,2,t_item_3);
    }


}

void DiagramEditor::TableLinear()
{

    ui->Linear_Table->setRowCount(Linear_diag.size());
    for(int i=0;i<Linear_diag.size();i++)
    {
        QString qstr=Linear_diag.at(i).getName();
        QTableWidgetItem *t_item_1=new QTableWidgetItem(qstr);
        ui->Linear_Table->setItem(i,0,t_item_1);

        QString qstr1=QString::number(Linear_diag.at(i).getValue());
        QTableWidgetItem *t_item_2=new QTableWidgetItem(qstr1);
        ui->Linear_Table->setItem(i,1,t_item_2);
    }


}

void DiagramEditor::TableLinearVs()
{
    ui->Linear_vs_Table->setRowCount(Linear_vs_diag.size());
    for(int i=0;i<Linear_vs_diag.size();i++)
    {
        QString qstr=Linear_vs_diag.at(i).getName();
        QTableWidgetItem *t_item_1=new QTableWidgetItem(qstr);
        ui->Linear_vs_Table->setItem(i,0,t_item_1);

        QString qstr1=QString::number(Linear_vs_diag.at(i).getValue());
        QTableWidgetItem *t_item_2=new QTableWidgetItem(qstr1);
        ui->Linear_vs_Table->setItem(i,1,t_item_2);
        ui->Linear_vs_Table->item(i,1)->setBackgroundColor(QColor(51,153,255,125));

        QString qstr2=QString::number(Linear_vs_diag.at(i).getValueOne());
        QTableWidgetItem *t_item_3=new QTableWidgetItem(qstr2);
        ui->Linear_vs_Table->setItem(i,2,t_item_3);
        ui->Linear_vs_Table->item(i,2)->setBackgroundColor(QColor(204,0,12,125));
    }

}

void DiagramEditor::on_Edit_tab_destroyed()
{

}

void DiagramEditor::on_Columnar_b_clicked()
{
    if(!((Circle_diag.empty())&&(Linear_diag.empty())&&(Linear_vs_diag.empty())))
    {
        //Columnar_diag.clear();
        Circle_diag.clear();
        Linear_diag.clear();
        Linear_vs_diag.clear();
        QGraphicsScene *empty =new QGraphicsScene(ui->Diag_View);
        ui->Diag_View->setScene(empty);

    }else{

    }
    open_numb_diagram=1;

        QString qstr2;

    ui->stackedWidget->setCurrentWidget(ui->Columnar_Page);
    TableColumnar();

}

void DiagramEditor::on_Circle_b_clicked()
{
    if(!((Columnar_diag.empty())&&(Linear_diag.empty())&&(Linear_vs_diag.empty())))
    {
        Columnar_diag.clear();
        //Circle_diag.clear();
        Linear_diag.clear();
        Linear_vs_diag.clear();
        QGraphicsScene *empty =new QGraphicsScene(ui->Diag_View);
        ui->Diag_View->setScene(empty);

    }else{

    }

    open_numb_diagram=2;
    QString qstr2;

    ui->stackedWidget->setCurrentWidget(ui->Circle_Page);
    TableCircle();

}

void DiagramEditor::on_Linear_b_clicked()
{
    if(!((Columnar_diag.empty())&&(Circle_diag.empty())&&(Linear_vs_diag.empty())))
    {
        Columnar_diag.clear();
        Circle_diag.clear();
        //Linear_diag.clear();
        Linear_vs_diag.clear();
        QGraphicsScene *empty =new QGraphicsScene(ui->Diag_View);
        ui->Diag_View->setScene(empty);
    }else{

    }
    open_numb_diagram=3;

    ui->stackedWidget->setCurrentWidget(ui->Linear_Page);
    TableLinear();
}

void DiagramEditor::on_Linear_vs_b_clicked()
{
    if(!((Columnar_diag.empty())&&(Circle_diag.empty())&&(Linear_diag.empty())))
    {
        Columnar_diag.clear();
        Circle_diag.clear();
        Linear_diag.clear();
        //Linear_vs_diag.clear();

        QGraphicsScene *empty =new QGraphicsScene(ui->Diag_View);
        ui->Diag_View->setScene(empty);
    }else{

    }
    open_numb_diagram=4;

    ui->stackedWidget->setCurrentWidget(ui->Linear_vs_Page);
    TableLinearVs();
}

void DiagramEditor::on_Edit_b_clicked()
{

    if(open_numb_diagram==0){};
    if(open_numb_diagram==1)
    {
        ui->stackedWidget->setCurrentWidget(ui->Columnar_Page);
    }
    if(open_numb_diagram==2)
    {
        ui->stackedWidget->setCurrentWidget(ui->Circle_Page);
    }
    if(open_numb_diagram==3)
    {
        ui->stackedWidget->setCurrentWidget(ui->Linear_Page);
    }
    if(open_numb_diagram==4)
    {
        ui->stackedWidget->setCurrentWidget(ui->Linear_vs_Page);
    }
}

void DiagramEditor::on_Table_Columnar_activated(const QModelIndex &index)
{

}

void DiagramEditor::on_OK_1_b_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void DiagramEditor::on_OK_1_b_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void DiagramEditor::on_OK_1_b_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void DiagramEditor::on_OK_1_b_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void DiagramEditor::on_Add_Columnar_clicked()
{
    Color m;
    QString qstr2;

    if(ui->Grey_color_Columnar->isChecked())
    {
        m.setColor(0);
        //qstr2=QString::number(0);
        qstr2="Сірий";
    }else
    if(ui->Blue_color_Columnar->isChecked())
    {
        m.setColor(1);
        //qstr2=QString::number(1);
        qstr2="Синій";
    }else
    if(ui->Red_color_Columnar->isChecked())
    {
        m.setColor(2);
        //qstr2=QString::number(2);
        qstr2="Червоний";
    }else
    if(ui->Green_color_Columnar->isChecked())
    {
        m.setColor(3);
        //qstr2=QString::number(3);
        qstr2="Зелений";
    }

    m.setName(ui->Columnar_name->text());
    m.setValue(ui->Columnar_value->value());

    Columnar_diag.push_back(m);

    TableColumnar();

//-------------------------------------------------------------------------------------------Columnar Draw

    DrowColumnar();

//-------------------------------------------------------------------------------------------Columnar Draw

}

void DiagramEditor::on_Columnar_color_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->Page_Add_Columnar_color);
}

void DiagramEditor::on_Back_b_1_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->Page_Add_Columan_Value);


}

void DiagramEditor::on_Columnar_delete_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    if(Columnar_diag.size()==0)
    {
        ui->ALERT_Columnar_1->setAutoFillBackground(true);
        ui->ALERT_Columnar_1->setPalette(sample_palette);
        ui->ALERT_Columnar_1->setText("All clean");
    }else{
    int n;
    QString qstr2;
    n=ui->Columnar_delete_number->value();
    n=n-1;

    if(n>Columnar_diag.size())
    {



        ui->ALERT_Columnar_1->setAutoFillBackground(true);
        ui->ALERT_Columnar_1->setPalette(sample_palette);
        ui->ALERT_Columnar_1->setText("Error");


    }else{
    Columnar_diag.erase(Columnar_diag.begin()+n);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Columnar_1->setAutoFillBackground(true);
    ui->ALERT_Columnar_1->setPalette(sample_palette);
    ui->ALERT_Columnar_1->setText("");

    TableColumnar();
    }


    //-------------------------------------------------------------------------------------------Columnar Draw

    DrowColumnar();

    //-------------------------------------------------------------------------------------------Columnar Draw
}
}

void DiagramEditor::on_Back_b_4_clicked()
{
    ui->stackedWidget_5->setCurrentWidget(ui->Page_Add_Circle_Value);
}

void DiagramEditor::on_Circle_color_clicked()
{
    ui->stackedWidget_5->setCurrentWidget(ui->Page_Add_Circle_color);
}

void DiagramEditor::on_Add_Circle_clicked()
{
    Color m;
    QString qstr2;

    if(ui->Grey_color_Circle->isChecked())
    {
        m.setColor(0);
        //qstr2=QString::number(0);
        qstr2="Сірий";
    }else
    if(ui->Blue_color_Circle->isChecked())
    {
        m.setColor(1);
        //qstr2=QString::number(1);
        qstr2="Синій";
    }else
    if(ui->Red_color_Circle->isChecked())
    {
        m.setColor(2);
        //qstr2=QString::number(2);
        qstr2="Червоний";
    }else
    if(ui->Green_color_Circle->isChecked())
    {
        m.setColor(3);
        //qstr2=QString::number(3);
        qstr2="Зелений";
    }

    m.setName(ui->Circle_name->text());
    m.setValue(ui->Circle_value->value());

    Circle_diag.push_back(m);

    TableCircle();

    //-------------------------------------------------------------------------------------------Circle Draw

    DrowCircle();

    //-------------------------------------------------------------------------------------------Circle Draw

}

void DiagramEditor::on_Circle_delete_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    if(Circle_diag.size()==0){
        ui->ALERT_Circle_1->setAutoFillBackground(true);
        ui->ALERT_Circle_1->setPalette(sample_palette);
        ui->ALERT_Circle_1->setText("All clean");
    }else{
    int n;
    QString qstr2;
    n=ui->Circle_delete_number->value();
    n=n-1;
    if(n>Circle_diag.size())
    {


        ui->ALERT_Circle_1->setAutoFillBackground(true);
        ui->ALERT_Circle_1->setPalette(sample_palette);
        ui->ALERT_Circle_1->setText("Error");


    }else{
    Circle_diag.erase(Circle_diag.begin()+n);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Circle_1->setAutoFillBackground(true);
    ui->ALERT_Circle_1->setPalette(sample_palette);
    ui->ALERT_Circle_1->setText("");

    TableCircle();

    //-------------------------------------------------------------------------------------------Circle Draw

    DrowCircle();

    //-------------------------------------------------------------------------------------------Circle Draw
 }
 }
}


void DiagramEditor::on_Add_Linear_clicked()
{
    Data m;

    m.setName(ui->Linear_name->text());
    m.setValue(ui->Linear_value->value());

    Linear_diag.push_back(m);

    TableLinear();


    //-------------------------------------------------------------------------------------------Linear Draw

    DrowLinear();

    //-------------------------------------------------------------------------------------------Linear Draw

}

void DiagramEditor::on_Linear_delete_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    int n;
    n=ui->Linear_delete_number->value();
    n=n-1;
    if(Linear_diag.size()==0)
    {
        ui->ALERT_Linear_1->setAutoFillBackground(true);
        ui->ALERT_Linear_1->setPalette(sample_palette);
        ui->ALERT_Linear_1->setText("All clean");
    }else{

    if(n>Linear_diag.size())
    {



        ui->ALERT_Linear_1->setAutoFillBackground(true);
        ui->ALERT_Linear_1->setPalette(sample_palette);
        ui->ALERT_Linear_1->setText("Error");


    }else{
    Linear_diag.erase(Linear_diag.begin()+n);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Linear_1->setAutoFillBackground(true);
    ui->ALERT_Linear_1->setPalette(sample_palette);
    ui->ALERT_Linear_1->setText("");

    TableLinear();
    DrowLinear();

}
}
}

void DiagramEditor::on_Add_Linear_vs_clicked()
{
    VsData m;

    m.setName(ui->Linear_vs_name->text());
    m.setValue(ui->Linear_vs_value->value());
    m.setValueOne(ui->Linear_vs_value1->value());

    Linear_vs_diag.push_back(m);

    TableLinearVs();

    //-------------------------------------------------------------------------------------------Linear vs Draw

    DrowLinearVs();

    //-------------------------------------------------------------------------------------------Linear vs Draw




}

void DiagramEditor::on_Linear_vs_delete_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    int n;
    n=ui->Linear_vs_delete_number->value();
    n=n-1;
    if(Linear_vs_diag.size()==0)
    {
        ui->ALERT_Linear_vs_1->setAutoFillBackground(true);
        ui->ALERT_Linear_vs_1->setPalette(sample_palette);
        ui->ALERT_Linear_vs_1->setText("All clean");
    }else{
    if(n>Linear_vs_diag.size())
    {

        ui->ALERT_Linear_vs_1->setAutoFillBackground(true);
        ui->ALERT_Linear_vs_1->setPalette(sample_palette);
        ui->ALERT_Linear_vs_1->setText("Error");


    }else{
    Linear_vs_diag.erase(Linear_vs_diag.begin()+n);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Linear_vs_1->setAutoFillBackground(true);
    ui->ALERT_Linear_vs_1->setPalette(sample_palette);
    ui->ALERT_Linear_vs_1->setText("");
    TableLinearVs();
    DrowLinearVs();

}
}

}

void DiagramEditor::on_Delete_b_clicked()
{
    Columnar_diag.clear();
    Circle_diag.clear();
    Linear_diag.clear();
    Linear_vs_diag.clear();

    QGraphicsScene *empty =new QGraphicsScene(ui->Diag_View);
    ui->Diag_View->setScene(empty);
}

void DiagramEditor::on_Save_b_clicked()
{
    ofstream f;
    f.open("D:\\Michael_Qt\\Kyrs1\\save.txt");

    if(open_numb_diagram==0){};
    if(open_numb_diagram==1)
    {
        //ui->stackedWidget->setCurrentWidget(ui->Columnar_Page);
        Color::saveColor(&Columnar_diag, f,1);
    }
    if(open_numb_diagram==2)
    {
        //ui->stackedWidget->setCurrentWidget(ui->Circle_Page);
        Color::saveColor(&Circle_diag, f,2);
    }
    if(open_numb_diagram==3)
    {
        //ui->stackedWidget->setCurrentWidget(ui->Linear_Page);
        Data::saveData(&Linear_diag, f);
    }
    if(open_numb_diagram==4)
    {
        //ui->stackedWidget->setCurrentWidget(ui->Linear_vs_Page);
        VsData::saveVsData(&Linear_vs_diag, f);
    }
    //Data::saveData(&Linear_diag, f);
    f.close();
}



void DiagramEditor::on_Linear_vs_color_clicked()
{

}

void DiagramEditor::on_Columnar_Swap_b_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    if(Columnar_diag.size()==0)
    {
        ui->ALERT_Columnar_2->setAutoFillBackground(true);
        ui->ALERT_Columnar_2->setPalette(sample_palette);
        ui->ALERT_Columnar_2->setText("Error");
    }else{
    int n1,n2;
    QString qstr2;
    n1=ui->Columnar_Swap_numb1->value();
    n1=n1-1;
    n2=ui->Columnar_Swap_numb2->value();
    n2=n2-1;
    if((n1>Columnar_diag.size())||(n2>Columnar_diag.size()))
    {
        ui->ALERT_Columnar_2->setAutoFillBackground(true);
        ui->ALERT_Columnar_2->setPalette(sample_palette);
        ui->ALERT_Columnar_2->setText("Error");
    }else{
    swap(Columnar_diag[n1],Columnar_diag[n2]);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Columnar_2->setAutoFillBackground(true);
    ui->ALERT_Columnar_2->setPalette(sample_palette);
    ui->ALERT_Columnar_2->setText("");
    TableColumnar();
    DrowColumnar();

}
}
}

void DiagramEditor::on_Circle_Swap_b_2_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    if(Circle_diag.size()==0)
    {
        ui->ALERT_Circle_2->setAutoFillBackground(true);
        ui->ALERT_Circle_2->setPalette(sample_palette);
        ui->ALERT_Circle_2->setText("Error");
    }else{
    int n1,n2;
    QString qstr2;
    n1=ui->Circle_Swap_numb1->value();
    n1=n1-1;
    n2=ui->Circle_Swap_numb2->value();
    n2=n2-1;
    if((n1>Circle_diag.size())||(n2>Circle_diag.size()))
    {
        ui->ALERT_Circle_2->setAutoFillBackground(true);
        ui->ALERT_Circle_2->setPalette(sample_palette);
        ui->ALERT_Circle_2->setText("Error");
    }else{
    swap(Circle_diag[n1],Circle_diag[n2]);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Circle_2->setAutoFillBackground(true);
    ui->ALERT_Circle_2->setPalette(sample_palette);
    ui->ALERT_Circle_2->setText("");
    TableCircle();
    DrowCircle();

}
}

}

void DiagramEditor::on_Linear_Swap_b_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    if(Linear_diag.size()==0)
    {
        ui->ALERT_Linear_2->setAutoFillBackground(true);
        ui->ALERT_Linear_2->setPalette(sample_palette);
        ui->ALERT_Linear_2->setText("Error");
    }else{
    int n1,n2;
    QString qstr2;
    n1=ui->Linear_Swap_numb1->value();
    n1=n1-1;
    n2=ui->Linear_Swap_numb2->value();
    n2=n2-1;


    if((n1>Linear_diag.size())||(n2>Linear_diag.size()))
    {
        ui->ALERT_Linear_2->setAutoFillBackground(true);
        ui->ALERT_Linear_2->setPalette(sample_palette);
        ui->ALERT_Linear_2->setText("Error");
    }else{
    swap(Linear_diag[n1],Linear_diag[n2]);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Linear_2->setAutoFillBackground(true);
    ui->ALERT_Linear_2->setPalette(sample_palette);
    ui->ALERT_Linear_2->setText("");
    TableLinear();
    DrowLinear();

}
}

}

void DiagramEditor::on_Linear_vs_Swap_b_clicked()
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);
    if(Linear_vs_diag.size()==0)
    {
        ui->ALERT_Linear_vs_2->setAutoFillBackground(true);
        ui->ALERT_Linear_vs_2->setPalette(sample_palette);
        ui->ALERT_Linear_vs_2->setText("Error");
    }else{
    int n1,n2;
    //QString qstr2;
    n1=ui->Linear_vs_Swap_numb1->value();
    n1=n1-1;
    n2=ui->Linear_vs_Swap_numb2->value();
    n2=n2-1;


    if((n1>Linear_vs_diag.size())||(n2>Linear_vs_diag.size()))
    {
        ui->ALERT_Linear_vs_2->setAutoFillBackground(true);
        ui->ALERT_Linear_vs_2->setPalette(sample_palette);
        ui->ALERT_Linear_vs_2->setText("Error");
    }else{
    swap(Linear_vs_diag[n1],Linear_vs_diag[n2]);
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->ALERT_Linear_vs_2->setAutoFillBackground(true);
    ui->ALERT_Linear_vs_2->setPalette(sample_palette);
    ui->ALERT_Linear_vs_2->setText("");
    TableLinearVs();
    DrowLinearVs();

}
}

}

void DiagramEditor::on_Open_b_clicked()
{
    ifstream f;
    f.open("D:\\Michael_Qt\\Kyrs1\\save.txt");
    string str;
    f>>str;
    if(str=="1")
    {

        Columnar_diag.clear();
        Color::openColor(&Columnar_diag,f);
        ui->stackedWidget->setCurrentWidget(ui->Columnar_Page);
        Columnar_diag.erase(Columnar_diag.begin()+Columnar_diag.size()-1);
        TableColumnar();
        DrowColumnar();
    }else{
    if(str=="2")
    {

        Circle_diag.clear();
        Color::openColor(&Circle_diag,f);
        ui->stackedWidget->setCurrentWidget(ui->Circle_Page);
        Circle_diag.erase(Circle_diag.begin()+Circle_diag.size()-1);
        TableCircle();
        DrowCircle();
    }else{
    if(str=="3")
    {

        Linear_diag.clear();
        Data::openData(&Linear_diag,f);
        ui->stackedWidget->setCurrentWidget(ui->Linear_Page);
        Linear_diag.erase(Linear_diag.begin()+Linear_diag.size()-1);
        TableLinear();
        DrowLinear();
    }else{
    if(str=="4")
    {

        Linear_vs_diag.clear();
        VsData::openVsData(&Linear_vs_diag,f);
        ui->stackedWidget->setCurrentWidget(ui->Linear_vs_Page);
        Linear_vs_diag.erase(Linear_vs_diag.begin()+Linear_vs_diag.size()-1);
        TableLinearVs();
        DrowLinearVs();
    }else{

    }}}}
}

void DiagramEditor::on_Columnar_Table_activated(const QModelIndex &index)
{

}

void DiagramEditor::on_Columnar_sort_b_clicked()
{

}

void DiagramEditor::on_pushButton_clicked()
{

}

void DiagramEditor::on_Columnar_sort1_b_clicked()
{
    Color::sortColor(&Columnar_diag,1);
    TableColumnar();
    DrowColumnar();

}

void DiagramEditor::on_Columnar_value_editingFinished()
{

}

void DiagramEditor::on_ALERT_Columnar_1_linkActivated(const QString &link)
{

}
