#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xmlparser.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>

#include <QTextStream>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void load();    /// Загрузка данных
    void solve();   /// Расчёт стоимости заказа
    void find();    /// Найти заказы по фамилии

private:
    void setTable();    /// Установить значения в таблицу

    QList <Customer *> customers;
    XmlParser *xmlParser;

    QVBoxLayout *vblFirstComp;
    QHBoxLayout *hblSecondComp;
    QHBoxLayout *hblThirdComp;

    QPushButton *pbLoad;
    QPushButton *pbSolve;
    QPushButton *pbFind;

    QTableWidget *twOrders;

    QLabel *lStayingCost;
    QLabel *lSurname;
    QLabel *lSumCost;

    QLineEdit *leStayingCost;
    QLineEdit *leSurname;
    QLineEdit *leSumCost;

    static const int ORDERS_ROWS = 0;
    static const int ORDERS_COLUMNS = 6;
};

#endif // MAINWINDOW_H
