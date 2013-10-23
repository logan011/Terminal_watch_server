#ifndef WIDGET_H
#define WIDGET_H

#include <QDoubleSpinBox>
#include<QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include<QVBoxLayout>
#include <QProgressBar>
#include<QTcpSocket>
#include<QGridLayout>
#include <QGroupBox>
#include <QByteArray>
#include<QMap>
#include <QCheckBox>
#include<QTcpServer>
#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
#include <QTime>
#include <QDate>
#include<QMenuBar>
#include "database.h"
namespace Ui {
class Widget;
}
enum {Handshake,Money_Dropped,Disconnected,Options};
struct date{
    date(){msg  = -1;Temprete =20; Water_left= 5000.0;CountMoney =0;power=carry_on = false; ID = -1,timesale ="";volt12 = 11.0;volt5 = 4.0;}
    void setstruct(int message,int Id,double Temp=20, double Water=50000, double Vol5=4, double Vol12=11, int Mon=0,
                   bool Power=false, bool Carry=false, QString TimeS="", QString TimeW="") {
            this->msg = message;
            this->Temprete = Temp;
            this->Water_left = Water;
            this->volt5 = Vol5;
            this->volt12 = Vol12;
            this->CountMoney = Mon;
            this->power = Power;
            this->carry_on = Carry;
            this->ID = Id;
            this->timesale = TimeS;
            this->timewater = TimeW;
        }
    double Temprete,Water_left,volt12,volt5;
    int CountMoney;
    bool power, carry_on;
    int ID;
   int msg;
   QString timewater,timesale;
};
struct bord
{
  QProgressBar *P_temprete,*P_water;
  QCheckBox *power, *open_out;
  QDoubleSpinBox *money;
  QPushButton *disc;
  QLineEdit *lastwatersale;
  QLineEdit *lastwaterapdate;
  QLineEdit *Voltage12;
  QLineEdit *Voltage5;
};
class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void slotnewconnection();
    void slotReadClient();
    void slotDisconFromServer();
private:
    date &deserialize(QByteArray array,date &dest);
  QByteArray serialize(date packet);
    void printreport( QSqlQuery report);
    QGridLayout *layout;
    QHBoxLayout *title;
    QMap<int,QTcpSocket *> clientmap;
    QMap<int,QPushButton*>buutonmap;
    QTcpServer *server;
    QTcpSocket* pClientSocket;
    QLabel *label;
    int countClient;
    int countwidget;
    bord *arrbox;
    QGroupBox *arraygroupbox;
    QGroupBox *createBox();
    QMenuBar *toolbar;
    bord * createbord(bord *arrbox);
    Ui::Widget *ui;
    date *datatoread;
     DatabaseManager *db;
};

#endif // WIDGET_H
