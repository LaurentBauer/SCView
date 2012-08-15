/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact:  Qt Software Information (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
**************************************************************************/

#ifndef MANHATTANSTYLE_H
#define MANHATTANSTYLE_H

#include <QStyle>
#include <QWindowsStyle>


QT_BEGIN_NAMESPACE
class QLinearGradient;
class QBrush;
QT_END_NAMESPACE

class ManhattanStylePrivate;

class ManhattanStyle : public QWindowsStyle
{
    Q_OBJECT;

public:
    ManhattanStyle(const QString &);

    ~ManhattanStyle();

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = 0) const;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = 0) const;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = 0) const;

    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QRect subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const;

    SubControl hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option, const QPoint &pos, const QWidget *widget = 0) const;
    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt, const QWidget *widget = 0) const;
    int styleHint(StyleHint hint, const QStyleOption *option = 0, const QWidget *widget = 0, QStyleHintReturn *returnData = 0) const;
    QRect itemRect(QPainter *p, const QRect &r, int flags, bool enabled, const QPixmap *pixmap, const QString &text, int len = -1) const;
    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const;

    QPalette standardPalette() const;

    void polish(QWidget *widget);
    void polish(QPalette &pal);
    void polish(QApplication *app);

    void unpolish(QWidget *widget);
    void unpolish(QApplication *app);

protected:
    bool event(QEvent *e);

protected Q_SLOTS:
    QIcon standardIconImplementation(StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const;
    int layoutSpacingImplementation(QSizePolicy::ControlType control1,
                                    QSizePolicy::ControlType control2,
                                    Qt::Orientation orientation,
                                    const QStyleOption *option = 0,
                                    const QWidget *widget = 0) const;

public:
    // Height of the project explorer navigation bar
    static int navigationWidgetHeight() { return 24; }
//    static qreal sidebarFontSize();
//    static QPalette sidebarFontPalette(const QPalette &original);

    // This is our color table, all colors derive from baseColor
    static QColor baseColor(){ return QColor(0x7579a8); } // Qt : 79629c vroom : a99bd0
    static QColor panelTextColor() { return Qt::white; }
    static QColor highlightColor();
    static QColor shadowColor();
    static QColor borderColor();
    static QColor buttonTextColor() { return QColor(0x4c4c4c); }

    // Sets the base color and makes sure all top level widgets are updated
    static void setBaseColor(const QColor &color);

    // Gradients used for panels
    static void horizontalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect);
    static void verticalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect);
    static void menuGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect);

    // Pixmap cache should only be enabled for X11 due to slow gradients
    static bool usePixmapCache() { return false; } // lolo : false. Original:true





private:
    ManhattanStylePrivate *d;
    Q_DISABLE_COPY(ManhattanStyle)

};

#endif // MANHATTANSTYLE_H
