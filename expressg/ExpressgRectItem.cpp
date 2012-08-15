/*  This file is part of [To be named], a STEP-Express viewer
    Copyright (C) 2012 Laurent Bauer lahoraent@hotmail.com

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; version 2
    of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "ExpressgRectItem.h"
#include <QBrush>
#include <QPen>

ExpressgRectItem::ExpressgRectItem(const QString & text, bool hasLeftRect, bool hasRightRect, bool isDashed, QGraphicsRectItem * parent)
    : QGraphicsRectItem(parent)
{
    qreal xLeft=0.0;

    QPen pen(Qt::white);
    if (isDashed)
    {
        pen.setStyle(Qt::CustomDashLine);
        QVector<qreal> dashes;
        dashes << 6 << 4;
        pen.setDashPattern(dashes);
    }
    setPen(pen);
    setBrush(Qt::transparent);

    if (hasLeftRect) xLeft = 20.0;

    QGraphicsTextItem * textItem = new QGraphicsTextItem (text, this);

    qreal xRight = xLeft+15;
    textItem->setPos(xRight,10.0);
    textItem->setDefaultTextColor(Qt::white);
    qreal textWidth = textItem->boundingRect().width();
    if (textWidth<85.0)  textWidth=85.0;
    xRight+=xLeft+textWidth+15.0; // 15 = margin after text

    if (hasLeftRect)
    {
        QGraphicsLineItem * leftRectLine = new QGraphicsLineItem(xLeft, 0.0, xLeft, 40.0, this);
        leftRectLine->setPen(pen);
    }

    if (hasRightRect)
    {
        QGraphicsLineItem * rightRectLine = new QGraphicsLineItem(xRight, 0.0, xRight, 40.0, this);
        rightRectLine->setPen(pen);
        xRight+=20.0;
    }

    setRect( 0.0, 0.0,xRight,40.0);

}
