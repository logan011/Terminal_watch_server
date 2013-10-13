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
#include <QCheckBox>
#include<QTcpServer>
#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QtSql>

namespace Ui {
class Widget;
}
enum {Money_Dropped,Power,Carry_on,Disconnected,First_packet};
struct date{
    date(){msg  = -1;Temprete =0; Water_left= 50.0;CountMoney =0;power=carry_on = false; ID = -1;}
    double Temprete,Water_left;
    int CountMoney;
    bool power, carry_on;
    int ID;
   int msg;
};
class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void createtable();
    void addtodatabase(int ,QString,QString);
public slots:
    void slotnewconnection();
    void slotReadClient();
    void slotsendtoclient();
    void slotDisconFromServer();
private:
    date &deserialize(QByteArray array,date &dest);
    void printreport( QSqlQuery report);
    QSqlDatabase DB;
    QGridLayout *layout;
    QHBoxLayout *title;
    QTcpServer *server;
    QTcpSocket* pClientSocket;
    QLabel *label;
    struct bord
    {
      QProgressBar *P_temprete,*P_water;
      QCheckBox *power, *open_out;
      QDoubleSpinBox *money;
      QPushButton *disc;
    };
    int countClient;
    int IdClient;
    bord *arrbox;
    QGroupBox *arraygroupbox;
    QGroupBox *createBox();
    Ui::Widget *ui;
    int countwidget;
    date *datatoread;

};

#endif // WIDGET_H
