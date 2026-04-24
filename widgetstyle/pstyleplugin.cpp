/*
 * Copyright (C) 2020 Reven Martin
 */

#include "pstyleplugin.h"
#include "basestyle.h"

#include <QStyle>

PStylePlugin::PStylePlugin(QObject *parent)
    : QStylePlugin(parent)
{
}

QStyle *PStylePlugin::create(const QString &key)
{
    // Qt6 的样式键值对匹配通常不区分大小写
    if (key.compare(QLatin1String("cutefish"), Qt::CaseInsensitive) == 0) {
        return new BaseStyle();
    }

    return nullptr;
}
