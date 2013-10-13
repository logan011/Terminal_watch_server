#include "widget.h"
#include "ui_widget.h"
#include <qdebug.h>
#include <QFile>
#include<QStyle>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    countClient = 0;
    IdClient = -1;
    countwidget = 0;
   QScrollArea  *area = new QScrollArea;
   title = new QHBoxLayout;
    arraygroupbox = new QGroupBox[30];
    layout = new QGridLayout;
    datatoread = new date();
    arrbox= new bord[30];
    label = new QLabel("<H1>Wait for connection...</H!>");
    QString style;
    QFile file("CssStyle");
            if(file.open(QIODevice::ReadOnly))
    {
        style = file.readAll();
        qDebug()<<"Eror";
        file.close();

    }
    title->addWidget(label,0,Qt::AlignCenter);
    setLayout(title);
    area->setWidget(this);
    area->setWidgetResizable(true);
    area->setMinimumHeight(300);
    area->setMinimumWidth(600);
    area->show();
    this->show();
    server = new QTcpServer();
    server->listen(QHostAddress::Any,2323);
    /*
    DB = QSqlDatabase::addDatabase("QSQLITE", "connection_name");
    DB.setDatabaseName("Water_Terminal");
    if(!DB.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Cannot open DataBase!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    createtable();
    */
    QObject::connect(server,SIGNAL(newConnection()),this,SLOT(slotnewconnection()));
    qApp->setStyleSheet(style);
}

QGroupBox *Widget::createBox()
{
    arrbox[countClient].money = new QDoubleSpinBox();
    arrbox[countClient].money->setMaximum(200);
    arrbox[countClient].power = new QCheckBox("Power");
    arrbox[countClient].open_out = new QCheckBox("Open out");
    arrbox[countClient].P_temprete = new QProgressBar;
    arrbox[countClient].P_water = new QProgressBar;
    arrbox[countClient].disc= new QPushButton("Disconnect");
    arrbox[countClient].money->setReadOnly(true);    
    arrbox[countClient].open_out->setDisabled(true);
    arrbox[countClient].power->setDisabled(true);  
    arrbox[countClient].P_temprete->setMaximum(50);
    arrbox[countClient].P_water->setMaximum(50000);
    arraygroupbox[countClient].setTitle(tr("Client ") + QString::number(countClient));
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;
    vbox->addWidget(new QLabel("Tempreture"));
    vbox->addWidget(arrbox[countClient].P_temprete);
    vbox->addWidget(new QLabel("Water"));
    vbox->addWidget(arrbox[countClient].P_water);
    vbox->addWidget(new QLabel("Money"));
    vbox->addWidget(arrbox[countClient].money);
    hbox->addWidget(arrbox[countClient].power);
    hbox->addWidget(arrbox[countClient].open_out);
    hbox->addWidget(arrbox[countClient].disc);
    vbox->addLayout(hbox);
     vbox->addStretch(29);
    arraygroupbox[countClient].setLayout(vbox);
       QObject::connect(arrbox[countClient].disc,SIGNAL(clicked()),this,SLOT(slotDisconFromServer()));
    return  (arraygroupbox+countClient);
}

void Widget::slotnewconnection()
{
    if(!countClient)
    {
        delete title;
        label->hide();
    }
    if(!layout)
    {
     layout = new QGridLayout;
     delete title;
     label->hide();
    }
    pClientSocket = server->nextPendingConnection();
    connect(pClientSocket, SIGNAL(readyRead()),
                this,  SLOT(slotReadClient()));
    if(countwidget < 4){
        layout->addWidget(createBox(),0,countwidget);

    }
    else
        layout->addWidget(createBox(),countwidget/4,countwidget%4);
                setLayout(layout);
    pClientSocket->write(QByteArray::number(countClient));
      countClient ++;
      countwidget ++;

}
void Widget::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    *datatoread = deserialize(pClientSocket->readAll(),*datatoread);
       switch(datatoread->msg)
       {
       case Money_Dropped:
       {
       arrbox[datatoread->ID].money->setValue(datatoread->CountMoney);
       arrbox[datatoread->ID].P_water->setValue(datatoread->Water_left);
       arrbox[datatoread->ID].open_out->setChecked(datatoread->carry_on);
       arrbox[datatoread->ID].power->setChecked(datatoread->power);
       arrbox[datatoread->ID].P_temprete->setValue(datatoread->Temprete);
       break;
       }
       case Power:
       {
            arrbox[datatoread->ID].power->setChecked(datatoread->power);
            break;
       }
       case Carry_on:
       {
           arrbox[datatoread->ID].open_out->setChecked(datatoread->carry_on);
           break;
       }
       case Disconnected:
       {
           arraygroupbox[datatoread->ID].hide();
           countwidget--;
           if(countwidget == 0)
           {
                 title = new QHBoxLayout;
                 title->addWidget(label,0,Qt::AlignCenter);
                 label->show();
                 delete layout;
                 layout = (QGridLayout *)0;
                 setLayout(title);

           }
           break;
       }
       }

}
date &Widget::deserialize(QByteArray array,date &dest)
{
    QDataStream stream(&array,QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_4_5);
    stream >> dest.ID;
       stream >> dest.CountMoney;
       stream>> dest.power;
       stream>>dest.carry_on;
      stream>>dest.Temprete;
       stream>>dest.Water_left;
       stream>>dest.msg;
       return dest;
}
void Widget::slotsendtoclient()
{
}
void Widget::createtable()
{
    QSqlQuery a_query(DB);
     a_query.prepare("CREATE TABLE IF NOT EXISTS terminal"
                     "(id INTEGER PRIMARY KEY, name TEXT, adress TEXT)");
  if(!a_query.exec())
  {
      printreport(a_query);
  }

}
void Widget::slotDisconFromServer()
{
    arraygroupbox[IdClient].hide();
}

void Widget::addtodatabase(int id, QString name,  QString addres)
{
    QSqlQuery a_query(DB);
    a_query.prepare("SELECT * from terminal");
    a_query.exec();
    if(!a_query.exec())
    {
        printreport(a_query);
    }
    QSqlRecord rec = a_query.record();
    if(id > rec.count())
    {
    a_query.prepare("INSERT INTO terminal (id, name, adress)"
                    "VALUES(:id, :name, :adress)");
    a_query.bindValue(":id",QString::number(id));
    a_query.bindValue(":name",name);
    a_query.bindValue(":adress",addres);
        if (!a_query.exec()) {
            printreport(a_query);
        }
    }
}
void Widget::printreport(QSqlQuery report)
{
    QMessageBox msgBox;
    msgBox.setText("Error");
    msgBox.setInformativeText(report.lastError().text());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

Widget::~Widget()
{
    delete [] arraygroupbox;
    delete []arrbox;
    delete ui;
}
