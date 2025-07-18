/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.deepin.Manual.Search.xml -a manual_search_adapter -c ManualSearchAdapter
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "manual_search_adapter.h"
#include "base/ddlog.h"

/*
 * Implementation of adaptor class ManualSearchAdapter
 */

ManualSearchAdapter::ManualSearchAdapter(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    qCDebug(app) << "Creating adaptor for interface com.deepin.Manual.Search";
    // constructor
    setAutoRelaySignals(true);
}

ManualSearchAdapter::~ManualSearchAdapter()
{
    qCDebug(app) << "Deleting adaptor for interface com.deepin.Manual.Search";
    // destructor
}

/**
 * @brief ManualSearchAdapter::ManualExists
 * @param in0
 * @return
 */
bool ManualSearchAdapter::ManualExists(const QString &in0)
{
    // handle method call com.deepin.Manual.Search.ManualExists
    qCDebug(app) << "DBus call: ManualExists for" << in0;
    bool out0;
    QMetaObject::invokeMethod(parent(), "ManualExists", Q_RETURN_ARG(bool, out0), Q_ARG(QString, in0));
    qCDebug(app) << "ManualExists result:" << out0;
    return out0;
}

/**
 * @brief ManualSearchAdapter::OnNewWindowOpen
 * @param data
 */
void ManualSearchAdapter::OnNewWindowOpen(const QString &data)
{
    qCDebug(app) << "DBus call: OnNewWindowOpen with data:" << data;
    QMetaObject::invokeMethod(parent(), "OnNewWindowOpen", Q_ARG(QString, data));
    qCDebug(app) << "OnNewWindowOpen signal emitted";
}
