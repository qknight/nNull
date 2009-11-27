//
// C++ Implementation: MainWidget
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "mainWidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  setupUi(this);
  trayIcon = new QSystemTrayIcon(this);
  cr = new CoreRoutines (trayIcon, this);
  connect(cr, SIGNAL(logMessage(QString)), this, SLOT(logMessage(QString)));
  connect(cr, SIGNAL(clearMessages()), this, SLOT(clearMessages()));
}

MainWidget::~MainWidget() {
}

void MainWidget::logMessage(QString message) {
//   qDebug() << message;
  textBrowser->append(message);
}

void MainWidget::clearMessages() {
  textBrowser->setPlainText("");
}

