//https://www.electroniclinic.com/qt-creator-signal-widgets-and-slot-widgets-with-example-programs/
#include <QApplication>
#include "mywidgets.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    myWidgets* window = new myWidgets;
    window->setWindowTitle("Cantilever Beam Analysis Using C++ and Qt");
    window->resize(800, 500);
    window->show();
    return app.exec();
}
