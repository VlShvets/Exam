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
    leStayingCost->setReadOnly(true);

    hblSecondComp->addWidget(leStayingCost);
    hblSecondComp->addStretch();

    pbSolve = new QPushButton(tr("Посчитать стоимость заказов"));
    connect(pbSolve, SIGNAL(clicked()), this, SLOT(solve()));

    hblSecondComp->addWidget(pbSolve);

    vblFirstComp->addLayout(hblSecondComp);

    twOrders = new QTableWidget(ORDERS_ROWS, ORDERS_COLUMNS);
    QStringList slOrders;
    slOrders << "Фамилия" << "Стоимость перевозки" << "Погрузка" <<
           "Стоимость погрузки" << "Минуты простоя" << "Стоимость заказа";
    twOrders->setHorizontalHeaderLabels(slOrders);

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

    xmlParser = new XmlParser(customers);
}

MainWindow::~MainWindow()
{
    for(Customer *customer : customers)
        delete customer;
    customers.clear();

    delete leStayingCost;
    delete leSurname;
    delete leSumCost;

    delete lStayingCost;
    delete lSurname;
    delete lSumCost;

    delete twOrders;

    delete pbLoad;
    delete pbSolve;
    delete pbFind;

    delete hblThirdComp;
    delete hblSecondComp;
    delete vblFirstComp;
}

void MainWindow::load()
{
    QString str = QFileDialog::getOpenFileName(nullptr,
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
    for(Customer *customer : customers)
    {
        for(Order *order : customer->orders)
            order->solveSumCost();
    }

    setTable();
}

void MainWindow::find()
{
    solve();

    float sumCost = 0.0;

    for(Customer *customer : customers)
    {
        if(customer->getSurname() == leSurname->text())
        {
            for(Order *order : customer->orders)
                sumCost += order->getSumCost();
            break;
        }
    }

    leSumCost->setText(QString::number(sumCost));
}

void MainWindow::setTable()
{
    leStayingCost->setText(QString::number(OrderWithoutLoading::getStayingCost()));

    int rowCount = 0;
    for(Customer *customer : customers)
        rowCount += customer->orders.count();
    twOrders->setRowCount(rowCount);

    QTableWidgetItem *twiOrder = nullptr;

    int numRow = 0;
    for(Customer *customer : customers)
    {
        for(Order *order: customer->orders)
        {
            twiOrder = new QTableWidgetItem(customer->getSurname());
            twiOrder->setFlags(twiOrder->flags() ^ Qt::ItemIsEditable);
            twOrders->setItem(numRow, 0, twiOrder);

            twiOrder = new QTableWidgetItem(QString::number(order->getShippingCost()));
            twiOrder->setFlags(twiOrder->flags() ^ Qt::ItemIsEditable);
            twOrders->setItem(numRow, 1, twiOrder);

            twiOrder = new QTableWidgetItem(QString::number(order->getIsLoading()));
            twiOrder->setFlags(twiOrder->flags() ^ Qt::ItemIsEditable);
            twOrders->setItem(numRow, 2, twiOrder);

            twiOrder = new QTableWidgetItem(QString::number(order->getLoadingCost()));
            twiOrder->setFlags(twiOrder->flags() ^ Qt::ItemIsEditable);
            twOrders->setItem(numRow, 3, twiOrder);

            twiOrder = new QTableWidgetItem(QString::number(order->getStayingTime()));
            twiOrder->setFlags(twiOrder->flags() ^ Qt::ItemIsEditable);
            twOrders->setItem(numRow, 4, twiOrder);

            twiOrder = new QTableWidgetItem(QString::number(order->getSumCost()));
            twiOrder->setFlags(twiOrder->flags() ^ Qt::ItemIsEditable);
            twOrders->setItem(numRow, 5, twiOrder);

            ++numRow;
        }
    }
}
