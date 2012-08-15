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

#include "LinkItem.h"
#include <ExpDict.h>
#include <QBrush>
#include <QPen>

LinkItem::LinkItem(const AttrDescriptor * attrDescriptor, bool attributeIsOptional, QPointF pos, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    qreal x = pos.x();
    qreal y = pos.y();

    QString name(attrDescriptor->Name());
    if (attrDescriptor->IsAggrType())
    {
        QString rightSide (attrDescriptor->TypeName());
        rightSide = rightSide.section(']',0,0);
        name += " : " + rightSide  + "]";
    }

    QGraphicsTextItem * textItem = new QGraphicsTextItem(name, this);
    textItem->setDefaultTextColor(Qt::white);
    textItem->setPos( x + 10.0, y-18.0);

    qreal w = textItem->boundingRect().width();
    QGraphicsLineItem * lineItem = new QGraphicsLineItem(x, y, x+w+20.0, y, this);
    if (attributeIsOptional)
    {
        QPen pen(Qt::CustomDashLine);
        pen.setBrush(QColor(Qt::white));
        QVector<qreal> dashes;
        dashes << 6 << 4;
        pen.setDashPattern(dashes);
        lineItem->setPen(pen);
    }
    else lineItem->setPen(QPen(Qt::white));
    QGraphicsEllipseItem * circle = new QGraphicsEllipseItem(x+w+20.0,y-5.0,10.0,10.0, this);
    circle->setBrush(QBrush(Qt::white));

    setRect(childrenBoundingRect());
    setPen(Qt::NoPen);
}
