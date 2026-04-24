/*
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>
 * Qt6 Refactor by Gemini (Safe Version)
 */

#include "tileset.h"
#include <QPainter>

inline bool bits(TileSet::Tiles flags, TileSet::Tile mask)
{ return (flags & mask) == mask; }

TileSet::TileSet() : _w1(0), _h1(0), _w3(0), _h3(0) {}

TileSet::TileSet(const QPixmap& pixmap, int w1, int h1, int w2, int h2)
    : _w1(w1), _h1(h1), _w3(0), _h3(0)
{
    if (pixmap.isNull() == false) {
        qreal dpr = pixmap.devicePixelRatio();
        _w3 = pixmap.width() / dpr - w1 - w2;
        _h3 = pixmap.height() / dpr - h1 - h2;
        
        _pixmaps.reserve(9);
        int sw1 = w1 * dpr;
        int sh1 = h1 * dpr;
        int sw2 = w2 * dpr;
        int sh2 = h2 * dpr;
        int sw3 = pixmap.width() - sw1 - sw2;
        int sh3 = pixmap.height() - sh1 - sh2;

        initPixmap(_pixmaps, pixmap, w1, h1, QRect(0, 0, sw1, sh1));
        initPixmap(_pixmaps, pixmap, w2, h1, QRect(sw1, 0, sw2, sh1));
        initPixmap(_pixmaps, pixmap, _w3, h1, QRect(sw1 + sw2, 0, sw3, sh1));

        initPixmap(_pixmaps, pixmap, w1, h2, QRect(0, sh1, sw1, sh2));
        initPixmap(_pixmaps, pixmap, w2, h2, QRect(sw1, sh1, sw2, sh2));
        initPixmap(_pixmaps, pixmap, _w3, h2, QRect(sw1 + sw2, sh1, sw3, sh2));

        initPixmap(_pixmaps, pixmap, w1, _h3, QRect(0, sh1 + sh2, sw1, sh3));
        initPixmap(_pixmaps, pixmap, w2, _h3, QRect(sw1, sh1 + sh2, sw2, sh3));
        initPixmap(_pixmaps, pixmap, _w3, _h3, QRect(sw1 + sw2, sh1 + sh2, sw3, sh3));
    }
}

void TileSet::initPixmap(PixmapList& list, const QPixmap& pixmap, int w, int h, const QRect& rect)
{
    if (w <= 0 or h <= 0) {
        list.append(QPixmap());
    } else {
        QPixmap p = pixmap.copy(rect);
        p.setDevicePixelRatio(pixmap.devicePixelRatio());
        list.append(p);
    }
}

void TileSet::render(const QRect& rect, QPainter* painter, Tiles tiles) const
{
    if (isValid() == false) return;

    const int x0 = rect.x();
    const int y0 = rect.y();
    const int w = rect.width();
    const int h = rect.height();

    const int wLeft = _w1;
    const int wRight = _w3;
    const int wCenter = w - (wLeft + wRight);

    const int hTop = _h1;
    const int hBottom = _h3;
    const int hCenter = h - (hTop + hBottom);

    if (bits(tiles, TopLeft)) painter->drawPixmap(x0, y0, _pixmaps.at(0));
    if (bits(tiles, TopRight)) painter->drawPixmap(x0 + w - wRight, y0, _pixmaps.at(2));
    if (bits(tiles, BottomLeft)) painter->drawPixmap(x0, y0 + h - hBottom, _pixmaps.at(6));
    if (bits(tiles, BottomRight)) painter->drawPixmap(x0 + w - wRight, y0 + h - hBottom, _pixmaps.at(8));

    if (wCenter > 0) {
        if (tiles & Top) painter->drawPixmap(x0 + wLeft, y0, wCenter, hTop, _pixmaps.at(1));
        if (tiles & Bottom) painter->drawPixmap(x0 + wLeft, y0 + h - hBottom, wCenter, hBottom, _pixmaps.at(7));
    }

    if (hCenter > 0) {
        if (tiles & Left) painter->drawPixmap(x0, y0 + hTop, wLeft, hCenter, _pixmaps.at(3));
        if (tiles & Right) painter->drawPixmap(x0 + w - wRight, y0 + hTop, wRight, hCenter, _pixmaps.at(5));
    }

    if (bits(tiles, Center) and wCenter > 0 and hCenter > 0) {
        painter->drawPixmap(x0 + wLeft, y0 + hTop, wCenter, hCenter, _pixmaps.at(4));
    }
}
