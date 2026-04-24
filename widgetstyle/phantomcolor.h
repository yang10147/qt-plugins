/*
 * Copyright (C) 2020 Reven Martin
 */

#ifndef PHANTOMCOLOR_H
#define PHANTOMCOLOR_H

#include <QColor>
#include <QPalette>

namespace Phantom {

class Color
{
public:
    // 计算颜色的明度，Qt6 依然支持，但我们确保返回类型明确
    static QColor alphaColor(const QColor &color, qreal alpha);
    static QColor mix(const QColor &c1, const QColor &c2, qreal weight);
    
    // 下面这些函数通常在 basestyle.cpp 里被大量调用
    static QColor lightColor(const QColor &color, int factor = 150);
    static QColor darkColor(const QColor &color, int factor = 150);
    
    static bool isDark(const QColor &color);
};

} // namespace Phantom

#endif
