#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    vblFirstComp = new QVBoxLayout;

    hblSecondComp = new QHBoxLayout;

    pbLoad = new QPushButton(tr("Загрузить данные"));
    connect(pbLoad, SIGNAL(clicked()), this, SLOT(load()));

    hblSecondComp->addWidget(pbLoad);
    hblSecondComp->addStretch();

    lStayingCost = new QLabel(tr("Цена простоя"));

    hblSecondComp->addWidget(lStayingCost);

    leStayingCost = new QLineEdit;
    connect(leStayingCost, SIGNAL(editingFinished()), this, SLOT(changeStayingCost()));

    hblSecondComp->addWidget(leStayingCost);
    hblSecondComp->addStretch();

    pbSolve = new QPushButton(tr("Посчитать стоимость заказов"));
    connect(pbSolve, SIGNAL(clicked()), this, SLOT(solve()));

    hblSecondComp->addWidget(pbSolve);
    hblSecondComp->addStretch();

    pbSave = new QPushButton(tr("Сохранить"));
    connect(pbSave, SIGNAL(clicked()), this, SLOT(save()));

    hblSecondComp->addWidget(pbSave);
    hblSecondComp->addStretch();

    vblFirstComp->addLayout(hblSecondComp);

    twOrders = new QTableWidget(ORDERS_ROWS, ORDERS_COLUMNS);
    QStringList slOrders;
    slOrders << "Фамилия" << "Стоимость перевозки" << "Погрузка" <<
           "Стоимость погрузки" << "Минуты простой" << "Стоимость заказа";
    twOrders->setHorizontalHeaderLabels(slOrders);
    connect(twOrders, SIGNAL(cellChanged(int, int)), this, SLOT(changeOrder(int, int)));

    vblFirstComp->addWidget(twOrders);

    hblThirdComp = new QHBoxLayout;

    lSurname = new QLabel(tr("Фамилия"));

    hblThirdComp->addWidget(lSurname);

    leSurname = new QLineEdit;

    hblThirdComp->addWidget(leSurname);
    hblThirdComp->addStretch();

    pbFind = new QPushButton(tr("Посчитать стоимость всех заказов"));
    connect(pbFind, SIGNAL(clicked()), this, SLOT(find()));

    hblThirdComp->addWidget(pbFind);
    hblThirdComp->addStretch();

    lSumCost = new QLabel(tr("Стоимость всех заказов"));

    hblThirdComp->addWidget(lSumCost);

    leSumCost = new QLineEdit;
    leSumCost->setReadOnly(true);

    hblThirdComp->addWidget(leSumCost);
    hblThirdComp->addStretch();


    vblFirstComp->addLayout(hblThirdComp);

    this->setLayout(vblFirstComp);

    xmlParser = new XmlParser(&orders);
}

MainWindow::~MainWindow()
{
    for(Order *order : orders)
        delete order;
    orders.clear();

    delete leStayingCost;
    delete leSurname;
    delete leSumCost;

    delete lStayingCost;
    delete lSurname;
    delete lSumCost;

    delete twOrders;

    delete pbLoad;
    delete pbSolve;
    delete pbSave;
    delete pbFind;

    delete hblThirdComp;
    delete hblSecondComp;
    delete vblFirstComp;
}

void MainWindow::load()
{
    QString str = QFileDialog::getOpenFileName(0,
                                               tr("Загрузить данные"),
                                               "../Exam/input.xml",
                                               "*.xml");
    if(!str.isEmpty())
    {
        QFile file(str);
        if(file.open(QIODevice::ReadOnly))
        {
            xmlParser->readXml(file);
            file.close();
        }
    }

    setTable();
}

void MainWindow::solve()
{
    for(Order *order : orders)
    {
        if(order->getIsLoading())
            order->setSumCost(order->getShippingCost() + order->getLoadingCost());
        else
            order->setSumCost(order->getShippingCost() + Order::getStayingCost() * order->getStayingTime());
    }

    setTable();
}

void MainWindow::save()
{
    QString str = QFileDialog::getSaveFileName(0,
                                               tr("Сохранить данные"),
                                               "../Exam/output.xml",
                                               "*.xml");
    if(!str.isEmpty())
    {
        QFile file(str);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream(&file) << xmlParser->createXml();

            file.close();
        }
    }
}

void MainWindow::find()
{
    solve();

    float sumCost = 0.0;

    for(Order *order : orders)
    {
        if(order->getSurname() == leSurname->text())
            sumCost += order->getSumCost();
    }

    leSumCost->setText(QString::number(sumCost));
}

void MainWindow::changeStayingCost()
{
    Order::setStayingCost(leStayingCost->text().toFloat());
}

void MainWindow::changeOrder(int i, int j)
{
    switch(j)
    {
    case 0:
        orders.at(i)->setSurname(twOrders->item(i, j)->text());
        break;
    case 1:
        orders.at(i)->setShippingCost(twOrders->item(i, j)->text().toFloat());
        break;
    case 2:
        orders.at(i)->setIsLoading(twOrders->item(i, j)->text() == "1" ? true : false);
        break;
    case 3:
        orders.at(i)->setLoadingCost(twOrders->item(i, j)->text().toFloat());
        break;
    case 4:
        orders.at(i)->setStayingTime(twOrders->item(i, j)->text().toInt());
        break;
    default:
        break;
    }
}

void MainWindow::setTable()
{
    leStayingCost->setText(QString::number(Order::getStayingCost()));

    twOrders->setRowCount(orders.count());

    QTableWidgetItem *twiOrder = nullptr;

    for(Order *order : orders)
    {
        twiOrder = new QTableWidgetItem(order->getSurname());
        twOrders->setItem(order->getNum() - 1, 0, twiOrder);

        twiOrder = new QTableWidgetItem(QString::number(order->getShippingCost()));
        twOrders->setItem(order->getNum() - 1, 1, twiOrder);

        twiOrder = new QTableWidgetItem(QString::number(order->getIsLoading()));
        twOrders->setItem(order->getNum() - 1, 2, twiOrder);

        twiOrder = new QTableWidgetItem(QString::number(order->getLoadingCost()));
        twOrders->setItem(order->getNum() - 1, 3, twiOrder);

        twiOrder = new QTableWidgetItem(QString::number(order->getStayingTime()));
        twOrders->setItem(order->getNum() - 1, 4, twiOrder);

        twiOrder = new QTableWidgetItem(QString::number(order->getSumCost()));
        twOrders->setItem(order->getNum() - 1, 5, twiOrder);
    }
}
