//
// C++ Implementation: execute_process
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "execute_process.h"

execute_process::execute_process() {
  myProcess = new QProcess();
  connect(myProcess, SIGNAL( error(QProcess::ProcessError)), this, SLOT( error(QProcess::ProcessError)));
  connect(myProcess, SIGNAL(finished ( int , QProcess::ExitStatus  )),
          this, SLOT(finished ( int , QProcess::ExitStatus  )));
  connect(myProcess, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
  connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
  connect(myProcess, SIGNAL( started()), this, SLOT(started()));
  connect(myProcess, SIGNAL( stateChanged ( QProcess::ProcessState )), this, SLOT(stateChanged ( QProcess::ProcessState )));
}

execute_process::~execute_process() {
}

void execute_process::execute(QString program) {
  emit debugOutput(QString("server: execute(%1)").arg(program));
  // stop old myProcessess first
  myProcess->close();
  QStringList arguments;
  arguments << "" << "";
  QString prog = QString("%1/%2").arg(QString(CONFIG_PATH)).arg(program);
  myProcess->start(prog, arguments);
}

void execute_process::finished ( int exitCode, QProcess::ExitStatus /*exitStatus*/ ) {
  qDebug() << QString("server: execution finished with status code (%1)").arg(exitCode);
  emit debugOutput(QString("server: execution finished with status code (%1)").arg(exitCode));
}

void execute_process::readyReadStandardError() {
//   qDebug()<< "updateError";
  QByteArray data = myProcess->readAllStandardError();
  QString text =  QString("server: exec: stderr: %1").arg(QString(data));
  qDebug() << text;
  emit debugOutput(text);
}

void execute_process::readyReadStandardOutput() {
//   qDebug()<< "updateText";
  QByteArray data = myProcess->readAllStandardOutput();
  QString text =  QString("server: exec: stdout: %1").arg(QString(data));
  qDebug() << text;
  emit debugOutput(text);
}

void execute_process::error ( QProcess::ProcessError error ) {
  QString m = QString("server: error: %1").arg(error);
  qDebug()<< m;
  emit debugOutput(m);
}

void execute_process::started () {
  QString m = QString("server: started");
  qDebug()<< m;
  emit debugOutput(m);
}

void execute_process::stateChanged ( QProcess::ProcessState newState ) {
  QString m = QString("server: stateChanged: %1").arg(newState);
  qDebug()<< m;
//   emit debugOutput(m);
}

