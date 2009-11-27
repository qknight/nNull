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

CoreRoutines::CoreRoutines() {
    // create the adaptor:
  na = new NmAdaptor(this);

  reloadConfigurations();
  connect(&ep, SIGNAL(debugOutput(QString)), na, SIGNAL(debugOutput(QString)));
  connect(this, SIGNAL(debugOutput(QString)), na, SIGNAL(debugOutput(QString)));
}

CoreRoutines::~CoreRoutines() {
}

uint CoreRoutines::listConfigs() {
//   qDebug() << "called CoreRoutines::listConfigs()\n";
//   qDebug() << configs.size();
  return configs.size();
}

// look into /root/config/* and list all those files with absolute path in configs
int CoreRoutines::reloadConfigurations() {
  emit debugOutput("server: reloadConfigurations() called");
  configs.clear();
  QDir dir = QString(CONFIG_PATH);
  dir.setNameFilters(QStringList("*.N0")); // i call my configs *.N0
  foreach(QString str,dir.entryList()) {
    qDebug() << "config found: " << str;
    configs.push_back(str);
  }
  return 0;
}

QString CoreRoutines::queryConfigurationName(int pos) {
  if (configs.size() > pos)
    return configs[pos];
  return QString("");
}

int CoreRoutines::executeConfiguration(QString config) {
  if (configs.contains(config)) {
    emit debugOutput(QString("server: executing config called: %1").arg(config));
    ep.execute(config);
    return 0; // good
  }
  emit debugOutput(QString("server: ERROR executing config called: %1 does not exist").arg(config));
  return -1; // bad
}

