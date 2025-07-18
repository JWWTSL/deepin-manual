// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "dbus/manual_open_proxy.h"
#include "base/ddlog.h"

#include <QtDBus/QtDBus>

ManualOpenProxy::ManualOpenProxy(QObject *parent)
    : QObject(parent)
{
    this->setObjectName("ManualOpenProxy");
    qCDebug(app) << "ManualOpenProxy initialized";
}

ManualOpenProxy::~ManualOpenProxy()
{
    qCDebug(app) << "ManualOpenProxy destroyed";
}

/**
 * @brief ManualOpenProxy::Open
 * @param app_name
 * @note DBus接口，用于打开给定应用名称的帮助文档内容
 */
void ManualOpenProxy::Open(const QString &app_name)
{
    qCDebug(app) << "Open manual requested for app:" << app_name;
    emit this->openManualRequested(app_name, "");
    qCDebug(app) << "Manual open signal emitted";
}

/**
 * @brief ManualOpenProxy::OpenTitle
 * @param app_name
 * @param title_name
 * 通过 应用名称与标签名，打开相应页面
 */
void ManualOpenProxy::OpenTitle(const QString &app_name, const QString &title_name)
{
    qCDebug(app) << app_name << "---" << title_name;
    emit this->openManualRequested(app_name, title_name);
    qCDebug(app) << "Title open signal emitted";
}

/**
 * @brief ManualOpenProxy::ShowManual
 * @param app_name
 * 显示帮助手册页面， 调用open()接口实现
 */
void ManualOpenProxy::ShowManual(const QString &app_name)
{
    qCDebug(app) << "Show manual requested for app:" << app_name;
    this->Open(app_name);
}

/**
 * @brief ManualOpenProxy::Search
 * @param keyword
 * @note DBus接口，根据给定的关键字发起搜索请求
 */
void ManualOpenProxy::Search(const QString &keyword)
{
    qCDebug(app) << keyword;
    emit this->searchRequested(keyword);
    qCDebug(app) << "Search signal emitted";
}
