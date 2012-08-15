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


#include "TypeItem.h"
#include <QBrush>
#include <QPen>

TypeItem::TypeItem(const TypeDescriptor *td, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
    , m_RightSymbol(new QGraphicsRectItem(this))
{



    setBrush(QColor(Qt::white));

    std::string str;
    str.append(td->BaseTypeName());
    QString text = str.c_str();
    QGraphicsTextItem * textItem = new QGraphicsTextItem (text, this);

    // geom:
    textItem->setPos(15.0,10.0);
    qreal rectWidth = textItem->boundingRect().width();
    if (rectWidth<85.0)  rectWidth=85.0;
    setRect( 0.0, 0.0,rectWidth+45.0,40.0);
    m_RightSymbol->setRect(rectWidth+30.0, 0.0, 15.0, 40.0);
}


void TypeItem::setOptional(bool isOptional)
{
    if (isOptional)
    {
        QPen pen(Qt::CustomDashLine);
        QVector<qreal> dashes;
        dashes << 6 << 4;
        pen.setDashPattern(dashes);
        pen.setWidth(2);
        setPen(pen);
        m_RightSymbol->setPen(pen);
    }
    else
    {
        QPen pen(Qt::SolidLine);
        setPen(pen);
        m_RightSymbol->setPen(pen);
    }
}
