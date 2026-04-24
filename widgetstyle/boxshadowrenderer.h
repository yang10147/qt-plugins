/*
 * Copyright (C) 2018 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 */

#pragma once

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QSize>
#include <QList>

class BoxShadowRenderer
{
public:
    void setBoxSize(const QSize &size);
    void setBorderRadius(qreal radius);
    void setDevicePixelRatio(qreal dpr);
    void addShadow(const QPoint &offset, int radius, const QColor &color);

    QImage render() const;

    static QSize calculateMinimumBoxSize(int radius);
    static QSize calculateMinimumShadowTextureSize(const QSize &boxSize, int radius, const QPoint &offset);

private:
    QSize m_boxSize;
    qreal m_borderRadius = 0.0;
    qreal m_dpr = 1.0;

    struct Shadow {
        QPoint offset;
        int radius;
        QColor color;
    };
    QList<Shadow> m_shadows;
};
