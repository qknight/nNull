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

#include <QDebug>
#include <QDir>
#include <QObject>
#include <QString>
#include <QVector>
#include "execute_process.h"
#include "nm_adaptor.h"
#include "globals.h"

/**
 @author Joachim Schiele <js@lastlog.de>
*/
class CoreRoutines : public QObject {
  Q_OBJECT

public:
  CoreRoutines();
  ~CoreRoutines();

public Q_SLOTS:
  uint listConfigs(); // returns the count of config files found
  QString queryConfigurationName(int pos); // config at position pos in the configs vector
  int reloadConfigurations(); // rereads the QVector with /root/configs/* files
  int executeConfiguration(QString config); // executes a given config

Q_SIGNALS:
  void debugOutput(QString);

private:
  NmAdaptor* na;
  QVector<QString> configs;
  execute_process ep;
};

#endif
