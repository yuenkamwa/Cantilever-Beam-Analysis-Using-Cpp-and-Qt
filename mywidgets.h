#ifndef MYWIDGETS_H
#define MYWIDGETS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QTextEdit>
#include <QApplication>

class myWidgets : public QWidget
{
    Q_OBJECT
public:
    myWidgets(QWidget *parent=0);
private:

    QLabel *label;
    QLineEdit *lnSpan;
    QLineEdit *lnLoadType;
    QLineEdit *lnDistA;
    QLineEdit *lnDistB;
    QLineEdit *lnLoadStart;
    QLineEdit *lnLoadEnd;

    QTextEdit *txResult;
    QPushButton *butRun;

    QVBoxLayout* layout;
private slots:
    void setText();
    void Run();
};

#endif // MYWIDGETS_H
