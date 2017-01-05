/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp dde-center -a dbuscontrolcenter -c DBusControlCenter -l Frame
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "dbuscontrolcenterservice.h"

#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QGuiApplication>
#include <QScreen>
#include <QString>

/*
 * Implementation of adaptor class DBusControlCenter
 */

DBusControlCenterService::DBusControlCenterService(Frame *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor

//    connect(parent, &Frame::xChanged, [parent]{
//        QDBusMessage m = QDBusMessage::createSignal("/com/deepin/dde/ControlCenter", "org.freedesktop.DBus.Properties", "PropertiesChanged");
//        QMap<QString, QVariant> changedProperties;
//        changedProperties["X"] = parent->visibleFrameXPos();
//        QList<QString> invalidatedProperties;
//        m << QVariant("com.deepin.dde.ControlCenter") << changedProperties << QVariant(invalidatedProperties);
//        QDBusConnection::sessionBus().send(m);
//    });

//    connect(parent, &Frame::hideInLeftChanged, parent, &Frame::xChanged);
}

DBusControlCenterService::~DBusControlCenterService()
{
    // destructor
}

Frame *DBusControlCenterService::parent() const
{
    return static_cast<Frame *>(QObject::parent());
}

bool DBusControlCenterService::showInRight() const
{
    // get the value of property ShowInRight
    // FIXME
//    return qvariant_cast< bool >(!parent()->isHideInLeft());
    return false;
}

int DBusControlCenterService::x() const
{
    if (!parent()->isVisible())
        return qApp->primaryScreen()->geometry().right();

    return parent()->x();
}

void DBusControlCenterService::Hide()
{
    // handle method call com.deepin.dde.ControlCenter.Hide
    parent()->hide();
}

void DBusControlCenterService::HideImmediately()
{
    // handle method call com.deepin.dde.ControlCenter.HideImmediately
    parent()->hide();
}

void DBusControlCenterService::Show()
{
    // handle method call com.deepin.dde.ControlCenter.Show
    parent()->show();
}

void DBusControlCenterService::ShowImmediately()
{
    // handle method call com.deepin.dde.ControlCenter.ShowImmediately
    parent()->show();
}

void DBusControlCenterService::ShowModule(const QString &name)
{
    // handle method call com.deepin.dde.ControlCenter.ShowModule
    //parent()->ShowModule(name);
//    parent()->selectModule(name);
    parent()->showSettingsPage(name, QString());
}

void DBusControlCenterService::Toggle()
{
    // handle method call com.deepin.dde.ControlCenter.Toggle
//    parent()->toggle(false);
    parent()->toggle();
}

void DBusControlCenterService::ToggleInLeft()
{
    // handle method call com.deepin.dde.ControlCenter.ToggleInLeft
//    parent()->toggle(true);
    parent()->show();
}

bool DBusControlCenterService::isNetworkCanShowPassword()
{
    // handle method call com.deepin.dde.ControlCenter.isNetworkCanShowPassword
    //return parent()->isNetworkCanShowPassword();

    return false; // for remove gcc warning.
}
