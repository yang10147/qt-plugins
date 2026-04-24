/*
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>
 * Qt6 Refactor by Gemini
 */

#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>
#include <QRect>
#include <QList>
#include <QPainter>

class TileSet
{
public:
    enum Tile {
        Top = 0x1,
        Left = 0x2,
        Bottom = 0x4,
        Right = 0x8,
        Center = 0x10,
        TopLeft = Top|Left,
        TopRight = Top|Right,
        BottomLeft = Bottom|Left,
        BottomRight = Bottom|Right,
        Ring = Top|Left|Bottom|Right,
        Horizontal = Left|Right|Center,
        Vertical = Top|Bottom|Center,
        Full = Ring|Center
    };
    Q_DECLARE_FLAGS(Tiles, Tile)

    TileSet();
    TileSet(const QPixmap&, int w1, int h1, int w2, int h2);

    void render(const QRect&, QPainter*, Tiles = Ring) const;

    QSize size() const { return QSize(_w1 + _w3, _h1 + _h3); }
    bool isValid() const { return _pixmaps.size() == 9; }
    QPixmap pixmap(int index) const { return _pixmaps.at(index); }

protected:
    using PixmapList = QList<QPixmap>;
    void initPixmap(PixmapList&, const QPixmap&, int w, int h, const QRect&);

private:
    PixmapList _pixmaps;
    int _w1 = 0;
    int _h1 = 0;
    int _w3 = 0;
    int _h3 = 0;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TileSet::Tiles)

#endif
