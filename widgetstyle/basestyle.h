/*
 * Copyright (C) 2020 Reven Martin
 * Copyright (C) 2020 KeePassXC Team <team@keepassxc.org>
 * Copyright (C) 2019 Andrew Richards
 *
 * Derived from Phantomstyle and relicensed under the GPLv2 or v3.
 */

#ifndef BASESTYLE_H
#define BASESTYLE_H

#include <QCommonStyle>
#include <QPalette>
#include <QPainter>
#include <QApplication>
#include <QWidget>

class BaseStylePrivate;
class ShadowHelper;
class BlurHelper;

class BaseStyle : public QCommonStyle
{
    Q_OBJECT

public:
    BaseStyle();
    ~BaseStyle() override;

    enum PhantomPrimitiveElement
    {
        // Qt6 中 PE_CustomBase 依然可用，但建议明确作用域
        Phantom_PE_IndicatorTabNew = QStyle::PE_CustomBase + 1,
        Phantom_PE_ScrollBarSliderVertical,
        Phantom_PE_WindowFrameColor,
    };

    static QPalette lightModePalette();
    static QPalette darkModePalette();
    QPalette standardPalette() const override;

    void drawPrimitive(PrimitiveElement elem,
                       const QStyleOption* option,
                       QPainter* painter,
                       const QWidget* widget = nullptr) const override;

    void drawControl(ControlElement ce, 
                     const QStyleOption* option, 
                     QPainter* painter, 
                     const QWidget* widget = nullptr) const override;

    int pixelMetric(PixelMetric metric,
                    const QStyleOption* option = nullptr,
                    const QWidget* widget = nullptr) const override;

    void drawComplexControl(ComplexControl control,
                            const QStyleOptionComplex* option,
                            QPainter* painter,
                            const QWidget* widget = nullptr) const override;

    QRect subElementRect(SubElement r, 
                         const QStyleOption* opt, 
                         const QWidget* widget = nullptr) const override;

    QSize sizeFromContents(ContentsType type,
                           const QStyleOption* option,
                           const QSize& size,
                           const QWidget* widget = nullptr) const override;

    SubControl hitTestComplexControl(ComplexControl cc,
                                     const QStyleOptionComplex* opt,
                                     const QPoint& pt,
                                     const QWidget* w = nullptr) const override;

    QRect subControlRect(ComplexControl cc,
                         const QStyleOptionComplex* opt,
                         SubControl sc,
                         const QWidget* widget = nullptr) const override;

    QPixmap generatedIconPixmap(QIcon::Mode iconMode, 
                                const QPixmap& pixmap, 
                                const QStyleOption* opt) const override;

    int styleHint(StyleHint hint,
                  const QStyleOption* option = nullptr,
                  const QWidget* widget = nullptr,
                  QStyleHintReturn* returnData = nullptr) const override;

    QRect itemPixmapRect(const QRect& r, int flags, const QPixmap& pixmap) const override;

    void drawItemPixmap(QPainter* painter, const QRect& rect, int alignment, const QPixmap& pixmap) const override;

    void drawItemText(QPainter* painter,
                      const QRect& rect,
                      int flags,
                      const QPalette& pal,
                      bool enabled,
                      const QString& text,
                      QPalette::ColorRole textRole = QPalette::NoRole) const override;

    using QCommonStyle::polish;
    void polish(QApplication* app) override;
    void unpolish(QApplication* app) override;
    void polish(QWidget *widget) override;
    void unpolish(QWidget *widget) override;

    bool isDarkMode() const;

protected:
    virtual QString getAppStyleSheet() const
    {
        return {};
    }

    BaseStylePrivate* d;

private:
    ShadowHelper *m_shadowHelper;
    BlurHelper *m_blurHelper;
};

#endif
