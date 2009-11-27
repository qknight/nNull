//
// C++ Implementation: CoreRoutines
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "CoreRoutines.h"

CoreRoutines::CoreRoutines(QSystemTrayIcon *ti, QWidget *parent) : QObject(parent) {
  trayIcon=ti;
  trayIconMenu = new QMenu;

  adaptor = new NmAdaptor("de.lastlog.nmInterface", "/MainApplication",
                          QDBusConnection::systemBus(), this);

  disconnected = QIcon(":icons/disconnected.png");
  connected = QIcon(":icons/connected.png");
  trayIcon->setIcon(disconnected);
  trayIcon->show();

  connect(trayIcon, SIGNAL(activated ( QSystemTrayIcon::ActivationReason )), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason )));
  connect(adaptor, SIGNAL(debugOutput(QString)), SIGNAL(logMessage(QString)));
  // this is ugly and can probably be replaced by a signal or something so that
  // only if there is no service the client needs to poll.  #include <QDBusServiceWatcher> coming in qt 4.6
  startTimer(1000);
}

CoreRoutines::~CoreRoutines() {
}

// FIXME this timerEvent should be replaced by #include <QDBusServiceWatcher>
void CoreRoutines::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);
  static bool status = false;
  if (status != adaptor->isValid())
    status = adaptor->isValid();
  else
    return;
  if (status) {
    emit logMessage("client<->server connected");
    trayIcon->setIcon(connected);
  }  else {
    emit logMessage("client<->server disconnected");
    trayIcon->setIcon(disconnected);
  }
  updateClientConfigs();
}

void CoreRoutines::updateClientConfigs() {
  if (adaptor->reloadConfigurations() != 0)
    emit logMessage("client: there was an error calling reloadConfigurations() on the server via dbus call");
  int c=adaptor->listConfigs();
  configs.clear();
  trayIconMenu->clear();

  for (int i=0; i < c; ++i)
    configs.push_back(adaptor->queryConfigurationName(i));

  foreach(QString ac, configs) {
    QAction* a = new QAction(ac, trayIconMenu);
    a->setData(ac);
    a->setEnabled(true);
    connect(a, SIGNAL(triggered()), this, SLOT(executeConfiguration()));
    trayIconMenu->addAction(a);
  }
  trayIconMenu->addSeparator();
  refreshAction = new QAction("refresh configs", trayIconMenu);
  trayIconMenu->addAction(refreshAction);
  connect(refreshAction, SIGNAL(triggered()), this, SLOT(updateClientConfigs(void)));

  quitAction = new QAction("quit", trayIconMenu);
  trayIconMenu->addAction(quitAction);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

  trayIcon->setContextMenu(trayIconMenu);
}

void CoreRoutines::executeConfiguration() {
  QAction* s = dynamic_cast<QAction*>( sender());
  if (s) {
    QString config = QVariant(s->data()).toString();
//     qDebug() << "executeConfiguration: " << config;
    emit logMessage(QString("client: executing a new configuration: %1").arg(config));
    if (adaptor->executeConfiguration(config) != 0)
//       showMessage(config, "error in remote dbus request");
      emit logMessage(QString("client: error in remote dbus request: %1").arg(config));
    else {
//       showMessage(config,"is being executed");
      emit logMessage(QString("client: sent request to server: %1").arg(config));
    }
  }
}

void CoreRoutines::iconActivated(QSystemTrayIcon::ActivationReason reason) {
  switch (reason) {
  case QSystemTrayIcon::Trigger:
    if (parent()) {
      QWidget* p = dynamic_cast<QWidget*>(parent());
      p->setVisible(!(p->isVisible()));
    }
    break;
  case QSystemTrayIcon::DoubleClick:
    break;
  case QSystemTrayIcon::MiddleClick:
//     showMessage("status","MiddleClick");
    emit clearMessages();
    break;
  default:
    ;
  }
}

// void CoreRoutines::showMessage(infoStruct message) {
//   trayIcon->showMessage("foo", message.message);
// }
//
// void CoreRoutines::showMessage(QString title, QString message) {
//   trayIcon->showMessage(title, message);
// }

