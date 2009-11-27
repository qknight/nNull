//
// C++ Interface: execute_process
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef EXECUTE_PROCESS_H
#define EXECUTE_PROCESS_H

#include <QProcess>
#include <QObject>
#include <QDebug>

#include "globals.h"

/**
 @author Joachim Schiele <js@lastlog.de>
*/
class execute_process : public QObject {
  Q_OBJECT
public:
  execute_process();
  ~execute_process();
  void execute(QString program);

private:
  QProcess *myProcess;

private Q_SLOTS:
  void error ( QProcess::ProcessError error );
  void finished ( int exitCode, QProcess::ExitStatus exitStatus );
  void readyReadStandardError();
  void readyReadStandardOutput();
  void started ();
  void stateChanged ( QProcess::ProcessState newState );
Q_SIGNALS:
  void debugOutput(QString);
};

#endif
