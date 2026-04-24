/*
 * Copyright (C) 2020 Reven Martin
 */

#ifndef PSTYLEPLUGIN_H
#define PSTYLEPLUGIN_H

#include <QStylePlugin>

class PStylePlugin : public QStylePlugin
{
    Q_OBJECT
    // 确保这里的 JSON 文件名与目录下的文件名一致
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "cutefishstyle.json")

public:
    explicit PStylePlugin(QObject *parent = nullptr);

    QStyle *create(const QString &key) override;
};

#endif
