#include "basestyle.h"
#include "phantomcolor.h"
#include <QStyleOption>
#include <QPainter>
#include <QWidget>
#include <QHash>
#include <QSharedPointer>

namespace Ph = Phantom;

static int GroupBox_Rounding = 4;
static bool BranchesOnEdge = false;
static qreal CheckMark_WidthOfHeightScale = 1.0;
static qreal DefaultFrame_Radius = 4.0;

class BaseStylePrivate {
public:
    BaseStylePrivate() : headSwatchFastKey(0) {}
    QHash<long long, QColor> swatchCache; // 简化为存储 QColor
    long long headSwatchFastKey;
    QPen checkBox_pen_scratch; // 补齐缺失的成员
};

namespace {
    struct PSave { QPainter* p; PSave(QPainter* _p):p(_p){p->save();} ~PSave(){p->restore();} };
    static inline void fillRectOutline(QPainter* p, const QRect& r, int, const QColor& c) { p->setPen(c); p->drawRect(r); }
    static inline void fillRectEdges(QPainter* p, const QRect& r, Qt::Edges e, int, const QColor& c) { p->fillRect(r, c); }
    static inline void drawArrow(QPainter* p, const QRect& r, int, const QBrush& b) { p->fillRect(r, b); }
    static inline void paintBorderedRoundRect(QPainter* p, const QRect& r, int, const QColor&, int, int) { p->drawRoundedRect(r, 4, 4); }
    static inline void drawCheck(QPainter* p, const QPen& pen, const QRect& r, const QColor&, const QColor&) { p->setPen(pen); p->drawPolyline(r.bottomLeft(), r.center(), r.topRight()); }
    static inline QRect expandRect(const QRect& r, int i) { return r.adjusted(-i, -i, i, i); }
}

using Swatchy = QColor;

void BaseStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    auto d = const_cast<BaseStylePrivate*>(reinterpret_cast<const BaseStylePrivate*>(this)); 
    QColor swatch = option->palette.color(QPalette::WindowText); // 直接用标准调色板
    QColor fgColor = option->palette.color(QPalette::Text);

    switch (element) {
