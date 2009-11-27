/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c NmAdaptor -p src/nm_adaptor.h:src/nm_adaptor.cpp interface.xml
 *
 * qdbusxml2cpp is Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NM_ADAPTOR_H_1259016954
#define NM_ADAPTOR_H_1259016954

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface de.lastlog.nmInterface
 */
class NmAdaptor: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "de.lastlog.nmInterface"; }

public:
    NmAdaptor(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~NmAdaptor();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<int> executeConfiguration(const QString &config)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(config);
        return asyncCallWithArgumentList(QLatin1String("executeConfiguration"), argumentList);
    }

    inline QDBusPendingReply<uint> listConfigs()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("listConfigs"), argumentList);
    }

    inline QDBusPendingReply<QString> queryConfigurationName(int pos)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(pos);
        return asyncCallWithArgumentList(QLatin1String("queryConfigurationName"), argumentList);
    }

    inline QDBusPendingReply<int> reloadConfigurations()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("reloadConfigurations"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void crashed();
    void debugOutput(const QString &message);
};

namespace de {
  namespace lastlog {
    typedef ::NmAdaptor nmInterface;
  }
}
#endif
