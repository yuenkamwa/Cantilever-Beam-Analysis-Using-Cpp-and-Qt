#include "mywidgets.h"
#include "beam.h"
#include <QApplication>

myWidgets::myWidgets(QWidget *parent): QWidget(parent)
{
    label = new QLabel("Please input load data (Unit: m, kN, kN/m). Pressume fixed-support on the left of the beam.");

    lnSpan = new QLineEdit();
    lnSpan->setFixedWidth(200);
    lnSpan->setPlaceholderText("Input span of beam:");
    lnSpan->setClearButtonEnabled(true);
    lnSpan->setText(QString::number(10));

    lnLoadType = new QLineEdit();
    lnLoadType->setFixedWidth(200);
    lnLoadType->setPlaceholderText("Input load type (P, T, U):");
    lnLoadType->setClearButtonEnabled(true);
    lnLoadType->setText(QString("T"));

    lnDistA = new QLineEdit();
    lnDistA->setFixedWidth(200);
    lnDistA->setPlaceholderText("Input distance - start:");
    lnDistA->setClearButtonEnabled(true);
    lnDistA->setText(QString::number(0));

    lnDistB = new QLineEdit();
    lnDistB->setFixedWidth(200);
    lnDistB->setPlaceholderText("Input distance - end:");
    lnDistB->setClearButtonEnabled(true);
    lnDistB->setText(QString::number(10));

    lnLoadStart = new QLineEdit();
    lnLoadStart->setFixedWidth(200);
    lnLoadStart->setPlaceholderText("Input load value - start:");
    lnLoadStart->setClearButtonEnabled(true);
    lnLoadStart->setText(QString::number(5.88));

    lnLoadEnd = new QLineEdit();
    lnLoadEnd->setFixedWidth(200);
    lnLoadEnd->setPlaceholderText("Input load value - end:");
    lnLoadEnd->setClearButtonEnabled(true);
    lnLoadEnd->setText(QString::number(5.88));

    butRun =  new QPushButton("Run");
    butRun->setFixedWidth(100);

    txResult = new QTextEdit();
    txResult->append("Point\tStation (m)\tShear (kN)\tMoment (kNm)");
    txResult->append("---------------------------------------------------------------");

    layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(lnSpan);
    layout->addWidget(lnLoadType);
    layout->addWidget(lnDistA);
    layout->addWidget(lnDistB);
    layout->addWidget(lnLoadStart);
    layout->addWidget(lnLoadEnd);
    layout->addWidget(butRun);
    layout->addWidget(txResult);

    setLayout(layout);
    connect(butRun, SIGNAL(clicked()), this, SLOT(Run()));
}

void myWidgets::setText()
{
//    txResult->setText("Hi");
    txResult->append("Hi");
}

void myWidgets::Run()
{
//    int loadType = 4;   // 1 = Point, 2 = Triangle (decrease from Left), 3 = Triangle (decrease from Right), 4 = Uniform
//    double L = 10;
//    double A = 0;
//    double B = 10;
//    double f = 5.88;
//    double f2 = 5.88;
    this->txResult->clear();
    this->txResult->append("Point\tStation (m)\tShear (kN)\tMoment (kNm)");
    this->txResult->append("---------------------------------------------------------------");

    double L = this->lnSpan->text().toDouble();
    double A = this->lnDistA->text().toDouble();
    double B = this->lnDistB->text().toDouble();
    double f = this->lnLoadStart->text().toDouble();
    double f2 = this->lnLoadEnd->text().toDouble();

    string strLoadType = this->lnLoadType->text().toStdString();
    int loadType;
    if(strLoadType == "P")
    {
        loadType = 1;
    }
    else if(strLoadType == "T")
    {
        loadType = f == 0 ? 3 : 2;
    }
    else if(strLoadType == "U")
    {
        loadType = 4;
    }
    else
    {
        return;
    }

    double x;
    Beam beam;
    double moment, shear, seg = 0.02 * L;
    for (int i = 0; i < 51; ++i)
    {
        x = i * seg;
        shear = beam.CanBeamAnal(loadType, L, A, B, f, f2, x, 0, 3);
        moment = beam.CanBeamAnal(loadType, L, A, B, f, f2, x, 0, 4);
        txResult->append(QString::number(i) + "\t" + QString::number(x) + "\t" + QString::number(shear) + "\t" + QString::number(moment));
    }
}
