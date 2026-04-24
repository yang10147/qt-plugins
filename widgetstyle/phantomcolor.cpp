#include <QColor>
#include <QVariant>
#include <QColor>
#include <QVariant>
#include <QColor>
/*
 * Copyright (C) 2020 Reven Martin
 */

#include "phantomcolor.h"
#include <QtMath>

namespace Phantom {

QColor Color::alphaColor(const QColor &color, qreal alpha)
{
    if (alpha >= 1.0) return color;
    if (alpha <= 0.0) return Qt::transparent;

    QColor c = color;
    c.setAlphaF(alpha);
    return c;
}

QColor Color::mix(const QColor &c1, const QColor &c2, qreal weight)
{
    if (weight >= 1.0) return c1;
    if (weight <= 0.0) return c2;

    qreal r = c1.redF() * weight + c2.redF() * (1.0 - weight);
    qreal g = c1.greenF() * weight + c2.greenF() * (1.0 - weight);
    qreal b = c1.blueF() * weight + c2.blueF() * (1.0 - weight);
    qreal a = c1.alphaF() * weight + c2.alphaF() * (1.0 - weight);

    return QColor::fromRgbF(
        qBound(0.0, r, 1.0),
        qBound(0.0, g, 1.0),
        qBound(0.0, b, 1.0),
        qBound(0.0, a, 1.0)
    );
}

QColor Color::lightColor(const QColor &color, int factor)
{
    return color.lighter(factor);
}

QColor Color::darkColor(const QColor &color, int factor)
{
    return color.darker(factor);
}

bool Color::isDark(const QColor &color)
{
    // 使用标准的亮度转换公式 (Rec. 601)
    return (0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) < 128;
}

} // namespace Phantom
