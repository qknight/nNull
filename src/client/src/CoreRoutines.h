//
// C++ Interface: CoreRoutines
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef COREROUTINES_H
#define COREROUTINES_H

#include <QMenu>
#include <QDialog>
#include <QVector>
#include <QString>
#include <QObject>
#include <QSystemTrayIcon>
#include <QSystemTrayIcon>

#include "src/nm_adaptor.h"
#include "src/infoStruct.h"

class CoreRoutines : public QObject {
  Q_OBJECT
public:
  CoreRoutines(QSystemTrayIcon *ti, QWidget *parent);
  ~CoreRoutines();

private:
  QVector<QString> configs;
  QSystemTrayIcon* trayIcon;
  NmAdaptor* adaptor;
  QAction* refreshAction;
  QAction* quitAction;
  QMenu* trayIconMenu;
  QIcon disconnected;
  QIcon connected;

private Q_SLOTS:
  void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void updateClientConfigs(void);
  void executeConfiguration(void);
  void timerEvent(QTimerEvent *event);
//   void showMessage(QString title, QString message);
//   void showMessage(infoStruct message);

Q_SIGNALS:
  void logMessage(QString message);
  void clearMessages();
};

#endif
