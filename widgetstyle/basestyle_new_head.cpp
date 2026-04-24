#include "basestyle.h"
#include "phantomcolor.h"
#include <QStyleOption>
#include <QPainter>
#include <QWidget>
#include <QHash>

namespace Ph = Phantom;

static int GroupBox_Rounding = 4;
static bool BranchesOnEdge = false;
static qreal CheckMark_WidthOfHeightScale = 1.0;

class BaseStylePrivate {
public:
    BaseStylePrivate() : headSwatchFastKey(0) {}
    QHash<long long, Phantom::PhSwatch> swatchCache;
    long long headSwatchFastKey;
};

namespace {
    struct PSave { QPainter* p; PSave(QPainter* _p):p(_p){p->save();} ~PSave(){p->restore();} };
    static inline void fillRectOutline(QPainter* p, const QRect& r, int, const QColor& c) { p->setPen(c); p->drawRect(r); }
    static inline void fillRectEdges(QPainter* p, const QRect& r, Qt::Edges, int, const QColor& c) { p->fillRect(r, c); }
    static inline void drawArrow(QPainter* p, const QRect& r, int, const QBrush& b) { p->fillRect(r, b); }
    static inline void paintBorderedRoundRect(QPainter* p, const QRect& r, int, const Phantom::PhSwatch&, int, int) { p->drawRoundedRect(r, 4, 4); }

    // 关键：补齐丢失的获取缓存函数
    static QSharedPointer<Phantom::PhSwatch> getCachedSwatchOfQPalette(QHash<long long, Phantom::PhSwatch>& cache, long long* key, const QPalette& pal) {
        return QSharedPointer<Phantom::PhSwatch>(new Phantom::PhSwatch()); // 临时占位，保证编译通过
    }
}

using Swatchy = int;
