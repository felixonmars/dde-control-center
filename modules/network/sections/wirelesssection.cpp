/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     listenerri <listenerri@gmail.com>
 *
 * Maintainer: listenerri <listenerri@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "wirelesssection.h"
#include "contentwidget.h"

#include <dspinbox.h>

#include <networkmanagerqt/manager.h>
#include <networkmanagerqt/wireddevice.h>

using namespace dcc::network;
using namespace dcc::widgets;
using namespace NetworkManager;

WirelessSection::WirelessSection(NetworkManager::WirelessSetting::Ptr wiredSetting, const QString &deviceInterface, QFrame *parent)
    : AbstractSection("Wi-Fi", parent),
      m_apSsid(new LineEditWidget(this)),
      m_deviceMac(new ComboBoxWidget(this)),
      //m_clonedMac(new LineEditWidget(this)),
      m_customMtuSwitch(new SwitchWidget(this)),
      m_customMtu(new SpinBoxWidget(this)),
      m_wirelessSetting(wiredSetting),
      m_deviceInterface(deviceInterface)
{
    // get the macAddress list from all wireless devices
    for (auto device : NetworkManager::networkInterfaces()) {
        if (device->type() != NetworkManager::Device::Type::Wifi) {
            continue;
        }
        NetworkManager::WirelessDevice::Ptr wDevice = device.staticCast<NetworkManager::WirelessDevice>();
        /* Alt:  permanentHardwareAddress to get real hardware address which is connot be changed */
        const QString &macStr = wDevice->permanentHardwareAddress() + " (" + wDevice->interfaceName() + ")";
        m_macStrMap.insert(macStr, wDevice->permanentHardwareAddress().remove(":"));
    }

    // "^([0-9A-Fa-f]{2}[:-\\.]){5}([0-9A-Fa-f]{2})$"
    m_macAddrRegExp = QRegExp("^([0-9A-Fa-f]{2}[:]){5}([0-9A-Fa-f]{2})$");

    initUI();
    initConnection();
}

WirelessSection::~WirelessSection()
{
}

bool WirelessSection::allInputValid()
{
    bool valid = true;

    const QString &apSsid = m_apSsid->text();
    if (apSsid.isEmpty()) {
        valid = false;
        m_apSsid->setIsErr(true);
    } else {
        m_apSsid->setIsErr(false);
    }

    return valid;

    //const QString &clonedMacStr = m_clonedMac->text();
    //if (clonedMacStr.isEmpty()) {
        //return true;
    //}
    //bool matched = m_macAddrRegExp.exactMatch(clonedMacStr);
    //m_clonedMac->setIsErr(!matched);
    //return matched;
}

void WirelessSection::saveSettings()
{
    m_wirelessSetting->setSsid(m_apSsid->text().toUtf8());

    QString hwAddr = m_macStrMap.value(m_deviceMac->value());
    m_wirelessSetting->setMacAddress(QByteArray::fromHex(hwAddr.toUtf8()));

    //QString clonedAddr = m_clonedMac->text().remove(":");
    //m_wirelessSetting->setClonedMacAddress(QByteArray::fromHex(clonedAddr.toUtf8()));

    m_wirelessSetting->setMtu(m_customMtuSwitch->checked() ? m_customMtu->spinBox()->value() : 0);

    m_wirelessSetting->setInitialized(true);
}

void WirelessSection::initUI()
{
    m_apSsid->setTitle(tr("SSID"));
    m_apSsid->setPlaceholderText(tr("Required"));
    m_apSsid->setText(m_wirelessSetting->ssid());

    m_deviceMac->setTitle(tr("Device MAC Addr"));
    for (const QString &key : m_macStrMap.keys()) {
        m_deviceMac->appendOption(key, m_macStrMap.value(key));
    }

    // get the macAddress from Settings
    const QString &macAddr = QString(m_wirelessSetting->macAddress().toHex()).toUpper();

    if (m_macStrMap.values().contains(macAddr)) {
        m_deviceMac->setCurrent(macAddr);
    } else {
        // set macAddress of the current device to be default value
        auto it = m_macStrMap.constBegin();
        for (; it != m_macStrMap.constEnd(); ++it) {
            if (it.key().contains(m_deviceInterface)) {
                m_deviceMac->setCurrent(it.value());
                break;
            }
        }

        Q_ASSERT(it != m_macStrMap.constEnd());
    }

    //m_clonedMac->setTitle(tr("Cloned MAC Addr"));
    //QString tmp = QString(m_wirelessSetting->clonedMacAddress().toHex()).toUpper();
    //QString clonedMacAddr;
    //if (!tmp.isEmpty()) {
        //for (int i = 0; i < tmp.size(); ++i) {
            //if (i != 0 && i % 2 == 0) {
                //clonedMacAddr.append(":");
            //}
            //clonedMacAddr.append(tmp.at(i));
        //}
    //}
    //m_clonedMac->setText(clonedMacAddr);

    m_customMtuSwitch->setTitle(tr("Customize MTU"));
    m_customMtuSwitch->setChecked(!(m_wirelessSetting->mtu() == 0));

    m_customMtu->setTitle(tr("MTU"));
    m_customMtu->spinBox()->setMinimum(0);
    m_customMtu->spinBox()->setMaximum(10000);
    m_customMtu->spinBox()->setValue(m_wirelessSetting->mtu());
    onCostomMtuChanged(m_customMtuSwitch->checked());

    appendItem(m_apSsid);
    appendItem(m_deviceMac);
    //appendItem(m_clonedMac);
    appendItem(m_customMtuSwitch);
    appendItem(m_customMtu);
}

void WirelessSection::initConnection()
{
    connect(m_deviceMac, &ComboBoxWidget::requestPage, this, &WirelessSection::requestPage);
    //connect(m_clonedMac->textEdit(), &QLineEdit::editingFinished, this, &WirelessSection::allInputValid);
    connect(m_customMtuSwitch, &SwitchWidget::checkedChanged, this, &WirelessSection::onCostomMtuChanged);
    connect(m_apSsid->textEdit(), &QLineEdit::editingFinished, this, &WirelessSection::allInputValid);
    connect(m_apSsid->textEdit(), &QLineEdit::textChanged, this, &WirelessSection::ssidChanged);
}

void WirelessSection::onCostomMtuChanged(const bool enable)
{
    m_customMtu->setVisible(enable);
}
