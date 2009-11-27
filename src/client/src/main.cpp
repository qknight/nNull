#include <QtGui>
#include <QApplication>
#include "mainWidget.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
     if (!QSystemTrayIcon::isSystemTrayAvailable()) {
         QMessageBox::critical(0, QObject::tr("Systray"),
                               QObject::tr("I couldn't detect any system tray "
                                           "on this system."));
         return 1;
     }
    QApplication::setQuitOnLastWindowClosed(false);
    MainWidget* mainWidget = new MainWidget;
    return app.exec();
}
