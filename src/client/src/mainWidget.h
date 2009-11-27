//
// C++ Interface: MainWidget
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDialog>
#include <QDebug>

#include "CoreRoutines.h"
#include "ui_logger.h"

class MainWidget : public QWidget, private Ui::LoggerWidget {
  Q_OBJECT

public:
  MainWidget(QWidget *parent = 0);
  ~MainWidget();

private:
  QSystemTrayIcon *trayIcon;
  CoreRoutines* cr;
  private Q_SLOTS:
    void logMessage(QString message);
    void clearMessages();
};

#endif
