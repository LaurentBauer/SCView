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

#include "EntityItem.h"
#include <QLinearGradient>
#include <QGraphicsDropShadowEffect>
#include <QPen>
#include <QtGlobal>
#include <ExpDict.h>
#include "TypeItem.h"
#include "LinkItem.h"
#include "ExpressgRectItem.h"

#include <iostream>
using namespace std;

EntityItem::EntityItem(const EntityDescriptor *entityDescriptor, QGraphicsItem *parent, QPointF pos)
    : QGraphicsRectItem(parent)
    , m_ED (entityDescriptor)
{
    qreal x0=0.0;
    qreal y0=0.0;
    if (parent)
    {
        x0=pos.x();
        y0=pos.y();
    }

    // EntityItem graphical representation
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setBrush(QColor(Qt::transparent));
    setPen(QPen(Qt::white));

    QGraphicsTextItem * textItem = new QGraphicsTextItem (entityDescriptor->Name(), this);
    textItem->setPos(x0+15.0,y0+10.0);
    textItem->setDefaultTextColor(Qt::white);

    qreal rectWidth = textItem->boundingRect().width();

    if (rectWidth<100.0) rectWidth=100.0;
    setRect( x0, y0,rectWidth+30.0,40.0);
    // End EntityItem graphical representation

    // Entity Item : children
    const AttrDescriptorList * attrList = &( ( ( EntityDescriptor * )entityDescriptor )->ExplicitAttr() );
    AttrDescLinkNode * attrPtr = ( AttrDescLinkNode * )attrList->GetHead();
    int attrCount =0;
    bool attrIsAggregate;

    qreal childXBase = x0+rectWidth+50.0;
    qreal childX;
    qreal childY=y0;
    qreal vLineHeight=0.0;
    while( attrPtr != 0 )
    {
        const AttrDescriptor * attrDescriptor = attrPtr->AttrDesc();
        attrIsAggregate = attrDescriptor->IsAggrType();
        childX = childXBase;

        // LINKS (horizontal)
        bool attributeIsOptional = (attrDescriptor->Optional()==SDAI_LOGICAL(LTrue));
        LinkItem * linkItem = new LinkItem(attrDescriptor, attributeIsOptional, QPointF(childXBase, childY+20.0), this );
        qreal linkWidth = linkItem->boundingRect().width();
        if ( childXBase+linkWidth > childX ) childX = childXBase+linkWidth;

        // CHILDREN
        const EntityDescriptor * entityDescriptor = dynamic_cast<const EntityDescriptor *> (attrDescriptor->DomainType() );
        const TypeDescriptor * aggrElemTypeDescriptor =0;
        const EntityDescriptor * aggrElementEntityDescriptor=0;
        if (attrIsAggregate)
        {
            aggrElemTypeDescriptor = attrDescriptor->AggrElemTypeDescriptor();   // pointed type inside the aggregate
            aggrElementEntityDescriptor = dynamic_cast<const EntityDescriptor *> ( aggrElemTypeDescriptor ); // pointed entity inside aggregate;
        }

        if (entityDescriptor)
        // is an Entity
        {
            // this is an ENTITY
            EntityItem * item = new EntityItem(entityDescriptor, this, QPointF( childX, childY ));
            vLineHeight = childY;
            childY += qMax(item->childrenBoundingRect().height()+10.0, 50.0);
        }
        else if ( aggrElementEntityDescriptor )
        // is an aggregate and the pointed type is an entity
        {
            EntityItem * item = new EntityItem(aggrElementEntityDescriptor, this, QPointF( childX, childY ));
            vLineHeight = childY;
            childY += qMax(item->childrenBoundingRect().height()+10.0, 50.0);
        }
        else // not an entity, but an attribute
        {
            const TypeDescriptor * childDescriptor = attrDescriptor->DomainType();
            if (attrIsAggregate)
                childDescriptor = attrDescriptor->AggrElemTypeDescriptor();   // pointed type inside the aggregate

            TypeItem * item = new TypeItem(childDescriptor, this);
            item->setPos( childX, childY );
            vLineHeight = childY;
            childY+=50.0;
        }
        attrPtr = ( AttrDescLinkNode * )attrPtr->NextNode();
        attrCount++;
    }

    Q_ASSERT( attrList->EntryCount() == attrCount );    // control : each attribute has been processed

    // draw remaining links
    if (attrCount >0)
    {
        // horizontal startLine
        QGraphicsLineItem * hLineItem = new QGraphicsLineItem(childXBase-20.0, y0+20.0, childXBase, y0+20.0, this);
        hLineItem->setPen(QPen(Qt::white));
        // vertical Line
        QGraphicsLineItem * vLineItem = new QGraphicsLineItem(childXBase, y0+20.0, childXBase, vLineHeight+20.0, this);
        vLineItem->setPen(QPen(Qt::white));
    }
}


/*
        cout << "Attribut = " << attrDescriptor->Name()
             << " , type = " << attrDescriptor->TypeName()
             << " , attrType= " << attrDescriptor->AttrType()
             << " , refersToType= " << attrDescriptor->RefersToType()
             << " , ReftypTyp= " << attrDescriptor->ReferentType()->Type()
             << " , " << attrDescriptor->ReferentType()->ReferentType()
             << endl;

        if ( attrIsAggregate )
        {
            attrDescriptor->AttrExprDefStr(str);
            cout << "Is Aggregate :" <<  str << " | " << attrDescriptor->TypeName() <<  endl;
            cout << "Type pointé :" << attrDescriptor->AggrElemTypeDescriptor()->Name() << endl;
            const EntityDescriptor * referentEntityDescriptor = dynamic_cast<const EntityDescriptor *> ( attrDescriptor->AggrElemTypeDescriptor() );
            if (referentEntityDescriptor)
                cout << "Type pointé EST une entité" << endl;
            else cout << "Type pointé N'EST PAS une entité" << endl;
        }
*/

/*
    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect();
    effect->setColor(QColor(255,255,255,50));
    effect->setXOffset(1.0);
    effect->setYOffset(1.0);
    setGraphicsEffect(effect);
*/
    /*
    QLinearGradient gradiant;
    gradiant.setStart(0.0,0.0);
    gradiant.setFinalStop(0.0,60.0);
    gradiant.setColorAt(0.0, QColor(98,98,93));
    gradiant.setColorAt(0.85, QColor(112,112,144));
    gradiant.setColorAt(1.0, QColor(96,96,112));
    setBrush(gradiant);
*/
