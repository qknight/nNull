#include <QCoreApplication>
#include <QtDBus/QtDBus>
#include "CoreRoutines.h"

int main(int argc, char* argv[]) {
  // we need QCoreApplication since we want signals/slots
  QCoreApplication app(argc, argv);
  CoreRoutines* cr = new CoreRoutines();

  // connect to D-BUS and register as an object:
  QDBusConnection connection = QDBusConnection::systemBus();
  QString objectName = "/MainApplication";
  if (!(connection.registerObject(objectName, cr))) {
    qDebug() << QString("FATAL 1/2:  connection.registerObject failed").arg(objectName);
    exit(1);
  }
  QString serviceName = "de.lastlog.nmInterface";
  if (!(connection.registerService(serviceName))) {
    qDebug() << QString("FATAL 2/2: connection.registerService %1 failed").arg(serviceName);
    qDebug() << "a) this can also indicate that a service is already registered with this name";
    qDebug() << "b) this is a permission problem - you might have to adapt /etc/dbus-1/system.d/nNull.conf, see example: http://mumble.sourceforge.net/DBus";
    exit(1);
  }
  return app.exec();
}
