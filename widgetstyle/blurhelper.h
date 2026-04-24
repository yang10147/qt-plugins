/*
 * Copyright (C) 2020 Reven Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 or (at your option)
 * version 3 of the License.
 */

#ifndef BLURHELPER_H
#define BLURHELPER_H

#include <QObject>
#include <QSet>
#include <QPointer>
#include <QHash>

class QWindow;
class QWidget;

class BlurHelper : public QObject
{
    Q_OBJECT

public:
    explicit BlurHelper(QObject* parent = nullptr);
    ~BlurHelper() override;

    void registerWidget(QWidget*);
    void unregisterWidget(QWidget*);

    bool eventFilter(QObject*, QEvent*) override;

protected:
    void installBlur(QWindow*);
    void uninstallBlur(QWindow*);

private:
    // Qt6 中 QHash 性能优化，且 QVector 已并入 QList
    QHash<QWindow*, QPointer<QWidget>> m_widgets;
};

#endif
