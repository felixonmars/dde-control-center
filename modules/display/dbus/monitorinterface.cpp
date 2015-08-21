/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p monitorinterface -c MonitorInterface com.deepin.daemon.Display.Monitor.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "monitorinterface.h"

/*
 * Implementation of interface class MonitorInterface
 */

QDBusArgument &operator<<(QDBusArgument &argument, const MonitorMode &mode)
{
    argument.beginStructure();
    argument << mode.id << mode.width << mode.height << mode.rate;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, MonitorMode &mode)
{
    argument.beginStructure();
    argument >> mode.id >> mode.width >> mode.height >> mode.rate;
    argument.endStructure();
    return argument;
}

MonitorInterface::MonitorInterface(const QString &path, QObject *parent)
    : QDBusAbstractInterface(staticServiceName(), path, staticInterfaceName(), QDBusConnection::sessionBus(), parent)
{
    qDBusRegisterMetaType<UshortList>();
    qDBusRegisterMetaType<MonitorMode>();
    qDBusRegisterMetaType<MonitorModeList>();

    QDBusConnection::sessionBus().connect(this->service(), this->path(), "org.freedesktop.DBus.Properties",  "PropertiesChanged","sa{sv}as", this, SLOT(__propertyChanged__(QDBusMessage)));
}

MonitorInterface::~MonitorInterface()
{
    QDBusConnection::sessionBus().disconnect(service(), path(), "org.freedesktop.DBus.Properties",  "PropertiesChanged",  "sa{sv}as", this, SLOT(propertyChanged(QDBusMessage)));
}
